#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " data" << endl;
        return 1;
    }
    cout << atoi(argv[1]) << endl;
    return 0;
}
