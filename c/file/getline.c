#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input("getline.c");
    string line;
    int data1, data2;
    while (getline(input, line)) {
        istringstream iss(line);
        // cout << line << endl;
        iss >> data1 >> data2;
        if (iss) {
            cout << data1 << '\t' << data2 << endl;
        } else {
            cout << "invalid line" << endl;
        }
    }
    input.close();
    return 0;
}

