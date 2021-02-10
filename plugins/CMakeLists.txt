if (BUILD_PLUGIN_NOOP)
	add_subdirectory(noop)
endif(BUILD_PLUGIN_NOOP)

if (BUILD_PLUGIN_OCL)
	add_subdirectory(ocl)
endif(BUILD_PLUGIN_OCL)

if (BUILD_PLUGIN_VECTOR_ADD)
	add_subdirectory(vadd)
endif(BUILD_PLUGIN_VECTOR_ADD)

if (BUILD_PLUGIN_JETSON)
	add_subdirectory(jetson_inference)
endif(BUILD_PLUGIN_JETSON)

if (BUILD_PLUGIN_VIRTIO)
	add_subdirectory(virtio)
endif(BUILD_PLUGIN_VIRTIO)
