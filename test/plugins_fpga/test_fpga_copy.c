#include "unity.h"
#include "error.h"
#include "fpga.h"
#include "noop.h"
#include "session.h"


static int fini(void) 
{
    return VACCEL_OK;
}

static int init(void) 
{
    return VACCEL_OK;
}


// Function to set up your test environment
void setUp(void){}

void tearDown(void){}



void test_vaccel_arraycopy_null(void)
{
    int input_array[] = {1, 2, 3, 4, 5};
    int output_array[] = {1, 2, 6, 4, 5};
    size_t len_input_array = sizeof(input_array) / sizeof(input_array[0]);

    TEST_ASSERT_EQUAL(vaccel_fpga_arraycopy(NULL, input_array, output_array, len_input_array), VACCEL_EINVAL);
}

void test_vaccel_arraycopy_valid(void)
{
    int ret;
    struct vaccel_session sess;
    int input_array[] = {1, 2, 3, 4, 5};
    int output_array[] = {1, 2, 6, 4, 5};
    size_t len_input_array = sizeof(input_array) / sizeof(input_array[0]);

    ret = vaccel_sess_init(&sess, 0);

    TEST_ASSERT_EQUAL(VACCEL_OK, ret);

    ret = vaccel_fpga_arraycopy(&sess, input_array, output_array, len_input_array);

    TEST_ASSERT_EQUAL(VACCEL_OK, vaccel_sess_free(&sess));
    TEST_ASSERT_NOT_EQUAL(VACCEL_ENOTSUP, ret);

    TEST_ASSERT_EQUAL_INT_ARRAY(input_array, output_array, len_input_array);

}



