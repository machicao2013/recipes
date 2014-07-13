#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <iostream>
#include <fstream>

void load()
{
    std::ifstream file("archive.txt");
    boost::archive::text_iarchive ia(file);
    std::string s;
    ia >> s;
    std::cout << s << std::endl;
}

int main()
{
    load();
    return 0;
}
