#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "receiver.h"

#include <boost/shared_ptr.hpp>

class DocumentCommand
{
protected:
    boost::shared_ptr<Receiver> m_receiver;
public:
    void set_receiver(const boost::shared_ptr<Receiver> &receiver)
    {
        m_receiver = receiver;
    }

    virtual void on_command() = 0;
};

class UndoCommand : public DocumentCommand
{
    virtual void on_command()
    {
        m_receiver->undo();
    }
};

class RedoCommand : public DocumentCommand
{
    virtual void on_command()
    {
        m_receiver->redo();
    }
};

class DisplayCommand : public DocumentCommand
{
    virtual void on_command()
    {
        m_receiver->display();
    }
};

#endif /* end of include guard: _COMMAND_H_ */


