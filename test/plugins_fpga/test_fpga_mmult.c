#include "unity.h"
#include "error.h"
#include "fpga.h"
#include "noop.h"
#include "session.h"
#include "genop.h"
#include "include/ops/fpga.h"
#include "ops/fpga.h"

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



void test_vaccel_mmult_null(void)
{
    float a[] = {1.2, 3.2, 3.0, 4.1, 5.7};
    float b[] = {1.1, 0.2, 6.1, 4.6, 5.2};
    size_t len_a = sizeof(a) / sizeof(a);
    float c[] = {0.1,0.1,0.1,0.1,0.1};

    TEST_ASSERT_EQUAL(vaccel_fpga_mmult(NULL, a, b, c, len_a), VACCEL_EINVAL);
}

void test_vaccel_mmult_valid(void)
{
    int ret;
    struct vaccel_session sess;
    
    float a[] = {1.2, 3.2, 3.0, 4.1, 5.7};
    float b[] = {1.1, 0.2, 6.1, 4.6, 5.2};
    size_t len_a = sizeof(a) / sizeof(a);
    float c[] = {0.1,0.1,0.1,0.1,0.1};

    ret = vaccel_sess_init(&sess, 0);

    TEST_ASSERT_EQUAL(VACCEL_OK, ret);

    ret = vaccel_fpga_mmult(&sess, a, b, c, len_a);

    TEST_ASSERT_EQUAL(VACCEL_OK, vaccel_sess_free(&sess));
    TEST_ASSERT_NOT_EQUAL(VACCEL_ENOTSUP, ret);

    float expected_c[] = {9.1, 9.1, 9.1, 9.1, 9.1}; // assume this is our output we want.

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_c, c, len_a);

}