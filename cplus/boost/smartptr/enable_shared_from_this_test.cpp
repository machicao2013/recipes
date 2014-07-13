#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

class A;

void do_stuff(boost::shared_ptr<A>)
{
    std::cout << "do something" << '\n';
}

class A : public boost::enable_shared_from_this<A>
{
public:
    void call_do_stuff()
    {
        do_stuff(shared_from_this());
    }
};

int main()
{
    boost::shared_ptr<A> p(new A());
    p->call_do_stuff();
    return 0;
}

