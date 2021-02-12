#ifndef __VACCEL_ML_H__
#define __VACCEL_ML_H__

enum vaccel_data_type {
	VACCEL_FLOAT = 0,
	VACCEL_DFLOAT,
	VACCEL_INT8,
	VACCEL_INT16,
	VACCEL_INT32,
	VACCEL_INT64,
};

struct vaccel_tensor_shape {
	/* Array holding the dimensions of a tensor */
	size_t *dims;

	/* Number of dimensions */
	size_t nr_dims;
};

struct vaccel_tensor {
	/* Buffer holding the actual data and its length */
	void *data;
	size_t len;

	/* Shape of the tensor */
	struct vaccel_tensor_shape shape;

	/* Data type of the tensor elements */
	enum vaccel_data_type data_type;

	/* Name of the tensor in Graph */
	const char *name;
};

struct vaccel_tf_protobuf_model {
	/* raw bytes of the model to load */
	void *model;

	size_t size;

	/* Name of input tensor */
	const char *in_tensor_name;

	/* Name of output tensor */
	const char *out_tensor_names;
	size_t nr_out_tensors; 

	enum vaccel_data_type type;
};

int vaccel_ml_inference(struct vaccel_session *sess,
		struct vaccel_tf_protobuf_model *model,
		struct vaccel_tensor *in, size_t in_nr,
		struct vaccel_tensor *out, size_t out_nr);

int vaccel_load_ml_model(struct vaccel_session *session, char *buff, size_t len);

#endif /* __VACCEL_ML_H__ */
