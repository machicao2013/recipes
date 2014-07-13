#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vdata;
    vdata.reserve(1025);
    cout << vdata.size() << " : " << vdata.capacity() << endl;
    vdata.resize(5);
    cout << vdata.size() << " : " << vdata.capacity() << endl;
    vector<int>(vdata).swap(vdata);
    cout << vdata.size() << " : " << vdata.capacity() << endl;
    // string(str).swap(str);
    return 0;
}

