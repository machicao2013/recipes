#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    vector<int> vdata;
    for (int i = 0; i < 20; i++) {
        vdata.push_back(i);
    }
    vector<int> vcopy;
    copy(vdata.begin() + vdata.size()/2, vdata.end(), back_inserter(vcopy));
    copy(vcopy.begin(), vcopy.end(), ostream_iterator<int>(cout, "\t"));
    return 0;
}

