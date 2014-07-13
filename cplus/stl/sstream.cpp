#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    string file = "data1.txt";
    ifstream in(file.c_str());
    if (!in) {
        cerr << "open file error" << endl;
        return 1;
    }
    string line;
    vector<int> datas;
    while (getline(in, line)) {
        istringstream iss(line);
        int data;
        while(iss >> data) {
            datas.push_back(data);
        }
    }
    in.close();
    copy(datas.begin(), datas.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}

