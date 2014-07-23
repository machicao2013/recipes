#include <iostream>
using namespace std;

void test_goto(int a)
{
    if (a == 0) {
        cout << a << endl;
        goto error;
    } else {
        cout << "====  " << a << endl;
    }
error:
    cout << "coming error" << endl;
}

int main()
{
    test_goto(0);
    cout << "=======================" << endl;
    test_goto(1);
    return 0;
}

