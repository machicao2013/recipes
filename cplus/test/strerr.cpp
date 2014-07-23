#include <string.h>
#include <errno.h>
#include <iostream>
using namespace std;

int main()
{
    cout  << "errno(11): " << strerror(11) << endl;
    return 0;
}

