#include <boost/function.hpp>
#include <iostream>
#include <cassert>
using namespace boost;

int f(int a, int b)
{
    return a + b;
}

int main()
{
    function<int (int, int)> func;
    assert(!func);

    func = f;
    if (func)
    {
        std::cout << func(10, 20) << '\n';
    }

    func = 0;
    assert(func.empty());
    return 0;
}

