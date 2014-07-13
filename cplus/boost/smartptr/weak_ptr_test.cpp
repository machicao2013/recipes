#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <cassert>

int main()
{
    boost::shared_ptr<int> sp(new int(10));
    assert(sp.use_count() == 1);

    boost::weak_ptr<int> wp(sp);
    assert(wp.use_count() == 1);

    if (!wp.expired())
    {
        boost::shared_ptr<int> sp2 = wp.lock();
        *sp2 = 100;
        assert(wp.use_count() == 2);
    }

    assert(wp.use_count() == 1);
    sp.reset();
    assert(wp.expired());
    assert(!wp.lock());
    return 0;
}

