#include <boost/typeof/typeof.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace boost;

#define VOID(A) (void)(A)

vector<int> func()
{
    vector<int> v(10);
    return v;
}

int main()
{
    BOOST_TYPEOF(2 * 0.3) x = 2 * 0.3;  // x --> double
    BOOST_AUTO(y, 2 + 3);               // y --> int

    BOOST_AUTO(a, new double[20]);     // a --> &(dobule *)
    BOOST_AUTO(p, make_pair(1, "string"));      // p --> pair<int, string>

    BOOST_AUTO(v, func());                        // vv --> vector<int> (*p)()

    VOID(x);
    VOID(y);
    VOID(a);
    VOID(p);
    VOID(v);
    return 0;
}

