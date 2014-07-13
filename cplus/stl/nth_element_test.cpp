#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <iterator>
using namespace std;

void generateRandom(size_t count, std::vector<int> &values)
{
    while (count) {
        values.push_back(random());
        count--;
    }
}

int main()
{
    std::vector<int> values;
    generateRandom(10, values);

    typedef vector<int>::iterator Iterator;
    copy(values.begin(), values.end(), ostream_iterator<int>(cout, "\n"));
    cout << endl << "========================" << endl;

    nth_element(values.begin(), values.begin() + 4, values.end());
    copy(values.begin(), values.end(), ostream_iterator<int>(cout, "\n"));
    cout << endl << "========================" << endl;
    return 0;
}

