#include <iostream>
using namespace std;

// http://www.cnblogs.com/skynet/p/3343726.html
//
class Base {
public:
    virtual void f() { cout << "Base::f" << endl; }
    virtual void g() { cout << "Base::g" << endl; }
    virtual void h() { cout << "Base::h" << endl; }
};

int main(int argc, const char *argv[])
{
    typedef void(*Fun)(void);
    Base b;
    Fun pFun = NULL;
    cout << "虚函数表地址：" << (intptr_t *)(&b) << endl;
    cout << "虚函数表--第一个函数地址：" << (intptr_t *)*(intptr_t *)(&b) << endl;

    pFun = (Fun)*((intptr_t *)*(intptr_t *)&b);
    pFun();
    pFun = (Fun)*((intptr_t *)*(intptr_t *)&b + 1);
    pFun();
    pFun = (Fun)*((intptr_t *)*(intptr_t *)&b + 2);
    pFun();
    return 0;
}
