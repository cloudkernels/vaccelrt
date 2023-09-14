#include "unity.h"
#include <vaccel.h>
#include <noop.h>


static int fini(void) {
    return VACCEL_OK;
}

static int init(void) {
    return VACCEL_OK;
}

// Function to set up your test environment
void setUp(void) {
    
}

void tearDown(void) {
}

void test_plugin_true(void) {
    TEST_ASSERT_EQUAL_INT(0,0);
}


void test_vaccel_noop_null(void){
    TEST_ASSERT_EQUAL(vaccel_noop(NULL), VACCEL_EINVAL);
}

void test_vaccel_noop(void){
    struct vaccel_session test_session;
    int ret = vaccel_sess_init(&test_session, 0);

    int new_ret = vaccel_noop(&test_session);

    printf("The integer is: %d\n",  new_ret);
}