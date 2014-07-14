#include <iostream>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

void test(uint64_t llVal)
{
    int offset = 0;
    char buffer[sizeof(uint64_t)];
    *((uint32_t*)(buffer+offset)) = 0;
    *((uint32_t*)(buffer+offset)) = htonl(*((uint32_t*)((char*)&llVal+4)));
    *((uint32_t*)(buffer+offset+4)) = htonl(*((uint32_t*)((char*)&llVal)));
    memcpy(&llVal, buffer, sizeof(uint64_t));
    cout << llVal << endl;
}

int main()
{
    test(0);
    return 0;
}

