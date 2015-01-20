#include "zhelpers.h"

int main (void)
{
    //  Prepare our context and router
    void *context = zmq_ctx_new ();
    void *router = zmq_socket (context, ZMQ_ROUTER);
    zmq_bind (router, "tcp://*:5563");

    while (1) {
        free(s_recv (router));
        free(s_recv (router));
        char *msg = s_recv(router);
        printf("recv msg: [%s]\n", msg);
        free(msg);
    }
    //  We never get here, but clean up anyhow
    zmq_close (router);
    zmq_ctx_destroy (context);
    return 0;
}
