#include <iostream>
#include <stdint.h>
using namespace std;

class class_Test
{
private:
    int *p;
    uint32_t data;
    std::string str;
public:
    class_Test()
    {}
    ~class_Test()
    {}
    std::string getStr()
    {
        return str;
    }
    uint32_t getData()
    {
        return data;
    }
    int *getP()
    {
        return p;
    }
};

int main()
{
    class_Test test;
    cout << test.getData() << endl;
    cout << "==========================" << endl;
    cout << test.getP() << endl;
    cout << "==========================" << endl;
    cout << test.getStr() << endl;
    cout << "==========================" << endl;
    return 0;
}

