#include <stdio.h>
#include "log.h"

void test1()
{
    log_debug("debug info");
    log_notice("%s", "notice info");
    log_error("%s", "error info");
}

int main()
{
    if(0 != log_open("usage.log")) {
        printf("%s\n", "log open error");
        return -1;
    }
    test1();
    log_close();
    return 0;
}

