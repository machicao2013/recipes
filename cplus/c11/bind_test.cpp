#include <functional>
#include <iostream>
using namespace std;

int Func(int x, int y)
{
    cout << x + y << endl;
    return 1000;
}

class Adder
{
private:

public:
    Adder()
    {}
    ~Adder()
    {}
    int add(int a, int b)
    {
        return (a + b);
    }
};

int main()
{
    function<int(int)> bf = bind(Func, 10, placeholders::_1);
    cout << bf(10) << endl;
    Adder adder;
    function<int(int, int)> bf2 = bind(&Adder::add, adder, placeholders::_1, placeholders::_2);
    cout << bf2(10, 10) << endl;
    return 0;
}

