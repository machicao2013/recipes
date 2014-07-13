#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
using namespace std;

bool isprime(int value)
{
    if (value < 2) {
        return false;
    }

    bool result = true;
    int i = 2;
    for (i = 2; i < sqrt(value); i++) {
        if (value % i == 0) {
            result = false;
        }
    }
    return result;
}

bool getNextPrime(int value, int &result)
{
    if (value < 2) {
        return 2;
    }
    if (value == numeric_limits<int>::max()) {
        return false;
    }
    int i = ++value;
    while (true) {
        if (isprime(i)) {
            result = i;
            return true;
        }
        if (i == numeric_limits<int>::max()) {
            return false;
        }
        i++;
    }
    return false;
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " value" << endl;
        return 1;
    }
    if (isprime(atoi(argv[1]))) {
        cout << argv[1] << " is prime" << endl;
    }
    int result = 0;
    if (getNextPrime(atoi(argv[1]), result)) {
        cout << "the next prime is " << result << endl;
    } else {
        cout << "out of range" << endl;
    }
    return 0;
}

