set(SOURCES vaccel.c ${plugin_bin_includes}/vaccel.h)
set_property(SOURCE ${plugin_bin_includes}/vaccel.h PROPERTY GENERATED 1)

add_library(vaccel-noop SHARED ${SOURCES})
target_include_directories(vaccel-noop PRIVATE ${plugin_src_includes} ${plugin_bin_includes})

add_dependencies(vaccel-noop vaccel)

# Setup make install
install(TARGETS vaccel-noop DESTINATION ${CMAKE_INSTALL_LIBDIR})
