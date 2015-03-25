#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
    }
    virtual void print()
    {
        cout << "Base print is invoked!" << endl;
    }
    virtual ~Base()
    {}
};

class Sub : public Base
{
public:
    Sub()
        // 虚表的构建发生在这个地方，因此会调用子类的print函数
    {
        print();
    }

    virtual void print()
    {
        cout << "Sub print is invoked!" << endl;
    }
};

int main()
{
    Base *p = new Sub();
    delete p;
    return 0;
}

