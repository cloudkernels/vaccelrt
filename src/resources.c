// SPDX-License-Identifier: Apache-2.0

#define _POSIX_C_SOURCE 200809L

#include "resources.h"
#include "error.h"
#include "id_pool.h"
#include "list.h"
#include "log.h"
#include "plugin.h"
#include "utils.h"
#include "vaccel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>

enum { MAX_RESOURCES = 2048, MAX_RESOURCE_RUNDIR = 1024 };

static bool initialized = false;
static id_pool_t id_pool;

/* All the live (created) vAccel resources.
 * At the moment, this is an array where each element is a list of all
 * resources of the same time. We should think the data structure again.
 */
static list_t live_resources[VACCEL_RES_MAX];

int resources_bootstrap(void)
{
	int ret = id_pool_new(&id_pool, MAX_RESOURCES);
	if (ret)
		return ret;

	for (int i = 0; i < VACCEL_RES_MAX; ++i)
		list_init(&live_resources[i]);

	initialized = true;

	return VACCEL_OK;
}

int resources_cleanup(void)
{
	if (!initialized)
		return VACCEL_OK;

	for (int i = 0; i < VACCEL_RES_MAX; ++i) {
		struct vaccel_resource *res;
		struct vaccel_resource *tmp;
		for_each_vaccel_resource_safe(res, tmp, &live_resources[i])
			resource_destroy(res);
	}

	initialized = false;

	return id_pool_destroy(&id_pool);
}

int resource_new(struct vaccel_resource *res, vaccel_resource_t type,
		 void *data, int (*cleanup_resource)(void *))
{
	if (!initialized)
		return VACCEL_EPERM;

	if (!res || type >= VACCEL_RES_MAX)
		return VACCEL_EINVAL;

	res->id = id_pool_get(&id_pool);

	if (res->id <= 0)
		return VACCEL_EUSERS;

	res->type = type;
	res->data = data;
	res->cleanup_resource = cleanup_resource;
	list_init_entry(&res->entry);
	list_add_tail(&live_resources[0], &res->entry);
	atomic_init(&res->refcount, 0);
	res->rundir = NULL;
	res->deps = NULL;
	res->nr_deps = 0;

	return VACCEL_OK;
}

int resource_get_by_id(struct vaccel_resource **resource, vaccel_id_t id)
{
	if (!initialized)
		return VACCEL_EPERM;

	for (int i = 0; i < VACCEL_RES_MAX; ++i) {
		struct vaccel_resource *res;
		struct vaccel_resource *tmp;
		for_each_vaccel_resource_safe(res, tmp, &live_resources[i]) {
			if (id == res->id) {
				*resource = res;
				return VACCEL_OK;
			}
		}
	}

	return VACCEL_EINVAL;
}

int resource_set_deps(struct vaccel_resource *res,
		      struct vaccel_resource **deps, size_t nr_deps)
{
	if (!res || !deps || !nr_deps)
		return VACCEL_EINVAL;

	struct vaccel_plugin *virtio = get_virtio_plugin();
	if (virtio) {
		int err = virtio->info->resource_set_deps(res, deps, nr_deps);
		if (err)
			return err;
	}

	res->deps = deps;
	res->nr_deps = nr_deps;

	return VACCEL_OK;
}

int vaccel_resource_get_deps(struct vaccel_resource ***deps, size_t *nr_deps,
			     struct vaccel_resource *res)
{
	if (!deps || !nr_deps || !res)
		return VACCEL_EINVAL;

	*deps = res->deps;
	*nr_deps = res->nr_deps;

	return VACCEL_OK;
}

int vaccel_resource_deps_to_ids(vaccel_id_t *ids, struct vaccel_resource **deps,
				size_t nr_deps)
{
	if (!ids || !deps || !nr_deps)
		return VACCEL_EINVAL;

	for (size_t i = 0; i < nr_deps; i++) {
		ids[i] = deps[i]->id;
	}

	return VACCEL_OK;
}

int vaccel_resource_deps_from_ids(struct vaccel_resource **deps,
				  vaccel_id_t *ids, size_t nr_ids)
{
	if (!deps || !ids || !nr_ids)
		return VACCEL_EINVAL;

	for (size_t i = 0; i < nr_ids; i++) {
		struct vaccel_resource *res;
		int ret = resource_get_by_id(&res, ids[i]);
		if (ret)
			return VACCEL_EINVAL;
		deps[i] = res;
	}

	return VACCEL_OK;
}

int vaccel_resource_set_deps_from_ids(struct vaccel_resource *res,
				      vaccel_id_t *ids, size_t nr_ids)
{
	if (!res || !ids || !nr_ids)
		return VACCEL_EINVAL;

	struct vaccel_resource **deps =
		(struct vaccel_resource **)malloc(sizeof(*deps) * nr_ids);
	if (!deps)
		return VACCEL_ENOMEM;

	int ret = vaccel_resource_deps_from_ids(deps, ids, nr_ids);
	if (ret) {
		free(deps);
		return VACCEL_ENOMEM;
	}

	res->deps = deps;
	res->nr_deps = nr_ids;

	return VACCEL_OK;
}

int resource_unset_deps(struct vaccel_resource *res)
{
	if (!res)
		return VACCEL_EINVAL;

	res->deps = NULL;
	res->nr_deps = 0;

	return VACCEL_OK;
}

int resource_destroy(struct vaccel_resource *res)
{
	if (!initialized)
		return VACCEL_EPERM;

	if (!res)
		return VACCEL_EINVAL;

	/* Check if this resources is currently registered to a session.
	 * We do not destroy currently-used resources */
	if (atomic_load(&res->refcount)) {
		vaccel_warn("Cannot destroy used resource %lld", res->id);
		return VACCEL_EBUSY;
	}

	id_pool_release(&id_pool, res->id);

	list_unlink_entry(&res->entry);

	/* Cleanup the type-specific resource */
	if (res->cleanup_resource)
		res->cleanup_resource(res->data);

	if (res->rundir) {
		cleanup_rundir(res->rundir);
		free(res->rundir);
	}

	if (res->deps || res->nr_deps)
		vaccel_warn("Resource %lld has deps that will not be destroyed",
			    res->id);

	return VACCEL_OK;
}

void resource_refcount_inc(struct vaccel_resource *res)
{
	if (!res) {
		vaccel_error("BUG! Refcounting invalid resource");
		return;
	}

	atomic_fetch_add(&res->refcount, 1);
}

void resource_refcount_dec(struct vaccel_resource *res)
{
	if (!res) {
		vaccel_error("BUG! Refcounting invalid resource");
		return;
	}

	atomic_fetch_sub(&res->refcount, 1);
}

int resource_create_rundir(struct vaccel_resource *res)
{
	if (!res) {
		vaccel_error(
			"BUG! Trying to create rundir for invalid resource");
		return VACCEL_EINVAL;
	}

	const char *root_rundir = vaccel_rundir();

	char rundir[MAX_RESOURCE_RUNDIR];
	int len = snprintf(rundir, MAX_RESOURCE_RUNDIR, "%s/resource.%lld",
			   root_rundir, res->id);
	
	if (len == MAX_RESOURCE_RUNDIR) {
		vaccel_error("rundir path '%s/resource.%lld' too long",
			     root_rundir, res->id);
		return VACCEL_ENAMETOOLONG;
	}

	int ret = mkdir(rundir, 0700);
	if (ret)
		return errno;

	res->rundir = strndup(rundir, MAX_RESOURCE_RUNDIR);
	if (!res->rundir)
		return VACCEL_ENOMEM;

	return VACCEL_OK;
}

static int is_dir(const char *path) {
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

static int is_url(const char *path) {

}

int vaccel_resource_new(struct vaccel_resource *res,
			const char *path, vaccel_resource_t type)
{
	if (!initialized)
                return VACCEL_EPERM;
        
	if (!res || type >= VACCEL_RES_MAX || !path)
                return VACCEL_EINVAL;

	if (is_url(path)) {
		return vaccel_resource_new_from_url(res, path, type);
	} else {
		if (is_dir(path))
			return vaccel_resource_new_dir(res, path, type);
		else
			return vaccel_resource_new_file(res, path, type);
	}
}
int vaccel_resource_new(struct vaccel_resource *res,
		        const char *path, vaccel_resource_t type)
{
        if (!initialized)
                return VACCEL_EPERM;

        if (!res || type >= VACCEL_RES_MAX || !path)
                return VACCEL_EINVAL;

        res->id = id_pool_get(&id_pool);

        if (res->id <= 0)
                return VACCEL_EUSERS;

        res->type = type;
        res->name = strdup(basename(path));
	res->path = strndup(dirname(path), strlen(path) - strlen(res->name));
	res->nr_files = 1;

        list_init_entry(&res->entry);
        list_add_tail(&live_resources[0], &res->entry);
        atomic_init(&res->refcount, 0);
        res->rundir = NULL;

        return VACCEL_OK;
}

int vaccel_resource_new_multi(struct vaccel_resource *res,
		              const char **paths, vaccel_resource_t type,
			      size_t nr_files)
{
	size_t i;

	if (!initialized)
		return VACCEL_EPERM;

	if (!res || type >= VACCEL_RES_MAX || !paths || !nr_files)
		return VACCEL_EINVAL;

	res->id = id_pool_get(&id_pool);

	if (res->id <= 0)
		return VACCEL_EUSERS;

	char **res_paths;
	res_paths = (char**) malloc (nr_files * sizeof(char*));
	for (i = 0; i < nr_files; ++i) {
		if (!paths[i])
			goto exit;
		res_paths[i] = strdup(paths)

	}
	res->type = type;
	res-
	
	return VACCEL_OK;
exit:
	for (size_t j = 0; j < i; ++j)
		free (res_paths[j]);
	free(res_paths);

	return VACCEL_EINVAL;
	
}
