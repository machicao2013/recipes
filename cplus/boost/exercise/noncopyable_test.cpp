#include <boost/noncopyable.hpp>

class Foo : private boost::noncopyable
{};

int main()
{
    Foo foo1;
    Foo foo2;
    // foo1(foo2); // error
    return 0;
}

