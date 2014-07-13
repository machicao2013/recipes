// resizing string
#include <iostream>
#include <string>

int main ()
{
    std::string str ("I like to code in C");
    std::cout << str << '\n';

    unsigned sz = str.size();
    std::cout << "size: " << str.size() << "\t data: " << str << "\tend" << std::endl;
    str.resize(28);
    std::cout << "size: " << str.size() << "\t data: " << str << "\tend" << std::endl;
    sz = str.size();

    str.resize (sz+2,'+');
    std::cout << "size: " << str.size() << "\t data: " << str << "\tend" << std::endl;

    str.resize (14);
    str[6] = '\0';
    std::cout << "size: " << str.size() << "\t data: " << str << "\tend" << std::endl;
    return 0;
}
