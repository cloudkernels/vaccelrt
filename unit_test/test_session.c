#include "unity.h"
#include "noop.h"
#include "plugin.h"
#include "error.h"
#include "list.h"
#include "slog.h"
#include <stdbool.h>
#include <string.h>
#include "log.h"
#include "vaccel_ops.h"
#include "id_pool.h"
#include "session.h"
#include "resources.h"
#include "utils.h"
#include "vaccel.h"



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


