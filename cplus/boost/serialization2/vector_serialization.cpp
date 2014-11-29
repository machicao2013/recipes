// reference: <a href="http://zh.highscore.de/cpp/boost/serialization.html">reference</a>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

void save()
{
    std::ofstream file("archive.xml");
    boost::archive::xml_oarchive oa(file);
    float array[] = {34.2, 78.1, 22.221, 1.0, -910.88};
    // std::vector<float> V1(array, array+5);
    boost::shared_ptr<std::vector<float> > ptr(new std::vector<float>(array, array + 5));
    // oa & BOOST_SERIALIZATION_NVP(V1);
    oa & BOOST_SERIALIZATION_NVP(ptr);
}

void load()
{
    std::ifstream file("archive.xml");
    boost::archive::xml_iarchive ia(file);

    // std::vector<float> V1;
    // boost::shared_ptr<std::vector<float> > ptr(new std::vector<float>());
    boost::shared_ptr<std::vector<float> > ptr;
    // ia >> BOOST_SERIALIZATION_NVP(V1); // No size/range needed
    ia >> BOOST_SERIALIZATION_NVP(ptr);

    std::ostream_iterator<float> oi(std::cout, " ");
    // std::copy(V1.begin(), V1.end(), oi);
    std::copy(ptr->begin(), ptr->end(), oi);
    std::cout << std::endl;
}

int main()
{
    save();
    load();
    return 0;
}

