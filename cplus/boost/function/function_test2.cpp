#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace boost;

struct demo_class
{
    int add(int a, int b)
    {
        return a + b;
    }

    int operator()(int x) const
    {
        return x * x;
    }
};

int main()
{
    //method 1
    function<int(demo_class&, int, int)> func1;
    func1 = bind(&demo_class::add, _1, _2, _3);
    demo_class sc;
    std::cout << func1(sc, 10, 20) << '\n';

    //method 2
    function<int(int, int)> func2;
    func2 = bind(&demo_class::add, &sc, _1, _2);
    std::cout << func2(10, 20) << '\n';

    return 0;
}

