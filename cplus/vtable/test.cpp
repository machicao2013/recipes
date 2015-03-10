#include <iostream>
using namespace std;

class Base1
{
public:
    int a[10];
};

class Base2
{
public:
    int *a;
};

class Base3
{
private:
    int a;
public:
    virtual ~Base3()
    {}
};

int main(int argc, const char *argv[])
{
    Base1 b1;
    Base2 b2;
    cout << "&b1: " << &b1 << endl;
    cout << "&(b1.a): " << &(b1.a) << endl;
    cout << "b1.a: " << b1.a << endl;
    cout << "&b2: " << &b2 << endl;
    cout << "&(b2.a): " << &(b2.a) << endl;
    cout << "b2.a: " << b2.a << endl;
    cout << sizeof(Base3) << endl;
    return 0;
}
