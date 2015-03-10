#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <stdint.h>
using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " filename" << endl;
        return 1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "open " << argv[1] << " failed" << endl;
        return 1;
    }
    map<string, uint32_t> counts;
    string line = "";
    string word = "";
    while (getline(in, line)) {
        istringstream iss(line);
        while (iss >> word) {
            if (counts.find(word) != counts.end()) {
                counts[word]++;
            } else {
                counts[word] = 1;
            }
        }
    }
    typedef map<string, uint32_t>::iterator Iterator;
    for(Iterator itr = counts.begin(); itr != counts.end(); ++itr) {
        cout << itr->first << "\t" << itr->second << endl;
    }
    in.close();
    return 0;
}

