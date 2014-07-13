#include <string>
#include <iostream>
#include <set>
#include <strings.h>
using namespace std;

class StringCaseComp
{
public:
    bool operator()(const string &lhs, const string &rhs)const
    {
        return strncasecmp(lhs.c_str(), rhs.c_str(), lhs.size());
    }
};

int main()
{
    set<string, StringCaseComp> sset;
    sset.insert("maxingsong");
    sset.insert("Maxingsong");
    sset.insert("MAxingsong");
    sset.insert("MaXingsong");
    sset.insert("MaxIngsong");
    sset.insert("MaxiNgsong");
    cout << sset.size() << endl;
    return 0;
}

