#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>

class A
{
private:
public:
    virtual void sing() = 0;
    virtual ~A()
    {
        std::cout << "Destructor invoked!" << '\n';
    }
};

class B : public A
{
public:
    virtual void sing()
    {
        std::cout << "Do re mi fa so la" << '\n';
    }
};

boost::shared_ptr<A> createA()
{
    boost::shared_ptr<A> p(new B());
    return p;
}

int main()
{
    typedef std::vector<boost::shared_ptr<A> > container_type;
    //typedef container_type::iterator iterator;

    container_type container;
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        container.push_back(createA());
    }

    //container.clear();  //cause shared_ptr removed, Destructor invoked
    container.erase(container.begin()); //cause shared_ptr removed, Destructor invoked

    std::cout << "The choir is gathered: \n";

/*
 *    iterator itr = container.begin();
 *
 *    while(itr != container.end())
 *    {
 *        (*itr)->sing();
 *        ++itr;
 *    }
 */

    return 0;
}

