#include <iterator>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("data.txt");
    istream_iterator<int> itrBegin(in);
    istream_iterator<int> itrEnd;
    vector<int> datas(itrBegin, itrEnd);
    copy(datas.begin(), datas.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}

