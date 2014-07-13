#include <fstream>
#include <iostream>
#include "person.pb.h"
using namespace std;

int main()
{
    Person person;
    std::fstream in("person.pb", std::ios::in | std::ios::binary);
    if (!person.ParseFromIstream(&in))
    {
        cerr << "Failed to parse person.pb." << endl;
        exit(1);
    }

    cout << "ID: " << person.id() << endl;
    cout << "name: " << person.name() << endl;
    if (person.has_email())
    {
        cout << "e-mail: " << person.email() << endl;
    }
    return 0;
}

