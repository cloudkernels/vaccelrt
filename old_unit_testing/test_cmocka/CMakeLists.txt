add_cmocka_test(simple_test
                SOURCES simple_test.c
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${CMOCKA_LIBRARIES}")
add_cmocka_test_environment(simple_test)
target_include_directories(simple_test PUBLIC "${CMOCKA_INCLUDE_DIRS}")