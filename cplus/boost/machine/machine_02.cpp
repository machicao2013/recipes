/**
 * @file machine_02.cpp
 * @author maxingsong, maxingsong@xunlei.com
 * @version 0.1
 * @date 2014-09-08
 * @brief : http://blog.csdn.net/karl_max/article/details/2897859
 */

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <time.h>
using namespace std;

struct EvStartStop : boost::statechart::event<EvStartStop>
{};

struct EvReset : boost::statechart::event<EvReset>
{};

struct Active;

struct StopWatch : boost::statechart::state_machine<StopWatch, Active>
{};

struct Stopped;

struct Active : boost::statechart::simple_state<Active, StopWatch, Stopped>
{
private:
    double _elapsedTime;
public:
    typedef boost::statechart::transition<EvReset, Active> reactions;
    Active() : _elapsedTime(0.0)
    {}

    double ElapsedTime() const
    {
        return _elapsedTime;
    }

    double& ElapsedTime()
    {
        return _elapsedTime;
    }
};

struct Running : boost::statechart::simple_state<Running, Active>
{
private:
    time_t _startTime;
public:
    typedef boost::statechart::transition<EvStartStop, Stopped> reactions;

    Running() : _startTime( time(0) )
    {}

    ~Running()
    {
        context<Active>().ElapsedTime() += difftime(time(0), _startTime);
    }
};

struct Stopped : boost::statechart::simple_state<Stopped, Active>
{
    typedef boost::statechart::transition<EvStartStop, Running> reactions;
};

int main()
{
    StopWatch watcher;
    watcher.initiate();
    watcher.process_event(EvStartStop());
    watcher.process_event(EvStartStop());
    watcher.process_event(EvStartStop());
    watcher.process_event(EvReset());
    return 0;
}

