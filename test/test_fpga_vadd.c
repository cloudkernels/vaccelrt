#include "unity.h"
#include "error.h"
#include "fpga.h"
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

void test_vaccel_arraycopy_null(void)
{
    float A[] = {1, 2, 3, 4, 5};
    float B[] = {1, 2, 6, 4, 5};
    float C[] = {1, 2, 6, 4, 5};
    size_t len_A = sizeof(A) / sizeof(A[0]);
    size_t len_B = sizeof(B) / sizeof(B[0]);

    TEST_ASSERT_EQUAL(vaccel_fpga_vadd(NULL, A, B, C, len_A, len_B), VACCEL_EINVAL);
}

void test_vaccel_vadd_valid(void)
{
    int ret;
    struct vaccel_session sess;
    float A[] = {1, 2, 3, 4, 5};
    float B[] = {1, 2, 6, 4, 5};
    float C[] = {1, 2, 6, 4, 5};
    size_t len_A = sizeof(A) / sizeof(A[0]);
    size_t len_B = sizeof(B) / sizeof(B[0]);

    ret = vaccel_sess_init(&sess, 0);

    TEST_ASSERT_EQUAL(VACCEL_OK, ret);

    ret = vaccel_fpga_vadd(&sess, A, B, C, len_A, len_B);
    
    printf("The value of the integer is: %d\n", ret);

    TEST_ASSERT_EQUAL(VACCEL_OK, vaccel_sess_free(&sess));
    TEST_ASSERT_NOT_EQUAL(VACCEL_ENOTSUP, ret);


    printf("{");
    for (size_t i = 0; i < len_A; i++) {
        printf("%f", C[i]);
        if (i < len_A - 1) {
            printf(".");
        }
    }
    printf("}\n");

}