#include <stdio.h>

int main(int argc, const char *argv[])
{
    int a = 'A';
    char *p = (char *)&a;
    // printf打印的是该地址指向的值，即A
    printf(p);
    return 0;
}
