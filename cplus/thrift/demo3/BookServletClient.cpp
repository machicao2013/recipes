#include "gen-cpp/BookServlet.h"
#include <vector>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;
using namespace ::xunlei;

int main(int argc, const char *argv[])
{
    shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    xunlei::BookServletClient client(protocol);

    try {
        transport->open();
        std::vector<xunlei::Book_Info> books;
        for (int i = 0; i < 5; i++)
        {
            xunlei::Book_Info book;
            book.book_id = i + 1;
            book.book_name = "hah";
            book.book_author = "afds";
            book.book_price = 4.5f;
            book.book_publisher = "huazhong";
            books.push_back(book);
        }
        client.Sender(books);
        transport->close();
    } catch (TException &tx) {
        printf("ERROR: %s\n", tx.what());
    }
    return 0;
}
