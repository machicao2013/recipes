#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <iostream>
#include <fstream>

void save()
{
    std::ofstream file("archive.xml");
    boost::archive::xml_oarchive oa(file);
    std::string s = "Hello World!\n";
    oa & BOOST_SERIALIZATION_NVP(s);
}

void load()
{
    std::ifstream file("archive.xml");
    boost::archive::xml_iarchive ia(file);
    std::string s;
    ia & BOOST_SERIALIZATION_NVP(s);
    std::cout << s << std::endl;
}

int main()
{
    save();
    load();
    return 0;
}

