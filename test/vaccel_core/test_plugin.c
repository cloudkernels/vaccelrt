#include "unity.h"
#include "plugin.h"
#include "error.h"
#include "list.h"
#include "slog.h"
#include <stdbool.h>
#include <string.h>


static const char *pname = "mock_plugin";
static struct vaccel_plugin plugin = {0};
static struct vaccel_plugin_info pinfo = {0};

static int fini(void) 
{
    return VACCEL_OK;
}

static int init(void) 
{
    return VACCEL_OK;
}

// Function to set up your test environment
void setUp(void) 
{
    plugin.info = &pinfo;
    pinfo.name = pname;
    list_init_entry(&plugin.entry);
    list_init_entry(&plugin.ops);
    pinfo.init = init;
    pinfo.fini = fini;

    plugins_bootstrap();
}


// Function to tear down your test environment
void tearDown(void) 
{
    plugins_shutdown();
}

void test_plugin_null(void) 
{
    TEST_ASSERT_EQUAL(register_plugin(NULL), VACCEL_EINVAL);
}


void test_plugin_null_name(void)
{
    struct vaccel_plugin_info info = { 0 };
	struct vaccel_plugin plugin;
	plugin.info = &pinfo;
	
    plugin.entry.next = &(plugin.entry);
    plugin.entry.prev = &(plugin.entry);

    TEST_ASSERT_EQUAL(register_plugin(&plugin), VACCEL_EINVAL);
}

void test_plugin_not_boostrapped(void)
{
    struct vaccel_plugin plugin = {};
    
    TEST_ASSERT_NOT_EQUAL(register_plugin(&plugin), VACCEL_EBACKEND);
}

void test_plugin_init_values_all(void)
{
    TEST_ASSERT_EQUAL(register_plugin(&plugin), VACCEL_OK);
    TEST_ASSERT_EQUAL(strcmp(plugin.info->name, "mock_plugin"), 0);
    TEST_ASSERT_TRUE(list_empty(&plugin.ops));

}

void test_plugin_exists(void)
{
    TEST_ASSERT_EQUAL(register_plugin(&plugin), VACCEL_OK);
    TEST_ASSERT_EQUAL(register_plugin(&plugin), VACCEL_EEXISTS);
}

void test_register_plugin(void)
{
    TEST_ASSERT_EQUAL(VACCEL_OK, register_plugin(&plugin));
}

void test_unregister_plugin(void)
{   
    register_plugin(&plugin);
    TEST_ASSERT_EQUAL(VACCEL_OK, unregister_plugin(&plugin));
}


// void test_register_plugin_function(void)
// {   

//     TEST_ASSERT_EQUAL(VACCEL_OK, register_plugin_function(&plugin_op));
// }

void test_register_plugin_function_invalid_inputs(void) 
{
    struct vaccel_op invalid_op = {0};

    TEST_ASSERT_EQUAL(VACCEL_EINVAL, register_plugin_function(NULL));
    TEST_ASSERT_EQUAL(VACCEL_EINVAL, register_plugin_function(&invalid_op));
}

void test_register_plugin_function_valid_input(void) 
{

    struct vaccel_op valid_op = 
    {
        .type = 1,                     
        .func = vaccel_noop, 
        .owner = &plugin,                  
        .plugin_entry = LIST_ENTRY_INIT(valid_op.plugin_entry), 
        .func_entry = LIST_ENTRY_INIT(valid_op.func_entry)
    };

    TEST_ASSERT_EQUAL(VACCEL_OK, register_plugin_function(&valid_op));

}


// void test_get_available_plugins(void) {

//     get_available_plugins(VACCEL_NO_OP);

//     /// I need more plugins I think before I start this one.
// }

// // void test_get_plugin_op_invalid_op_type(void) 
// // {
// //     TEST_ASSERT_EQUAL(NULL, get_plugin_op(VACCEL_FUNCTIONS_NR, 0));
// // }


// // void test_get_plugin_op_no_plugins(void) 
// // {   

// //     TEST_ASSERT_EQUAL(NULL, get_plugin_op(VACCEL_PLUGIN_GENERIC, 0));

// // }


// // void test_get_plugin_op_no_hint(void) {

// //     TEST_ASSERT_EQUAL(NULL, (VACCEL_NO_OP, 0));

// // }
