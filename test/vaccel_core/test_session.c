#include "unity.h"
#include "error.h"
#include "session.h"


static int fini(void) 
{
    return VACCEL_OK;
}

static int init(void) 
{
    return VACCEL_OK;
}


void setUp(void) {}


void tearDown(void) {}


void test_true_values(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}


void test_session_init_no_sess(void)
{
    TEST_ASSERT_EQUAL(vaccel_sess_init(NULL,0), VACCEL_EINVAL);
}


void test_session_init(void)
{
    static struct vaccel_session session;
    TEST_ASSERT_EQUAL(vaccel_sess_init(&session,0), VACCEL_OK);
}


void test_sess_update(void)
{
    static struct vaccel_session session;
    vaccel_sess_update(&session, 1);
    TEST_ASSERT_EQUAL(1, session.hint);
}


void test_sessions_boostrap(void)
{
    static struct vaccel_session session;
    int ret = sessions_bootstrap();
    TEST_ASSERT_EQUAL(VACCEL_OK, ret);
}