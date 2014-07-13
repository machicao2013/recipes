namespace cpp xunlei

include "book.thrift"

service BookServlet {
    bool Sender(1: list<book.Book_Info> books),
    oneway void Sender2(1: list<book.Book_Info> books)
}
