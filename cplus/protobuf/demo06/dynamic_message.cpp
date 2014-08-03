#include <iostream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::compiler;

int main()
{
    DiskSourceTree sourceTree;
    sourceTree.MapPath("", "./");
    Importer importer(&sourceTree, NULL);
    importer.Import("Foo.proto");

    const Descriptor *descriptor = importer.pool()->FindMessageTypeByName("Pair");
    cout << descriptor->DebugString();

    DynamicMessageFactory factory;
    const Message *message = factory.GetPrototype(descriptor);
    Message *pair = message->New();

    const Reflection *reflection = pair->GetReflection();

    const FieldDescriptor *field = NULL;
    field = descriptor->FindFieldByName("key");
    reflection->SetString(pair, field, "my key");
    field = descriptor->FindFieldByName("value");
    reflection->SetUInt32(pair, field, 1111);

    cout << pair->DebugString();

    delete pair;

    return 0;
}

