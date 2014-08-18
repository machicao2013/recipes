/// @file codex.cpp
/// @author maxingsong, maxingsong@xunlei.com
/// @version 0.1
/// @date 2014-07-25
/// @brief ported from:
/// http://cxwangyi.blogspot.com/2010/06/google-protocol-buffers-proto.html
/// http://cxwangyi.wordpress.com/category/programming-languages/protocol-buffer/

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/tokenizer.h>
#include <google/protobuf/compiler/parser.h>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
using namespace google::protobuf;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;
using namespace std;

//-----------------------------------------------------------------------------
//// Parsing given .proto file for Descriptor of the given message (by
//// name).  The returned message descriptor can be used with a
//// DynamicMessageFactory in order to create prototype message and
//// mutable messages.  For example:
///*
//DynamicMessageFactory factory;
//const Message* prototype_msg = factory.GetPrototype(message_descriptor);
//const Message* mutable_msg = prototype_msg->New();
//*/
////-----------------------------------------------------------------------------
void GetMessageTypeFromProtoFile(const string& proto_filename, FileDescriptorProto* file_desc_proto)
{

    FILE* proto_file = fopen(proto_filename.c_str(), "r");
    {
        if (proto_file == NULL) {
            //LOG(FATAL) << "Cannot open .proto file: " << proto_filename;
            cerr << "Cannot open .proto file: " << proto_filename;
        }

        FileInputStream proto_input_stream(fileno(proto_file));
        Tokenizer tokenizer(&proto_input_stream, NULL);
        Parser parser;
        if (!parser.Parse(&tokenizer, file_desc_proto)) {
            //LOG(FATAL) << "Cannot parse .proto file:" << proto_filename;
            cerr << "Cannot parse .proto file:" << proto_filename;

        }
    }
    fclose(proto_file);

    // Here we walk around a bug in protocol buffers that
    // |Parser::Parse| does not set name (.proto filename) in
    // file_desc_proto.
    if (!file_desc_proto->has_name()) {
        file_desc_proto->set_name(proto_filename);
    }
}

//-----------------------------------------------------------------------------
//// Print contents of a record file with following format:
////
////   { <int record_size> <KeyValuePair> }
////
//// where KeyValuePair is a proto message defined in mpimr.proto, and
//// consists of two string fields: key and value, where key will be
//// printed as a text string, and value will be parsed into a proto
//// message given as |message_descriptor|.
////-----------------------------------------------------------------------------
void PrintDataFile(const string& data_filename, const FileDescriptorProto& file_desc_proto, const string& message_name)
{
    const uint32_t kMaxRecieveBufferSize = 32 * 1024 * 1024;  // 32MB
    static char buffer[kMaxRecieveBufferSize];

    ifstream input_stream(data_filename.c_str());
    if (!input_stream.is_open()) {
        //LOG(FATAL) << "Cannot open data file: " << data_filename;
        cerr << "Cannot open data file: " << data_filename;
    }

    google::protobuf::DescriptorPool pool;
    const google::protobuf::FileDescriptor* file_desc = pool.BuildFile(file_desc_proto);
    if (file_desc == NULL) {
        //LOG(FATAL) << "Cannot get file descriptor from file descriptor" << file_desc_proto.DebugString();
        cerr << "Cannot get file descriptor from file descriptor" << file_desc_proto.DebugString();
    }

    const google::protobuf::Descriptor* message_desc = file_desc->FindMessageTypeByName(message_name);
    if (message_desc == NULL) {
        //LOG(FATAL) << "Cannot get message descriptor of message: " << message_name;
        cerr << "Cannot get message descriptor of message: " << message_name;
    }

    google::protobuf::DynamicMessageFactory factory;
    const google::protobuf::Message* prototype_msg = factory.GetPrototype(message_desc);
    if (prototype_msg == NULL) {
        //LOG(FATAL) << "Cannot create prototype message from message descriptor";
        cerr << "Cannot create prototype message from message descriptor";
    }
    google::protobuf::Message* mutable_msg = prototype_msg->New();
    if (mutable_msg == NULL) {
        //LOG(FATAL) << "Failed in prototype_msg->New(); to create mutable message";
        cerr << "Failed in prototype_msg->New(); to create mutable message";
    }

    uint32_t proto_msg_size; // uint32 is the type used in reocrd files.
    for (;;) {
        input_stream.read((char*)&proto_msg_size, sizeof(proto_msg_size));

        if (proto_msg_size > kMaxRecieveBufferSize) {
            //LOG(FATAL) << "Failed to read a proto message with size = " << proto_msg_size << ", which is larger than kMaxRecieveBufferSize ("
            //<< kMaxRecieveBufferSize << ")." << "You can modify kMaxRecieveBufferSize defined in " << __FILE__;
            cerr << "Failed to read a proto message with size = " << proto_msg_size << ", which is larger than kMaxRecieveBufferSize ("
                << kMaxRecieveBufferSize << ")." << "You can modify kMaxRecieveBufferSize defined in " << __FILE__;
        }

        input_stream.read(buffer, proto_msg_size);
        if (!input_stream)
            break;

        if (!mutable_msg->ParseFromArray(buffer, proto_msg_size)) {
            // LOG(FATAL) << "Failed to parse value in KeyValuePair:" << pair.value();
            // cerr << "Failed to parse value in KeyValuePair:" << pair.value();
        }

        cout << mutable_msg->DebugString();
    }

    delete mutable_msg;
}

int main(int argc, char** argv)
{
    string proto_filename, message_name;
    vector<string> data_filenames;
    FileDescriptorProto file_desc_proto;

    // ParseCmdLine(argc, argv, &proto_filename, &message_name, &data_filenames);
    GetMessageTypeFromProtoFile(proto_filename, &file_desc_proto);

    for (size_t i = 0; i < data_filenames.size(); ++i) {
        PrintDataFile(data_filenames[i], file_desc_proto, message_name);
    }

    return 0;
}

