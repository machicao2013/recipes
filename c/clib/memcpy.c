#include <stdio.h>

void* my_memcpy(void *dest, void *src, size_t n)
{
    if (NULL == src || NULL == dest || n == 0)
    {
        return dest;
    }

    char *pdest = (char *)dest;
    char *psrc = (char *)src;

    size_t i = 0;
    if(src >= dest)
    {
        for (i = 0; i < n; i++)
        {
            *(pdest + i) = *(psrc + i);
        }
    }
    else
    {
        for (i = n - 1; i >= 0; i--)
        {
            *(pdest + i) = *(psrc + i);
        }
    }
    return dest;
}

void* my_memcpy1(void *dst, const void *src, size_t n)
{
    if (NULL == src || NULL == dst || n <= 0)
    {
        return dst;
    }
    size_t i;
    for (i = 0; i < n; i++)
    {
        ((char *)dst)[i] = ((char*)src)[i];
    }
    return dst;
}

int main()
{
    char ch[30] = "abcdefghijklmnopq";
    /*
     *printf("%s\n", ch);
     *char *ptr = &ch + 5;
     *my_memcpy(ptr, ch, 10);
     *printf("%s\n", ptr);
     */

    char ch2[20] = "9523fsajdlfasjldfad";
    my_memcpy1(ch, ch2, 20);
    printf("%s\n", ch);
    return 0;
}

