set(include_dirs ${CMAKE_SOURCE_DIR}/src)
message("Include directories: ${include_dirs}")
set(SOURCES
    vaccel.cpp
    ${include_dirs}/vaccel.h
    ${include_dirs}/backend.h)

# expose rpath for libraries when installing
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_library(vaccel-ocl SHARED ${SOURCES})
target_include_directories(vaccel-ocl PRIVATE ${include_dirs})
target_link_libraries(vaccel-ocl PRIVATE list)

# Setup make install
install(TARGETS vaccel-ocl DESTINATION "${lib_path}")
