#include <boost/scoped_ptr.hpp>
#include <string>
#include <iostream>

int main()
{
    boost::scoped_ptr<std::string> p(new std::string("Use scoped_ptr often"));

    if(p)
    {
        std::cout << *p << '\n';
    }

    size_t i = (*p).size();
    std::cout << "the size of *p is " << i << '\n';

    *p = "Acts just like a pointer";

    return 0;
}
