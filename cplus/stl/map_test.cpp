#include <map>
#include <string>
#include <iostream>
using namespace std;

namespace std
{
    bool operator<(const string &lhs, const string &rhs)
    {
        cout << "====================" << endl;
        return false;
    }
}

int main()
{
    map<string, int> smap;
    smap["hell"] = 1;
    smap["wordl"] = 2;
    cout << smap.size() << endl;
    return 0;
}

