#include <limits>
#include <iostream>
using namespace std;

int main()
{
    cout << "max long: " << std::numeric_limits<long>::max() << endl;
    cout << "max unsigned long: " << std::numeric_limits<unsigned long>::max() << endl;
    cout << "max long long: " << std::numeric_limits<long long>::max() << endl;
    return 0;
}

