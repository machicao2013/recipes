#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct in_addr addr;

    if (argc != 2) {
        fprintf(stderr, "%s <dotted-address>\n", argv[0]);
        //exit(EXIT_FAILURE);
        return -1;
    }

    if (inet_aton(argv[1], &addr) == 0) {
        perror("inet_aton error\n");
        return -1;
    }

    printf("%d\n", addr);
    printf("%s\n", inet_ntoa(addr));
    return 0;
}

