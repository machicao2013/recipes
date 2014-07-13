#include <stdio.h>

int sum(int a, int b)
{
    printf("&a = %p\n", &a);
    printf("&b = %p\n", &b);
    return 0;
}

int main()
{
    //入栈的顺序c,b,a
    int a = 10;
    int b = 20;
    int c = 30;
    printf("&a = %p\n", &a);
    printf("&b = %p\n", &b);
    printf("&c = %p\n", &c);
    printf("=====================\n");
    sum(a, b);
    return 0;
}

