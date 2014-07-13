#include <iostream>
using namespace std;

class A
{
private:

public:
    A()
    {
        cout << "A constructor" << endl;
    }
    A(const A &a)
    {
        cout << "A copy constructor" << endl;
    }
    virtual ~A()
    {
        cout << "A destructor" << endl;
    }
};

class B
{
private:
    A &_a;
public:
    B(A &a) : _a(a)
    {

    }
    virtual ~B()
    {

    }
};

int main()
{
    A a;
    B b(a);
    return 0;
}
