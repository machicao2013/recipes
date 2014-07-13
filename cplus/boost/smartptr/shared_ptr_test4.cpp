#include <boost/shared_ptr.hpp>
#include <iostream>
using namespace std;
using namespace boost;

class shared
{
private:
    shared_ptr<int> _p;
public:
    shared(shared_ptr<int> p) : _p(p)
    {
    }
    ~shared()
    {
    }
    void print()
    {
        cout << "count: " << _p.use_count() << ", v=" << *_p << endl;
    }
};

void print_func(shared_ptr<int> p)
{
    cout << "count: " << p.use_count() << ", v=" << *p << endl;
}

int main()
{
    shared_ptr<int> p(new int(10));
    shared s1(p), s2(p);

    s1.print();
    s2.print();

    *p = 20;
    print_func(p);

    s1.print();
    return 0;
}

