#include <vector>
#include "tensorflow/core/public/session.h"

#include <api/ml.h>

using namespace tensorflow;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;

int ml_inference(struct vaccel_tf_protobuf_model *model,
		struct vaccel_tensor *in,
		struct vaccel_tensor *out, size_t out_nr)
{
	// Load model
	//
	
	// Set-up in&out tensors
	
	// Run inference
	return VACCEL_OK;
}
