if (BUILD_PLUGIN_NOOP)
	add_subdirectory(noop)
endif(BUILD_PLUGIN_NOOP)

if (BUILD_PLUGIN_EXEC)
	add_subdirectory(exec)
endif(BUILD_PLUGIN_EXEC)

if (BUILD_PLUGIN_MBENCH)
	add_subdirectory(mbench)
endif(BUILD_PLUGIN_MBENCH)
