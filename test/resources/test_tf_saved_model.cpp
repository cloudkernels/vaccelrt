// SPDX-License-Identifier: Apache-2.0

/*
 * TensorFlow Saved Model from Memory Test
 *
 * The code below tests the creation and registration of a TensorFlow saved
 * model from memory.
 *
 */

#include <catch.hpp>
#include <utils.hpp>

#include "utils.h"
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vaccel.h>

TEST_CASE("tf_saved_model_from_memory", "[resources_tf_saved_model]")
{
	int ret;
	char *path = abs_path(SOURCE_ROOT, "examples/models/tf/lstm2/");

	struct vaccel_tf_saved_model *model = vaccel_tf_saved_model_new();
	REQUIRE(model);

	size_t len;
	unsigned char *ptr = read_file_from_dir(path, "saved_model.pb", &len);
	REQUIRE(ptr);
	REQUIRE(len);

	ret = vaccel_tf_saved_model_set_model(model, ptr, len);
	REQUIRE(ret == VACCEL_OK);

	ptr = read_file_from_dir(path, "variables/variables.index", &len);
	REQUIRE(ptr);
	REQUIRE(len);

	ret = vaccel_tf_saved_model_set_checkpoint(model, ptr, len);
	REQUIRE(ptr);
	REQUIRE(len);
	REQUIRE(ret == VACCEL_OK);

	ptr = read_file_from_dir(path, "variables/variables.index", &len);
	REQUIRE(ptr);
	REQUIRE(len);

	ret = vaccel_tf_saved_model_set_var_index(model, ptr, len);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_tf_saved_model_register(model);
	REQUIRE(ret == VACCEL_OK);

	vaccel_id_t model_id = vaccel_tf_saved_model_id(model);
	vaccel_info("Registered new resource: %ld", model_id);

	struct vaccel_session sess;
	ret = vaccel_sess_init(&sess, 0);
	REQUIRE(ret == VACCEL_OK);

	vaccel_info("Registering model %ld with session %u", model_id,
		    sess.session_id);

	ret = vaccel_sess_register(&sess, model->resource);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_sess_unregister(&sess, model->resource);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_tf_saved_model_destroy(model);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_sess_free(&sess);
	REQUIRE(ret == VACCEL_OK);

	free(model);
	free(path);
}

TEST_CASE("tf_saved_model_from_file", "[resources_tf_saved_model]")
{
	int ret;
	char *path = abs_path(SOURCE_ROOT, "examples/models/tf/lstm2/");

	struct vaccel_tf_saved_model *model = vaccel_tf_saved_model_new();
	REQUIRE(model);

	ret = vaccel_tf_saved_model_set_path(model, path);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_tf_saved_model_register(model);
	REQUIRE(ret == VACCEL_OK);

	vaccel_id_t model_id = vaccel_tf_saved_model_id(model);
	vaccel_info("Registered new resource: %ld", model_id);

	struct vaccel_session sess;
	ret = vaccel_sess_init(&sess, 0);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_sess_register(&sess, model->resource);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_sess_unregister(&sess, model->resource);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_tf_saved_model_destroy(model);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_sess_free(&sess);
	REQUIRE(ret == VACCEL_OK);

	free(model);
	free(path);
}
