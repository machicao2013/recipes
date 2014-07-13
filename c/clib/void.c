#include <stdio.h>

// #pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic warning "-Wpointer-arith"

int main()
{
    char ch[] = "12345678910";
    void *p = ch;
    // printf("sizeof(void) = %lu\n", sizeof(void));  // error
    printf("sizeof(void*) = %lu\n", sizeof(void*));
    printf("sizeof(int*) = %lu\n", sizeof(int*));
    printf("sizeof(char*) = %lu\n", sizeof(char*));
    printf("%p\n", p);
    printf("%p\n", (p + 1));  // warn
    printf("%p\n", (p + 2));  // warn
    printf("%p\n", (p + 3));  // warn
    // error
    // *p = '2';
    // *(p + 1) = '3';

    printf("%s\n", ch);
    return 0;
}

