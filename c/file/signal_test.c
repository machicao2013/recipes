#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void sigHandler(int sig)
{
    sleep(5);
    printf("signal output\n");
}

int main()
{
    if (signal(SIGINT, sigHandler) == SIG_ERR) {
        exit(0);
    }
    sleep(2);
    printf("main output\n");
    /* sleep(5); */
    return 0;
}

