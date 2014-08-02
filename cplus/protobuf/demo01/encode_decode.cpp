#include <sstream>
#include <assert.h>
#include "person.pb.h"
using namespace std;

int main()
{
    std::string temp = "";
    Person person;
    assert(!person.has_id());
    person.set_id(123);
    person.set_name("maxingsong");
    person.set_email("hello@gmail.com");

    person.SerializeToString(&temp);

    person.ParseFromString(temp);
    assert(person.id() == 123);
    assert(person.name() == "maxingsong");
    assert(person.has_email());
    assert(person.email() == "hello@gmail.com");

    return 0;
}

