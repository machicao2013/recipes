#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main()
{
    const char *p = "abcdefghijklmnopqrst";
    char buffer[5];
    snprintf(buffer, 5, "%s", p);
    cout << strlen(buffer) << endl;
    return 0;
}

