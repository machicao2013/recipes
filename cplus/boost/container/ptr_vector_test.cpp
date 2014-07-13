#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>
using namespace boost;
using namespace std;

class Foo
{
private:
    int m_data;
public:
    Foo()
    {
        m_data = 2;
        cout << "construct Foo" << endl;
    }

    ~Foo()
    {
        cout << "destory Foo" << endl;
    }

    int get_data()
    {
        return m_data;
    }
};

int main()
{
    ptr_vector<Foo> foo_vectors;
    for (int i = 0; i < 5; i++) {
        foo_vectors.push_back(new Foo());
    }
    cout << "size: " << foo_vectors.size() << endl;
    Foo &foo = foo_vectors.at(2);
    cout << foo.get_data() << endl;
    return 0;
}

