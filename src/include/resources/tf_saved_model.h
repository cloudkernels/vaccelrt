// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vaccel_file.h>
#include <vaccel_id.h>

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct vaccel_resource;

/* A struct representing a TensorFlow saved model
 *
 * A TensorFlow saved model consists of:
 * 1) A protobuf file containing the model
 * 2) A set of checkpoints containing values for the variables of the
 *    model.
 */
struct vaccel_tf_saved_model {
	/* Underlying resource object */
	struct vaccel_resource *resource;

	/* The path of the saved model in disk */
	const char *path;

	/* Model file */
	struct vaccel_file model;

	/* Checkpoint file */
	struct vaccel_file checkpoint;

	/* Variables index file */
	struct vaccel_file var_index;

	/* Placeholder for plugin-specific data */
	void *priv;
};

struct vaccel_tf_saved_model *vaccel_tf_saved_model_new(void);

int vaccel_tf_saved_model_set_path(struct vaccel_tf_saved_model *model,
				   const char *path);

const char *vaccel_tf_saved_model_get_path(struct vaccel_tf_saved_model *model);

int vaccel_tf_saved_model_set_model(struct vaccel_tf_saved_model *model,
				    const uint8_t *ptr, size_t len);

const uint8_t *
vaccel_tf_saved_model_get_model(struct vaccel_tf_saved_model *model,
				size_t *len);

int vaccel_tf_saved_model_set_checkpoint(struct vaccel_tf_saved_model *model,
					 const uint8_t *ptr, size_t len);

const uint8_t *
vaccel_tf_saved_model_get_checkpoint(struct vaccel_tf_saved_model *model,
				     size_t *len);

int vaccel_tf_saved_model_set_var_index(struct vaccel_tf_saved_model *model,
					const uint8_t *ptr, size_t len);

const uint8_t *
vaccel_tf_saved_model_get_var_index(struct vaccel_tf_saved_model *model,
				    size_t *len);

int vaccel_tf_saved_model_register(struct vaccel_tf_saved_model *model);

int vaccel_tf_saved_model_destroy(struct vaccel_tf_saved_model *model);

vaccel_id_t vaccel_tf_saved_model_id(const struct vaccel_tf_saved_model *model);

vaccel_id_t
vaccel_tf_saved_model_remote_id(const struct vaccel_tf_saved_model *model);

#ifdef __cplusplus
}
#endif
