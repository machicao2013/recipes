#include "command.h"
#include "invoker.h"
#include "receiver.h"

int main()
{
    boost::shared_ptr<Receiver> receiver(new Receiver());
    boost::shared_ptr<DocumentCommand> redo(new RedoCommand());
    boost::shared_ptr<DocumentCommand> undo(new UndoCommand());
    boost::shared_ptr<DocumentCommand> display(new DisplayCommand());

    redo->set_receiver(receiver);
    undo->set_receiver(receiver);
    display->set_receiver(receiver);

    Invoker invoker;
    invoker.add_command(redo);
    invoker.add_command(undo);
    invoker.add_command(display);

    invoker.invoke();

    return 0;
}

