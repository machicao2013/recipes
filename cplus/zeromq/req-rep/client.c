#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Connection to hello world server....\n");
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:8888");

    int request_no;
    for(request_no = 0; request_no != 10; ++request_no) {
        char buffer[10];
        printf("Sending Hello %d...\n", request_no);

        if(-1 == zmq_send(socket, "Hello", 5, 0)){
            printf("send message error, %d, %s\n", errno, zmq_strerror(errno));
            break;
        }
        // zmq_recv(socket, buffer, 10, 0);
        // printf("Received world %d\n", request_no);
    }
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}

