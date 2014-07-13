#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t a = 220, b = 120;
    int c = a + b;
    a = 300;
    printf("c = %d\n", c);
    printf("a = %d\n", a);
    return 0;
}

