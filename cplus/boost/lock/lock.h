#include <pthread.h>

class MutexLock
{
private:
    pthread_mutex_t _mutex;
public:
    MutexLock()
    {
        pthread_mutex_init(&_mutex, NULL);
    }

    ~MutexLock()
    {
        pthread_mutex_destroy(&_mutex);
    }

    bool lock()
    {
        return (pthread_mutex_lock(&_mutex) == 0);
    }

    bool unlock()
    {
        return (pthread_mutex_unlock(&_mutex) == 0);
    }
};

class MutexLockGuard
{
private:
    MutexLock& _lock;
public:
    explicit MutexLockGuard(MutexLock &lock) : _lock(lock)
    {
        _lock.lock();
    }
    ~MutexLockGuard()
    {
        _lock.unlock();
    }
};
