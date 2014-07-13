#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> array;
    for (int i = 0; i < 5; i++) {
        array.push_back(i);
    }

    for(auto i : array) {
        cout << i << endl;
    }
    return 0;
}

