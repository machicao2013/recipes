#include <functional>
#include <iostream>
using namespace std;

size_t print(const char *str)
{
    cout << str << endl;
    return 0;
}

class Printer
{
private:

public:
    Printer()
    {}
    ~Printer()
    {}
    size_t operator()(const char *str)
    {
        cout << str << endl;
        return 0;
    }
};

int main()
{
    std::function<size_t(const char*)> print_func;
    print_func = print;
    print_func("hello world");

    Printer printer;
    print_func = printer;
    print_func("hello world");
    return 0;
}

