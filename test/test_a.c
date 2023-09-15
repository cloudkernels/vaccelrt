// test_a.c:

#include "unity.h"
#include "a.h"

void setUp() {}
void tearDown() {}

void test_a(void) {
    int result = a();
    TEST_ASSERT_EQUAL(99, result);
}