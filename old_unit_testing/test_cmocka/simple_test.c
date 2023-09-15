#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "plugin.h"
#include "error.h"
#include "list.h"
#include "slog.h"
#include <stdbool.h>
#include <string.h>

static const char *pname = "mock_plugin";
static struct vaccel_plugin plugin = {0};
static struct vaccel_plugin_info pinfo = {0};

static int fini(void) {
    return VACCEL_OK;
}

static int init(void) {
    return VACCEL_OK;
}

static int setUp(void **state) {
    (void)state;  // Unused parameter
    plugin.info = &pinfo;
    pinfo.name = pname;
    list_init_entry(&plugin.entry);
    list_init_entry(&plugin.ops);
    pinfo.init = init;
    pinfo.fini = fini;

    plugins_bootstrap();
    return 0;
}

static int tearDown(void **state) {
    (void)state;  // Unused parameter
    plugins_shutdown();
    return 0;
}

static void test_plugin_true(void **state) {
    (void)state;  // Unused parameter
    assert_int_equal(0, 0);
}

static void test_plugin_null(void **state) {
    (void)state;  // Unused parameter
    assert_int_equal(register_plugin(NULL), VACCEL_EINVAL);
}

static void test_plugin_null_name(void **state) {
    (void)state;  // Unused parameter
    struct vaccel_plugin_info info = { 0 };
    struct vaccel_plugin test_plugin;
    test_plugin.info = &pinfo;
    test_plugin.entry.next = &(test_plugin.entry);
    test_plugin.entry.prev = &(test_plugin.entry);
    assert_int_equal(register_plugin(&test_plugin), VACCEL_EINVAL);
}

static void test_plugin_not_boostrapped(void **state) {
    (void)state;  // Unused parameter
    struct vaccel_plugin test_plugin = {};
    assert_int_not_equal(register_plugin(&test_plugin), VACCEL_EBACKEND);
}

static void test_plugin_init_values_all(void **state) {
    (void)state;  // Unused parameter
    assert_int_equal(register_plugin(&plugin), VACCEL_OK);
    assert_string_equal(plugin.info->name, "mock_plugin");
    assert_true(list_empty(&plugin.ops));
}

static void test_plugin_exists(void **state) {
    (void)state;  // Unused parameter
    register_plugin(&plugin);

    // here we call the function first and then we call assert.
    // each assert here setsup and tearsdown.

    assert_int_equal(register_plugin(&plugin), VACCEL_EEXISTS);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_plugin_true),
        cmocka_unit_test(test_plugin_null),
        cmocka_unit_test(test_plugin_null_name),
        cmocka_unit_test(test_plugin_not_boostrapped),
        cmocka_unit_test(test_plugin_init_values_all),
        cmocka_unit_test(test_plugin_exists),
    };

    return cmocka_run_group_tests(tests, setUp, tearDown);
}
