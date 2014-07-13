#include <boost/optional.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace boost;

optional<double> calc(int x)
{
    return optional<double>(x != 0, 1.0/x);
}

optional<double> sqrt_op(double x)
{
    return optional<double>(x >= 0, sqrt(x));
}

int main()
{
    optional<double> d = calc(10);
    if (d) {
        cout << *d << endl;
    }

    d = sqrt_op(9.0);
    if (d) {
        cout << *d << endl;
    }
    return 0;
}

