#include <vector>

class Observer
{
public:
    Observer();
    virtual ~Observer();
    virtual void update() = 0;

private:
    /* data */
};

class Observable
{
public:
    Observable ();
    void register(Observer *x);
    void unregister(Observer *x);

    void nofifyObservers()
    {
        std::vector<Observer>::iterator itr;
        for(itr = _observers.begin(); itr != _observers.end(); ++itr)
        {
            itr->update();
        }
    }
    virtual ~Observable ();

private:
    std::vector<Observer *> _observers;
};
