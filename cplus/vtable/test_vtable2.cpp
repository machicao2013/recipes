#include <iostream>
#include <stdint.h>
using namespace std;

class Base {
public:
    virtual void f() { cout << "Base::f" << endl; }
    uint32_t *p;
};
class Base2 {
public:
    virtual void f() { cout << "Base::f" << endl; }
    uint32_t p[1];
};

int main(int argc, const char *argv[])
{
    Base b;
    cout << "&b = \t\t" << &b << endl;
    cout << "&(b.p) = \t" << &(b.p) << endl;
    Base2 b2;
    cout << "&b2 = \t\t" << &b2 << endl;
    cout << "&(b2.p) = \t" << &(b2.p) << endl;
    intptr_t *p = (intptr_t *)&b;
    cout << p << endl;
    return 0;
}
