#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/assign.hpp>
using namespace std;
using namespace boost::assign;

struct square {
    void operator()(int &x)
    {
        x = x * x;
    }
};

int main()
{

    vector<int> v = (list_of(1), 2, 3, 4, 5);
    for_each(v.begin(), v.end(), square());
    for(int x : v) {
        cout << x << endl;
    }
    return 0;
}

