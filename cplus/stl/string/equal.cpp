// equal algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::equal
#include <vector>       // std::vector

bool mypredicate (int i, int j) {
    return (i==j);
}

int main () {
    int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
    std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

    // using default comparison:
    if ( std::equal (myvector.begin(), myvector.end(), myints) )
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";

    //myvector[3]=81;                                 // myvector: 20 40 60 81 100
    int size = 20;
    while(size--)
        myvector.push_back(20);
    //myvector.pop_back();

    // using predicate comparison:
    if ( std::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";

    return 0;
}
