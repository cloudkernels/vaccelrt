#include <vaccel.h>
#include <backend.h>
#include <vaccel_ops.h>

void list_platforms(void);
extern "C" int vaccel_backend_initialize(struct vaccel_backend *backend)
{
	int ret;

	ret = initialize_backend(backend, "list_platforms");
	if (ret)
		return ret;

	ret = register_backend(backend);
	if (ret)
		return ret;

	ret = register_backend_function(backend, VACCEL_OCL,
			(void *)list_platforms);
	if (ret)
		goto unregister;

	return VACCEL_OK;

unregister:
	cleanup_backend(backend);
	return ret;
}

extern "C" int vaccel_backend_finalize(struct vaccel_backend *backend)
{
	//unregister_backend(backend);
	return VACCEL_OK;
}
