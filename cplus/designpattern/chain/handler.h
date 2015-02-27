#ifndef _HANDLER_H_
#define _HANDLER_H_

#include <boost/shared_ptr.hpp>

class Handler
{
protected:
    boost::shared_ptr<Handler> m_successor;
public:
    void set_successor(const boost::shared_ptr<Handler> &successor)
    {
        m_successor = successor;
    }

    void do_handler()
    {
        on_handler();
    }

    virtual void on_handler() = 0;
};


#endif /* end of include guard: _HANDLER_H_ */
