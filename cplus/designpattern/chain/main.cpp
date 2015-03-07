#include "handler.h"
#include "concrete_handler.h"

int main()
{
    boost::shared_ptr<Handler> handler1(new ConcreteHandlerA());
    boost::shared_ptr<Handler> handler2(new ConcreteHandlerB());
    handler1->set_successor(handler2);
    handler1->do_handler();
    return 0;
}

