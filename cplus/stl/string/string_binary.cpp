#include <string>
#include <iostream>
#include <string.h>
using namespace std;

int main() {
    std::string str("test string");
    cout<<str<<"  "<<str.c_str()<<endl;
    cout<<str.size()<<endl;

    char* buf = new char[str.size()+1];
    memset(buf, 0, sizeof(buf));
    buf[1] = 'A';

    string test(buf, str.size());
    cout<<test<<"  "<<test.c_str()<<endl;
    cout<<test<<"  "<<test.data()<<endl;
    cout<<test.size()<<endl;
    cout<<test.length()<<endl;

    memcpy(buf, str.c_str(), str.size());

    test = string(buf, str.size());
    cout<<test<<"  "<<test.c_str()<<endl;
    cout<<test.size()<<endl;

    return 0;
}
