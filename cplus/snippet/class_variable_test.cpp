#include <iostream>
using namespace std;

class class_variable_test
{
private:
    int variable1;
    int variable2;
public:
    class_variable_test()
    {}

    virtual ~class_variable_test()
    {}

    int get_variable1()
    {
        return variable1;
    }

    int get_variable2()
    {
        return variable2;
    }
};

int main()
{
    class_variable_test obj;
    cout << obj.get_variable1() << endl;
    cout << obj.get_variable2() << endl;
    return 0;
}

