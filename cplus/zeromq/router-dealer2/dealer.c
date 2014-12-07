#include "zhelpers.h"
#include <pthread.h>
#define NBR_WORKERS 10

int main (void)
{
    void *context = zmq_ctx_new ();
    void *worker = zmq_socket (context, ZMQ_DEALER);
    s_set_id (worker);          //  Set a printable identity
    zmq_connect (worker, "tcp://localhost:5671");

    int total = 0;
    while (1) {
        //  Tell the broker we're ready for work
        s_sendmore (worker, "");
        s_send (worker, "Hi Boss");

        //  Get workload from broker, until finished
        // free (s_recv (worker));     //  Envelope delimiter
        // char *workload = s_recv (worker);
        // int finished = (strcmp (workload, "Fired!") == 0);
        // free (workload);
        // if (finished) {
            // printf ("Completed: %d tasks\n", total);
            // break;
        // }
        total++;

        //  Do some random work
        s_sleep (randof (500) + 1);
    }
    zmq_close (worker);
    zmq_ctx_destroy (context);
    return 0;
}

