#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

volatile bool start = 0;

# glibc为每个线程分配内存作为缓存
void* thread_run( void* )
{

    while(1)
    {
        if(start)
        {
            cout << "Thread malloc" << endl;
            // 第一次分配内存的时候会给该线程分配64M的Thread Local Memory
            char *buf = new char[1024];
            start = 0;
        }
        sleep(1);
    }
}

int main()
{
    pthread_t th;
    int a = 0;

    cin >> a;
    cout << "================" << endl;
    cin >> a;
    cout << "================" << endl;
    pthread_create(&th, 0, thread_run, 0);

    while(cin >> a)
    {
        start  = 1;
    }

    return 0;
}
