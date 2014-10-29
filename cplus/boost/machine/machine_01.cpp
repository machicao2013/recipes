#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>
using namespace std;

// init state
struct Greeting;

// define a state machine
struct Machine : boost::statechart::state_machine<Machine, Greeting>
{};

// define a state which belongs to machine Machine
struct Greeting : boost::statechart::simple_state<Greeting, Machine>
{
    Greeting()
    {
        cout << "construct Greeting" << endl;
    }

    ~Greeting()
    {
        cout << "destruct Greeting" << endl;
    }
};

int main()
{
    Machine machine;
    machine.initiate();
    return 0;
}

