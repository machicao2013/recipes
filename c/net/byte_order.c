#include <stdio.h>

void print_bytes(void *bytes, size_t len) {
    unsigned char *p = bytes;
    int i = 0;
    printf("0x");
    for (i = 0; i < len; i++)
    {
        printf("%02x", *p);
        p++;
    }
    printf("\n");
}

int main()
{
    int data = 0x12345678;
    print_bytes(&data, sizeof(data));
    int a = 0x01;
    char *pa = (char *)&a;
    if (*pa == 0x01)
    {
        printf("little endian\n");
    }
    else
    {
        printf("big endian\n");
    }
    return 0;
}

