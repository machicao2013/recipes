#include <iostream>
#include <vector>
using namespace std;

typedef bool Remove(int a);

void removeElementsFromVector(vector<int> &array, Remove remove)
{
    vector<int>::iterator itr;
    for( itr = array.begin(); itr != array.end();) {
        if (remove(*itr)) {
            cout << *itr << " was removed" << endl;
            itr = array.erase(itr);
        } else {
            cout << *itr << " was not removed" << endl;
            ++itr;
        }
    }
}

bool remove(int a)
{
    return ((a & 1) == 0);
}

int main()
{
    vector<int> array;
    for (size_t i = 0; i < 5; i++) {
        array.push_back(i);
    }
    vector<int>::iterator itr;
    //YOU CANNOT DO THIS
    //for(itr = array.begin(); itr != array.end(); ++itr) {
    //    cout << *itr << endl;
    //    array.erase(itr);
    //}
    //
    //YOU SHOULD DO THIS
    //for(itr = array.begin(); itr != array.end();) {
    //    cout << *itr << endl;
    //    array.erase(itr);
    //}

    removeElementsFromVector(array, remove);
    return 0;
}

