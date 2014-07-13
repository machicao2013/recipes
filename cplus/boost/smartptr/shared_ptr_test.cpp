#include <boost/shared_ptr.hpp>
#include <cassert>

class A
{
private:
    boost::shared_ptr<int> _no;
public:
    A(boost::shared_ptr<int> no) : _no(no)
    {
    }

    void value(int i)
    {
        *_no = i;
    }

    virtual ~A()
    {
    }
};

class B
{
private:
    boost::shared_ptr<int> _no;
public:
    B(boost::shared_ptr<int> no) : _no(no)
    {
    }

    int value() const
    {
        return *_no;
    }
    virtual ~B()
    {
    }
};

int main()
{
    boost::shared_ptr<int> temp(new int(14));
    A a(temp);
    B b(temp);
    a.value(28);
    assert(b.value() == 28);
    return 0;
}

