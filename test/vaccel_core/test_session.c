#include "unity.h"
#include "session.h"
#include "plugin.h"
#include "log.h"
#include "utils.h"
#include "id_pool.h"
#define MAX_VACCEL_SESSIONS 1024

struct vaccel_session test_sess = {0};

extern struct {
	/* true if the sessions subsystem has been initialized */
	bool initialized;

	/* Available session ids */
	id_pool_t ids;

	/* Active sessions */
	struct vaccel_session *running_sessions[MAX_VACCEL_SESSIONS];
} sessions;


static void mock_sessions_bootstrap(void) 
{
    sessions.initialized = true;
}

static void mock_sessions_cleanup(void) 
{
    sessions.initialized = false;
}


// void setUp(void) 
// {   

//     int result = sessions_bootstrap();


//     if (result != VACCEL_OK) {
//         TEST_FAIL_MESSAGE("Failed to initialize sessions subsystem");
//     }
// }

// void tearDown(void) 
// {
//     int result = sessions_cleanup();

//     if (result != VACCEL_OK) {
//         TEST_FAIL_MESSAGE("Failed to clean up sessions subsystem");
//     }
// }

void test_vaccel_sess_register_null(void) 
{   
    int ret = vaccel_sess_register(NULL, NULL);
    TEST_ASSERT_EQUAL(VACCEL_EINVAL, ret);
}

void test_vaccel_sess_init(void) 
{   
    int ret = vaccel_sess_init(&test_sess, 0);
    TEST_ASSERT_EQUAL(VACCEL_OK, ret);
}

void test_vaccel_sess_init_null(void)
{   
    int ret = vaccel_sess_init(NULL, 0);
    TEST_ASSERT_EQUAL(VACCEL_EINVAL, ret);
}

void test_vaccel_sess_init_not_init(void)
{   
    mock_sessions_cleanup();
    int ret = vaccel_sess_init(&test_sess, 0);
    TEST_ASSERT_EQUAL(VACCEL_ESESS, ret);
    mock_sessions_bootstrap();
}

void test_vaccel_sess_update(void)
{
    int ret = vaccel_sess_update(&test_sess, 0);
    TEST_ASSERT_EQUAL(VACCEL_OK, ret);
}

void test_vaccel_sess_update_null(void)
{
    int ret = vaccel_sess_update(NULL, 0);
    TEST_ASSERT_EQUAL(VACCEL_EINVAL, ret);
}

void test_vaccel_sess_update_not_init(void)
{   
    mock_sessions_cleanup();
    int ret = vaccel_sess_update(&test_sess, 0);
    TEST_ASSERT_EQUAL(VACCEL_ESESS, ret);
    mock_sessions_bootstrap();
}

void test_vaccel_free_null(void)
{
    int ret = vaccel_sess_free(NULL);
    TEST_ASSERT_EQUAL(VACCEL_EINVAL, ret);
}

void test_vaccel_free_not_init(void)
{   
    mock_sessions_cleanup();
    int ret = vaccel_sess_free(&test_sess);
    TEST_ASSERT_EQUAL(VACCEL_ESESS, ret);
    mock_sessions_bootstrap();
}


void test_vaccel_free(void)
{
    int ret = vaccel_sess_free(&test_sess);
    TEST_ASSERT_EQUAL(VACCEL_OK, ret);
}