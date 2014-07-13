#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;

void display_person(tutorial::Person *person)
{
    cout << "Name: " << person->name() << endl;
    cout << "Id: " << person->id() << endl;
    cout << "Email: " << person->email() << endl;

    tutorial::Person::PhoneNumber *number;
    int size = person->phone_size();
    for (int i = 0; i < size; i++)
    {
        number = person->mutable_phone(i);
        cout << "\tNumber: " << number->number() << endl;
        cout << "\tType: " << number->type() << endl;
    }
}

int main(int argc, const char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return 1;
    }

    tutorial::AddressBook addressbook;

    {
        fstream in(argv[1], ios::in | ios::binary);
        if (!in)
        {
            cerr << "Failed to open " << argv[1] << endl;
            return 1;
        }
        else if(!addressbook.ParseFromIstream(&in))
        {
            cerr << "parse error" << endl;
        }
        in.close();
    }

    int size = addressbook.person_size();

    for (int i = 0; i < size; i++)
    {
        display_person(addressbook.mutable_person(i));
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
