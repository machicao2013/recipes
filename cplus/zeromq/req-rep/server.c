#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main()
{
    void *context = zmq_ctx_new();
    // void *socket = zmq_socket(context, ZMQ_REP);
    void *socket = zmq_socket(context, ZMQ_ROUTER);
    int rc = zmq_bind(socket, "tcp://*:8888");
    if (rc != 0) {
        printf("bind error\n");
        return 1;
    }

    printf("EAGAIN: %d\n", EAGAIN);
    while (1) {
        char buffer[10] = {0};
        if(-1 == zmq_recv(socket, buffer, 10, 0)) {
            printf("Received error [%d] %s\n", errno, zmq_strerror(errno));
            break;
        } else {
            printf("Received Hello\n");
        }
        // sleep(1);
        // zmq_send(socket, "World", 5, 0);
    }
    return 0;
}

