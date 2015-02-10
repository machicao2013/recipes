#include "zhelpers.h"

int main (void)
{
    //  Prepare our context and dealer
    void *context = zmq_ctx_new ();
    void *dealer = zmq_socket (context, ZMQ_DEALER);
    // zmq_setsockopt (dealer, ZMQ_IDENTITY, "B", 1);
    zmq_connect (dealer, "tcp://localhost:5563");

    int count = 10;
    while (count--) {
        //  Read envelope with address
        // char *address = s_recv (dealer);
        //  Read message contents
        // char *contents = s_recv (dealer);
        // printf ("[%s] %s\n", address, contents);
        // free (address);
        // printf ("[%s]\n", contents);
        // free (contents);
        // s_sendmore(dealer, "");
        s_send(dealer, "Hello");
    }
    //  We never get here, but clean up anyhow
    zmq_close (dealer);
    zmq_ctx_destroy (context);
    return 0;
}
