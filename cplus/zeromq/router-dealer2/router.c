#include "zhelpers.h"
#include <pthread.h>
#define NBR_WORKERS 10

int main (void)
{
    void *context = zmq_ctx_new ();
    void *broker = zmq_socket (context, ZMQ_ROUTER);

    zmq_bind (broker, "tcp://*:5671");
    srandom ((unsigned) time (NULL));

    int64_t end_time = s_clock () + 5000;
    int workers_fired = 0;
    while (1) {
        //  Next message gives us least recently used worker
        char *identity = s_recv (broker);
        // s_sendmore (broker, identity);
        // free (identity);
        free (s_recv (broker));     //  Envelope delimiter
        free (s_recv (broker));     //  Response from worker
        // s_sendmore (broker, "");

        //  Encourage workers until it's time to fire them
        if (s_clock () < end_time)
            // s_send (broker, "Work harder");
            ;
        else {
            // s_send (broker, "Fired!");
            if (++workers_fired == NBR_WORKERS)
                break;
        }
    }
    zmq_close (broker);
    zmq_ctx_destroy (context);
    return 0;
}
