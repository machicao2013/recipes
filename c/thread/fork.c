#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char *p;
    p = malloc(10);//p is virtual address
    strcpy(p, "ccc");
    printf("p=%p %s\n", p, p);
    if (fork() == 0)
    {
        strcpy(p, "ccc3333");
        printf("child p=%p %s\n", p,p);
        sleep(10);
        printf("child p=%p %s\n", p,p);
    }
    else
    {
        sleep(3);
        strcpy(p, "ccc444");
        printf("father p=%p %s\n", p,p);
    }
    free(p);
    return 0;
}
