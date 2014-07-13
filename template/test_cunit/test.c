#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int init_suit()
{
    return 0;
}

int cleanup_suit()
{
    return 0;
}

void test1()
{
    size_t a = -1;
    CU_ASSERT(a > 0);
    CU_ASSERT(sizeof(size_t) == sizeof(long));
}

void test2()
{
    CU_ASSERT(1);
}

int add_suite()
{
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("test parser", init_suit, cleanup_suit);
    if (NULL == pSuite)
        return 1;
    if (NULL == CU_add_test(pSuite, "test1", test1)) {
        return 1;
    }
    if (NULL == CU_add_test(pSuite, "test2", test2)) {
        return 1;
    }
    return 0;
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    if (add_suite() != 0) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}

