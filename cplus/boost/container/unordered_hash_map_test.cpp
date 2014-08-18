#include<string>
#include<iostream>

#include<boost/unordered_map.hpp>

using namespace std;

struct person
{
    string name;
    int age;

    person(string name, int age)
    {
        this->name =  name;
        this->age = age;
    }

    bool operator== (const person& p) const
    {
        return name==p.name && age==p.age;
    }
};

size_t hash_value(const person& p)
{
    cout << "hash_value was invoked!" << endl;
    size_t seed = 0;
    boost::hash_combine(seed, boost::hash_value(p.name));
    boost::hash_combine(seed, boost::hash_value(p.age));
    return seed;
}

int main()
{
    typedef boost::unordered_map<person,int> umap;
    umap m;
    person p1("Tom1",20);
    person p2("Tom2",22);
    person p3("Tom3",22);
    person p4("Tom4",23);
    person p5("Tom5",24);
    m.insert(umap::value_type(p3, 100));
    m.insert(umap::value_type(p4, 100));
    m.insert(umap::value_type(p5, 100));
    m.insert(umap::value_type(p1, 100));
    m.insert(umap::value_type(p2, 100));

    for(umap::iterator iter = m.begin(); iter != m.end(); iter++)
    {
        cout<<iter->first.name<<"\t"<<iter->first.age<<endl;
    }

    cout << "=============================" << endl;
    boost::unordered_map<std::string, int> smap;
    smap["hello"] = 20;
    smap["world"] = 30;
    for(boost::unordered_map<std::string, int>::iterator iter = smap.begin();
        iter != smap.end(); ++iter) {
        cout << iter->first << "\t" << iter->second << endl;
    }
    return 0;
}


