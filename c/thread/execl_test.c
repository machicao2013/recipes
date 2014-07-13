#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int id = 1;
    char *cmdstring = "ls -l";
    if( -1 == execl("/bin/sh", "sh", "-c", cmdstring, (char *)0)) {
        printf("======%s\n", strerror(errno));
    }
    printf("%d\n", id);
    return 0;
}

