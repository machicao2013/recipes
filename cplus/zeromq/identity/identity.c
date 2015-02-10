#include "zhelpers.h"
#include <unistd.h>

int main (void)
{
    int mandatory = 1;
    void *context = zmq_ctx_new ();
    void *sink = zmq_socket (context, ZMQ_ROUTER);
    zmq_setsockopt(sink, ZMQ_ROUTER_MANDATORY, &mandatory, 4);
    zmq_bind (sink, "inproc://example");

    //  First allow 0MQ to set the identity
    // void *anonymous = zmq_socket (context, ZMQ_REQ);
    void *anonymous = zmq_socket (context, ZMQ_ROUTER);
    zmq_setsockopt(anonymous, ZMQ_IDENTITY, "PEER1", 5);
    zmq_setsockopt(anonymous, ZMQ_ROUTER_MANDATORY, &mandatory, 4);
    zmq_connect (anonymous, "inproc://example");
    sleep(1);
    if(s_send(anonymous, "PEER1") <= 0) {
        printf("send PEER1 error\n");
    } else {
        printf("send PEER1 success\n");
    }
    if(s_send (anonymous, "ROUTER uses a generated UUID") <= 0) {
        printf("send message error\n");
    } else {
        printf("send message success\n");
    }
    s_dump (sink);

    //  Then set the identity ourselves
    void *identified = zmq_socket (context, ZMQ_REQ);
    zmq_setsockopt (identified, ZMQ_IDENTITY, "PEER2", 5);
    zmq_connect (identified, "inproc://example");
    s_send (identified, "ROUTER socket uses REQ's socket identity");
    s_dump (sink);

    zmq_close (sink);
    zmq_close (anonymous);
    zmq_close (identified);
    zmq_ctx_destroy (context);
    return 0;
}
