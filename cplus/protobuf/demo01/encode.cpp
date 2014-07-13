#include <fstream>
#include <cassert>
#include "person.pb.h"

int main()
{
    Person person;
    assert(!person.has_id());
    person.set_id(123);
    person.set_name("Bob");
    person.set_email("bob@gmail.com");

    std::fstream out("person.pb", std::ios::out | std::ios::binary | std::ios::trunc);
    person.SerializeToOstream(&out);
    out.close();
    return 0;
}

