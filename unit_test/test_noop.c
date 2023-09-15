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

void test_vaccel_noop_valid(void){
    struct vaccel_session sess;
    memset(&sess, 0, sizeof(struct vaccel_session));
    sess.session_id = 111;
    int result = vaccel_noop(&sess);
    TEST_ASSERT_EQUAL_INT(VACCEL_OK, result); // this will fail as its not getting the plugin operation.
}

// void test_vaccel_noop(void){
//     int ret = vaccel_sess_init(&session, 0);

//     int new_ret = vaccel_noop(&session);

//     printf("The integer is: %d\n",  new_ret);
// }