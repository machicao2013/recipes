#include <stdio.h>

int main()
{
#ifdef __linux__
    printf("define linux\n");
#endif
    printf("%s\n", "end");
    return 0;
}

