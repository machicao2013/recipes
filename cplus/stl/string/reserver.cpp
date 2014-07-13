#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string content;
    ifstream in("resize.cpp", ios::in | ios::ate);
    if (in) {
        std::ifstream::streampos filesize = in.tellg();
        content.reserve(filesize);
        in.seekg(0);
        std::string line = "";
        while (!in.eof()) {
            getline(in, line);
            content += line + "\n";
        }
    }
    cout << content;
    return 0;
}

