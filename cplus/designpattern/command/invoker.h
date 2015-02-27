#ifndef _INVOKER_H_
#define _INVOKER_H_

#include "command.h"

#include <vector>
#include <boost/shared_ptr.hpp>

class Invoker
{
private:
    std::vector<boost::shared_ptr<DocumentCommand> > m_commands;
    typedef std::vector<boost::shared_ptr<DocumentCommand> >::iterator Iterator;

public:
    Invoker()
    {}

    ~Invoker()
    {}

    void add_command(const boost::shared_ptr<DocumentCommand> &command)
    {
        m_commands.push_back(command);
    }

    void invoke()
    {
        for(Iterator itr = m_commands.begin(); itr != m_commands.end(); ++itr) {
            (*itr)->on_command();
        }
    }
};


#endif /* end of include guard: _INVOKER_H_ */
