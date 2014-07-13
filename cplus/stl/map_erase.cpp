#include <iostream>
#include <map>
using namespace std;

int main()
{
    typedef map<int, int>::iterator Iterator;
    map<int, int> array;
    for (size_t i = 0; i < 15; i++) {
        array[i] = i + 1;
    }
    Iterator itr;
    for(itr = array.begin(); itr != array.end(); ++itr) {
        cout << itr->first << " = " << itr->second << endl;
    }

    cout << "==========================" << endl;
    for(itr = array.begin(); itr != array.end();){
        if (itr->first % 2 == 1) {
            // erase掉itr时，itr失效
            array.erase(itr++);
        } else {
            ++itr;
        }
    }

    for(itr = array.begin(); itr != array.end(); ++itr) {
        cout << itr->first << " = " << itr->second << endl;
    }
    return 0;
}

