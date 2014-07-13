#include <pthread.h>
#include <string.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    char buffer[50];
    sprintf(buffer, "%ld", pthread_self());
    printf("%s\n", buffer);
    return 0;
}
