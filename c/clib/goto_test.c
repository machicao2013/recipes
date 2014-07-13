#include <stdio.h>

int main()
{
    int a = 2;
    if (a == 3) {
        printf("a = %d\n", a);
        goto end;
    }
end:
    printf("=======  end ======\n");
    return 0;
}

