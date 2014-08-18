#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

int main()
{
    shared_ptr<int> sa(new int(5));
    shared_ptr<int> sb = sa;
    sa.reset(new int(10));
    cout << *sa << "\t" << *sb << endl;
    return 0;
}

