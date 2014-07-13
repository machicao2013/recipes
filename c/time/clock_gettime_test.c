#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    struct timespec time1 = {0, 0};
    clock_gettime(CLOCK_REALTIME, &time1);
    printf("CLOCK_REALTIME: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);
    printf("%ld\n", time1.tv_sec/3600/24/365 + 1970);
    clock_gettime(CLOCK_MONOTONIC, &time1);
    printf("CLOCK_MONOTONIC: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    printf("CLOCK_PROCESS_CPUTIME_ID: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);
    printf("CLOCK_THREAD_CPUTIME_ID: %ld, %ld\n", time1.tv_sec, time1.tv_nsec);
    printf("\n%ld\n", time(NULL));
    sleep(1);
    return 0;
}
