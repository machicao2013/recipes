#include <boost/noncopyable.hpp>
#include "lock.h"

class Counter : boost::noncopyable
{
private:
    int64_t _count;
    mutable MutexLock _lock;
public:
    Counter() : _count(0)
    {
    }

    int64_t value()
    {
        MutexLockGuard lock(_lock);
        return _count;
    }

    int64_t getAndIncrease()
    {
        MutexLockGuard lock(_lock);
        int64_t ret = _count++;
        return ret;
    }
    virtual ~Counter()
    {
    }
};

