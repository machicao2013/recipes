/*
 * network_util_test.c - a small networking utils test
 *
 * Copyright (C) 2014 Xunlei CO. Ltd
 *
 * Author: maxingsong (maxingsong@xunlei.com)
 * Create: 2014-04-23 09:39:01
 *
 * History:
 * --------
 * 2014-04-23    v1.0    maxingsong (maxingsong@xunlei.com)
 *     1. Initial revision.
 */

#include "network_util.h"
#include <stdio.h>
#include <unistd.h>
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
    CU_ASSERT(1);
    char err_buf[256];
    memset(err_buf, 0, sizeof(err_buf));

    //test resolve
    char ip_buf[16] = {0};
    int ret = resolve(err_buf, "localhost", ip_buf);
    CU_ASSERT_EQUAL(ret, 0);
    printf("localhost: %s\n", ip_buf);
    memset(ip_buf, 0, sizeof(ip_buf));
    ret = resolve(err_buf, "baidu.com", ip_buf);
    CU_ASSERT_EQUAL(ret, 0);
    printf("baidu.com: %s\n", ip_buf);
    ret = resolve(err_buf, "b.u.com", ip_buf);
    CU_ASSERT_EQUAL(ret, -1);
    //test createTcpServer
    int fd = 0;
    fd = createTcpServer(err_buf, 9999, "127.0.0.1");
    CU_ASSERT(fd > 2);
    //test keepalive
    ret = setTcpKeepAlive(err_buf, fd);
    CU_ASSERT(ret == 0);
    ret = setSendBufferSize(err_buf, fd, 1024);
    CU_ASSERT(ret == 0);
    ret = setTcpNoDelay(err_buf, fd);
    CU_ASSERT(ret == 0);
    ret = setNonBlock(err_buf, fd);
    CU_ASSERT(ret == 0);
    ret = setReuseAddr(err_buf, fd);
    CU_ASSERT(ret == 0);
    if (fd > 2) {
        close(fd);
    }
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
    if (NULL == CU_add_test(pSuite, "test1", test1))
    {
        return 1;
    }
    if (NULL == CU_add_test(pSuite, "test2", test2))
    {
        return 1;
    }
    return 0;
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    if (add_suite() != 0)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}

