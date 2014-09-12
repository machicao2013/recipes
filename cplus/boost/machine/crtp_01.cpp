/**
 * @file crtp_01.cpp
 * @author maxingsong, maxingsong@xunlei.com
 * @version
 * @date 2014-09-08
 * @brief http://www.suninf.net/curiously-recurring-template-pattern/
 */

#include <iostream>
using namespace std;

template <typename T>
class Counter
{
private:
    T* m_pointee;
    static int m_nCounter;
public:
    Counter()
    {
        ++m_nCounter;
    }
    Counter(const Counter&)
    {
        ++m_nCounter;
    }
    ~Counter()
    {
        --m_nCounter;
    }
    static int Get()
    {
        return m_nCounter;
    }
};

template <typename T>
int Counter<T>::m_nCounter = 0;

class CounterInstance : public Counter<CounterInstance>
{};

int main()
{
    CounterInstance a[3];
    (void)a;
    cout << CounterInstance::Get() << endl;
    return 0;
}
