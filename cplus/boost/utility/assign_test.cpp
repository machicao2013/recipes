#include <boost/assign.hpp>
#include <string>
using namespace std;

int main()
{
    using namespace boost::assign;
    std::vector<int> v;
    v += 1, 2, 3, 4, 5, 6*6;

    std::set<string> s;
    s += "cpp", "java", "c#", "python";

    std::map<int, string> m;
    m += make_pair(1, "one"), make_pair(2, "two");
    return 0;
}

