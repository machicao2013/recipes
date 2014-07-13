#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace boost;

class demo_class
{
private:
    typedef function<void(int)> func_t;
    func_t func;
    int n;
public:
    demo_class(int i) : n(i)
    {}

    template <typename CallBack>
    void accept(CallBack f)
    {
        func = f;
    }

    void run()
    {
        func(n);
    }
};

class call_back_factory
{
private:

public:
    void call_back_func1(int i)
    {
        std::cout << "call back factory1: " << i * 2 << std::endl;
    }

    void call_back_func2(int i, int j)
    {
        std::cout << "call back factory2: " << i * j * 2 << std::endl;
    }

    virtual ~call_back_factory()
    {}
};

void call_back_func(int i)
{
    std::cout << "call back func: "  << i * 2 << std::endl;
}

int main()
{
    //for function
    demo_class dc(10);
    dc.accept(call_back_func);
    dc.run();

    //for member function
    call_back_factory cb;
    dc.accept(bind(&call_back_factory::call_back_func1, cb, _1));
    dc.run();
    dc.accept(bind(&call_back_factory::call_back_func2, cb, _1, 5));
    dc.run();

    return 0;
}

