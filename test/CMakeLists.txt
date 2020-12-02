include(GoogleTest)

set(include_dirs ${CMAKE_SOURCE_DIR}/src)

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/tests.cpp")

# backend system unit test
set(backend_src "${PROJECT_SOURCE_DIR}/src/backend.c")
add_executable(
	backend_tests
	test_backend.cpp ${backend_src}
)
target_include_directories(
	backend_tests
	PRIVATE
	${GTEST_INCLUDE} ${include_dirs}
)
target_compile_options(backend_tests PUBLIC -Wall -Wextra -Werror -g -ggdb)
target_link_libraries("backend_tests" gtest_main dl)
gtest_add_tests(TARGET backend_tests)