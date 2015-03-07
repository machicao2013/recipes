#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include <iostream>

class Receiver
{
public:
    Receiver()
    {}

    ~Receiver()
    {}

    void undo()
    {
        std::cout << "UndoCommand invoked!" << std::endl;
    }

    void redo()
    {
        std::cout << "RedoCommand invoked!" << std::endl;
    }

    void display()
    {
        std::cout << "DisplayCommand invoked!" << std::endl;
    }
};

#endif /* end of include guard: _RECEIVER_H_ */
