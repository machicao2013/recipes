#include <stdio.h>
#include <pthread.h>

__thread int value = 25;

void* worker1(void *args)
{
    (void)args;
    value++;
    printf("%d\n", value);
}

void* worker2(void *args)
{
    (void)args;
    value++;
    printf("%d\n", value);
}

int main()
{
    pthread_t pid1, pid2;
    pthread_create(&pid1, NULL, worker1, NULL);
    pthread_create(&pid2, NULL, worker2, NULL);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    return 0;
}

