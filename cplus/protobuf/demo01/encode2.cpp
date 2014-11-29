#include <iostream>
#include <cassert>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include "person.pb.h"

using namespace std;
using namespace google::protobuf;

void print_value(const Reflection *reflection, const Message &message, const FieldDescriptor *descriptor);

int main()
{
    Person *person = new Person();
    assert(!person->has_id());
    person->set_id(123);
    person->set_name("Bob");
    // person->set_email("bob@gmail.com");

    Message *message = person;

    cout << "person: " << message->ShortDebugString() << endl;

    const Reflection *reflection = message->GetReflection();
    const Descriptor *descriptor = message->GetDescriptor();
    const FieldDescriptor *filed_descriptor = NULL;
    int field_count = descriptor->field_count();
    cout << "field_count: " << field_count << endl;
    for(int i = 0; i < field_count; ++i) {
        filed_descriptor = descriptor->field(i);
        cout << "name: " << filed_descriptor->name() << endl;
        // cout << "value: " << reflection->GetString(*message, filed_descriptor) << endl;
        cout << "full name: " << filed_descriptor->full_name() << endl;
        cout << "is required: " << filed_descriptor->is_required() << endl;
        cout << "is optional: " << filed_descriptor->is_optional() << endl;
        cout << "is repeated: " << filed_descriptor->is_repeated() << endl;
        cout << "HasField: " << boolalpha << reflection->HasField(*message, filed_descriptor) << endl;
        print_value(reflection, *message, filed_descriptor);
        cout << "======================================" << endl;
    }
    return 0;
}

void print_value(const Reflection *reflection, const Message &message, const FieldDescriptor *descriptor)
{
    const EnumValueDescriptor *enum_descriptor = NULL;
    switch (descriptor->cpp_type()) {
    case FieldDescriptor::CPPTYPE_INT32:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetInt32(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_INT64:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetInt64(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_UINT32:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetUInt32(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_UINT64:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetUInt64(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_DOUBLE:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetDouble(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_FLOAT:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetFloat(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_BOOL:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetBool(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_ENUM:
        enum_descriptor = reflection->GetEnum(message, descriptor);
        cout << "type: " << descriptor->cpp_type_name() << "name: " <<
            enum_descriptor->name() << ", number: " <<
            enum_descriptor->number() << endl;
        break;
    case FieldDescriptor::CPPTYPE_STRING:
        cout << "type: " << descriptor->cpp_type_name() << ", value: " <<
            reflection->GetString(message, descriptor) << endl;
        break;
    case FieldDescriptor::CPPTYPE_MESSAGE:
        print_value(reflection, reflection->GetMessage(message, descriptor), descriptor);
        break;
    default:
        break;
    }
}
