// SPDX-License-Identifier: Apache-2.0

/*
 * TensorFlow Inference Test
 *
 * The code below performs a TensorFlow inference test.
 *
 */

#include <catch.hpp>
#include <utils.hpp>

#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <vaccel.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

TEST_CASE("tf_inference", "[ops_tf]")
{
	struct vaccel_session vsess;
	struct vaccel_tf_saved_model model;
	struct vaccel_tf_status status;
	int ret;
	char *model_path = abs_path(SOURCE_ROOT, "examples/models/tf/lstm2");

	vsess.session_id = 0;
	vsess.resources = nullptr;
	vsess.hint = 0;
	vsess.priv = nullptr;

	model.resource = nullptr;
	model.path = nullptr;
	model.priv = nullptr;

	ret = vaccel_tf_saved_model_set_path(&model, model_path);
	REQUIRE(ret == VACCEL_OK);
	REQUIRE(model.resource == NULL);
	REQUIRE_FALSE(model.path == nullptr);
	REQUIRE(model.priv == nullptr);
	INFO("model.path: " << model.path);

	ret = vaccel_tf_saved_model_register(&model);
	REQUIRE(ret == VACCEL_OK);
	REQUIRE_FALSE(model.path == nullptr);
	REQUIRE(model.priv == nullptr);
	REQUIRE_FALSE(model.resource == NULL);

	ret = vaccel_sess_init(&vsess, 0);
	REQUIRE(ret == VACCEL_OK);
	REQUIRE_FALSE(vsess.session_id == 0);
	REQUIRE_FALSE(vsess.resources == nullptr);
	REQUIRE(vsess.hint == 0);
	REQUIRE(vsess.priv == nullptr);

	printf("Initialized vAccel session %u\n", vsess.session_id);

	ret = vaccel_sess_register(&vsess, model.resource);
	REQUIRE(ret == VACCEL_OK);
	REQUIRE_FALSE(vsess.session_id == 0);
	REQUIRE(vsess.hint == 0);
	REQUIRE_FALSE(
		list_empty(&vsess.resources->registered[model.resource->type]));
	REQUIRE(vsess.priv == nullptr);

	ret = vaccel_tf_session_load(&vsess, &model, &status);
	REQUIRE(ret == VACCEL_OK);

	if (status.message != nullptr)
		free((char *)status.message);

	struct vaccel_tf_buffer run_options = { nullptr, 0 };
	const char *in_node_name = "serving_default_input_1";

	struct vaccel_tf_node in_node = { const_cast<char *>(in_node_name), 0 };

	int64_t dims[] = { 1, 30 };
	float data[30];
	for (float &i : data)
		i = 1.00;

	struct vaccel_tf_tensor *in =
		vaccel_tf_tensor_new(2, dims, VACCEL_TF_FLOAT);
	REQUIRE(in);

	in->data = data;
	in->size = sizeof(float) * 30;

	const char *out_node_name = "StatefulPartitionedCall";

	struct vaccel_tf_node out_node = { const_cast<char *>(out_node_name),
					   0 };
	struct vaccel_tf_tensor *out;

	ret = vaccel_tf_session_run(&vsess, &model, &run_options, &in_node, &in,
				    1, &out_node, &out, 1, &status);
	REQUIRE(ret == VACCEL_OK);

	if (status.message != nullptr)
		free((char *)status.message);

	printf("Success!\n");
	printf("Output tensor => type:%u nr_dims:%u\n", out->data_type,
	       out->nr_dims);
	for (int i = 0; i < out->nr_dims; ++i)
		printf("dim[%d]: %" PRId64 "\n", i, out->dims[i]);

	printf("Result Tensor :\n");
	auto *offsets = (float *)out->data;
	for (unsigned int i = 0; i < min(10, out->size / sizeof(float)); ++i)
		printf("%f\n", offsets[i]);

	ret = vaccel_tf_tensor_destroy(in);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_tf_tensor_destroy(out);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_tf_session_delete(&vsess, &model, &status);
	REQUIRE(ret == VACCEL_OK);

	if (status.message != nullptr)
		free((char *)status.message);

	ret = vaccel_sess_unregister(&vsess, model.resource);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_sess_free(&vsess);
	REQUIRE(ret == VACCEL_OK);

	ret = vaccel_tf_saved_model_destroy(&model);
	REQUIRE(ret == VACCEL_OK);

	free(model_path);
}
