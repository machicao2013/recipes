#include <map>
#include <iostream>
using namespace std;

int main()
{
    map<int, int> rectangle;
    for (size_t i = 0; i < 4; i++) {
        rectangle[i] = i;
    }
    for(auto itr = rectangle.begin(); itr != rectangle.end(); ++itr) {
        cout << itr->first << '\t' << itr->second << endl;
    }

    return 0;
}

