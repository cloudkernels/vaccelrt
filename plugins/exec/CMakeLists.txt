set(SOURCES vaccel.c ${plugin_bin_includes}/vaccel.h)
set_property(SOURCE ${plugin_bin_includes}/vaccel.h PROPERTY GENERATED 1)

add_library(vaccel-exec SHARED ${SOURCES})
target_include_directories(vaccel-exec PRIVATE ${plugin_src_includes} ${plugin_bin_includes})

add_dependencies(vaccel-exec vaccel)

# Setup make install
install(TARGETS vaccel-exec DESTINATION ${CMAKE_INSTALL_LIBDIR})
