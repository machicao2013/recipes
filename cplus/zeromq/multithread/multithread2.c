//  Multithreaded relay

#include "zhelpers.h"
#include <pthread.h>

static void* step (void *context) {
    void *receiver = zmq_socket (context, ZMQ_PAIR);
    zmq_connect (receiver, "inproc://step");
    printf ("Step ready, signaling step\n");
    int i = 0;
    for (i = 0; i < 10; i++) {
        char *data = s_recv(receiver);
        printf("%s\n", data);
        free(data);
    }
    zmq_close (receiver);

    return NULL;
}

int main (void)
{
    void *context = zmq_ctx_new ();

    //  Bind inproc socket before starting step2
    void *sender = zmq_socket (context, ZMQ_PAIR);
    zmq_bind (sender, "inproc://step");
    pthread_t thread;
    pthread_create (&thread, NULL, step, context);

    int i = 0;
    for (i = 0; i < 10; i++) {
        s_send(sender, "Hello");
    }
    zmq_close (sender);
    sleep(1);

    printf ("Test successful!\n");
    zmq_ctx_destroy (context);
    return 0;
}
