#include <iostream>
using namespace std;

class const_member
{
private:
    int value;
public:
    const_member(int value)
    {
        this->value = value;
    }
    virtual ~const_member()
    {

    }
    int getValue() const
    {
        return value;
    }
};

int main()
{
    const_member member(10);
    cout << member.getValue() << endl;
    const const_member m(20);
    const_member n = m;
    cout << n.getValue() << endl;
    return 0;
}

