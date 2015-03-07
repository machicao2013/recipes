#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace boost;
using namespace std;

class A
{
private:

public:
    A()
    {}
    ~A()
    {}
    virtual void close()
    {
        cout << "A close invoked!" << endl;
    }
};

class B : public A
{
public:
    virtual void close()
    {
        cout << "B close invoked!" << endl;
    }
};

int main()
{
    shared_ptr<A> pa(new B, boost::bind(&A::close, _1));
    return 0;
}

