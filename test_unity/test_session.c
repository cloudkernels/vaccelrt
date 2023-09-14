#include "unity.h"
#include <vaccel.h>
#include <session.h>


// static struct vaccel_session test_session;
// static struct vaccel_resource test_resource;


static int fini(void) {
    return VACCEL_OK;
}

static int init(void) {
    return VACCEL_OK;
}

static struct vaccel_session session;

void setUp(void) {
}

void tearDown(void) {
}

void test_true_values(void){
    TEST_ASSERT_EQUAL(true, true);
}

void test_session_init_no_sess(void){
    TEST_ASSERT_EQUAL(vaccel_sess_init(NULL,0), VACCEL_EINVAL);
}

void test_session_init(void){
    TEST_ASSERT_EQUAL(vaccel_sess_init(&session,0), VACCEL_OK);
}

void test_sess_update(void){
    vaccel_sess_update(&session, 1);
    TEST_ASSERT_EQUAL(1, session.hint);
}

void test_sessions_boostrap(void){
    int ret = sessions_bootstrap();
    TEST_ASSERT_EQUAL(VACCEL_OK, ret);
}


