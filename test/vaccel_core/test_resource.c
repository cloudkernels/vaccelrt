#include "unity.h"
#include "mock_resources.h"
#include "resources.h"

// #include "id_pool.h"
// #include "error.h"
// #include "list.h"
// #include "log.h"
// #include "utils.h"
// #include "plugin.h"

// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <sys/stat.h>



// extern bool initialized = false;


void setUp(void)
{
    resources_bootstrap();

}

void tearDown(void) 
{
    resources_cleanup();
}

void test_resource_new(void)
{   
    static struct vaccel_resource test_res = {0};
    vaccel_resource_t mock_test_type;
    void *data;
    int (*mock_cleanup_resource)(void *);
    
    // Set up expectations for the mock function
    resource_new_ExpectAndReturn(&test_res, mock_test_type, data, mock_cleanup_resource, VACCEL_OK);
    
    // Call the function being tested
    int ret = resource_new(&test_res, mock_test_type, data, mock_cleanup_resource);
    
    // Check the return value
    TEST_ASSERT_EQUAL(VACCEL_OK, ret);
}


// void test_resource_new_null(void)
// {
//     resource_new_ExpectAndReturn(NULL, mock_test_type, data, mock_cleanup_resource, VACCEL_EINVAL);
//     int ret = resource_new(NULL, mock_test_type, data, mock_cleanup_resource);
//     TEST_ASSERT_EQUAL(VACCEL_EINVAL, ret);
// }

// void test_resource_new_not_init(void)
// {   
//     resource_new_ExpectAndReturn(NULL, mock_test_type, data, mock_cleanup_resource, VACCEL_EPERM);
//     int ret = resource_new(NULL, mock_test_type, data, mock_cleanup_resource);
//     TEST_ASSERT_EQUAL(VACCEL_EPERM, ret);
// }

// void test_resource_new_too_many_users(void)
// {   
//     resource_new_ExpectAndReturn(&test_res, mock_test_type, data, mock_cleanup_resource, VACCEL_EPERM);
//     int ret = resource_new(&test_res, mock_test_type, data, mock_cleanup_resource);
//     TEST_ASSERT_EQUAL(VACCEL_EPERM, ret);
// }
