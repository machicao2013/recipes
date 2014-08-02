#include "Foo.pb.h"
#include <assert.h>
#include <string>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
using namespace std;

int main()
{
    string data;  // will store a serialized version of the message
    {
        // Create a message and serialize it.
        Foo foo;
        foo.set_text("Hello World!");
        foo.add_numbers(1);
        foo.add_numbers(5);
        foo.add_numbers(42);

        foo.SerializeToString(&data);
    }

    {
        // parse the serialized message and check that it contains the correct data
        Foo foo;
        foo.ParseFromString(data);

        assert(foo.text() == "Hello World!");
        assert(foo.numbers_size() == 3);
        assert(foo.numbers(0) == 1);
        assert(foo.numbers(1) == 5);
        assert(foo.numbers(2) == 42);
    }

    {
        using ::google::protobuf::FieldDescriptor;

        // Same as the last block, but do it dynamically via the Message reflection interface
        ::google::protobuf::Message *foo = new Foo();
        const ::google::protobuf::Descriptor *descriptor = foo->GetDescriptor();

        // Get the descriptos for the fields we're interested in and verify their types
        const ::google::protobuf::FieldDescriptor *text_field = descriptor->FindFieldByName("text");
        assert(text_field != NULL);
        assert(text_field->type() == FieldDescriptor::TYPE_STRING);
        assert(text_field->label() == FieldDescriptor::LABEL_OPTIONAL);

        const ::google::protobuf::FieldDescriptor *numbers_field = descriptor->FindFieldByName("numbers");
        assert(numbers_field != NULL);
        assert(numbers_field->type() == FieldDescriptor::TYPE_INT32);
        assert(numbers_field->label() == FieldDescriptor::LABEL_REPEATED);

        // parse the message
        foo->ParseFromString(data);

        // Use the reflection interface to examine the contents
        const ::google::protobuf::Reflection *reflection = foo->GetReflection();
        assert(reflection->GetString(*foo, text_field) == "Hello World!");
        assert(reflection->FieldSize(*foo, numbers_field) == 3);
        assert(reflection->GetRepeatedInt32(*foo, numbers_field, 0) == 1);
        assert(reflection->GetRepeatedInt32(*foo, numbers_field, 1) == 5);
        assert(reflection->GetRepeatedInt32(*foo, numbers_field, 2) == 42);

        if(NULL != foo) {
            delete foo;
            foo = NULL;
        }
    }
    return 0;
}

