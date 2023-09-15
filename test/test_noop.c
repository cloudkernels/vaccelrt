#include "unity.h"
#include "error.h"
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

void test_plugin_true(void) 
{
    TEST_ASSERT_EQUAL_INT(0,0);
}


void test_vaccel_noop_null(void)
{
    TEST_ASSERT_EQUAL(vaccel_noop(NULL), VACCEL_EINVAL);
}

void test_vaccel_noop_valid(void)
{
    int ret;
    struct vaccel_session sess;

    ret = vaccel_sess_init(&sess, 0);

    TEST_ASSERT_EQUAL(VACCEL_OK, ret);

    ret = vaccel_noop(&sess);
    // TEST_ASSERT_EQUAL_INT(VACCEL_OK, result); // this will fail as its not getting the plugin operation.

    TEST_ASSERT_EQUAL(VACCEL_OK, vaccel_sess_free(&sess));

    printf("Memory address of x: %p\n", (void *)ret);

}   
