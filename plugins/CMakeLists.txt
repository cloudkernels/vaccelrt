set(plugin_src_includes ${CMAKE_SOURCE_DIR}/src/include)
set(plugin_bin_includes ${CMAKE_BINARY_DIR}/src/include)

if (BUILD_PLUGIN_NOOP)
	add_subdirectory(noop)
endif(BUILD_PLUGIN_NOOP)

if (BUILD_PLUGIN_EXEC)
	add_subdirectory(exec)
endif(BUILD_PLUGIN_EXEC)
