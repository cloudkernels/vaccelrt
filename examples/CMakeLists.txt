set(include_dirs ${CMAKE_SOURCE_DIR}/src)

add_executable(classify classification.c)
target_include_directories(classify PRIVATE ${include_dirs})
target_link_libraries(classify PRIVATE vaccel dl)

add_executable(list_platforms list_platforms.c)
target_include_directories(list_platforms PRIVATE ${include_dirs})
target_link_libraries(list_platforms PRIVATE vaccel dl list)


# Install the examples
install(TARGETS classify DESTINATION "${bin_path}")
