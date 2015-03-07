#include <stdio.h>

int main()
{
    char c = 'a';
    printf("%c, sizeof(char)=%d, sizeof('a')=%d\n", c, sizeof(c), sizeof('a'));
    return 0;
}

