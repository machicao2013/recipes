#include <iostream>
#include <list>
using namespace std;

int main()
{
    list<int> array;
    for (size_t i = 0; i < 5; i++) {
        array.push_back(i);
    }
    list<int>::iterator itr;
    for(itr = array.begin(); itr != array.end(); ++itr) {
        cout << *itr << endl;
        //array.erase(itr);  //error, look vector_erase
    }
    cout << "==================================" << endl;

    return 0;
}

