#include <unistd.h>
#include <stdio.h>

int main()
{
    char *ptr = sbrk(0);
    printf("%p\n", ptr);
    ptr = sbrk(1);
    *(ptr + 1) = 'C';
    *(ptr + 2) = 'C';
    printf("%p\n", ptr);
    *(ptr + 4 * 1024 - 1) = 'C';
    return 0;
}

