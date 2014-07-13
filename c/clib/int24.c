#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT_24 0x7fffff
#define MIN_INT_24 -(MAX_INT_24 + 1)

void print0x(unsigned char *v, int size)
{
    int i;
    unsigned char *t = v + size - 1;
    for (i = 0; i < size; i++, t--) {
        printf("%.2X", *t);
    }
}

void test(int i)
{
    if (i > MAX_INT_24 || i < MIN_INT_24)
    {
        printf("error arguments\n");
        return;
    }
    char store[3];
    printf("i = %d, 0x%x, -i = %d, 0x%x\n", i, i, -i, -i);
    memcpy(store, &i, 3);
    int load;
    memcpy(&load, store, 3);
    printf("用3bytes存储整数-986638\n");
    printf("直接使用2次memcpy,此时不相等:%d,%d\n字节为:", i, load);
    print0x((unsigned char *)&load, 4);
    printf("\n左移:");
    load <<= 8;
    print0x((unsigned char *)&load, 4);
    printf("\n右移:");
    load >>= 8;
    print0x((unsigned char *)&load, 4);
    printf("\n相等");
    printf("%d,%d\n", i, load);
}

int main()
{
    int i = 0x20F1F2;
    test(i);
    test(-i);
    return 0;
}
