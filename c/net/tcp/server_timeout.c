#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXPENDING 5
#define BUFFSIZE 3200
#define PORT 9999

void Die(char *mess)
{
    perror(mess);
    exit(1);
}

void HandleClient(int sock)
{
    char buffer[BUFFSIZE];
    int received = -1;
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
        Die("Failed to recevie inital bytes from client");
    }
    printf("%s\n", buffer);
    printf("===============================================\n");
    while (received > 0) {
        if (send(sock, buffer, received, 0) != received) {
            Die("Failed to send bytes to client");
        }
        if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
            Die("Failed to receive additional bytes from client");
        }
        printf("===============================================\n");
    }
    close(sock);
}

void setRcvTimeout(int socket, int timeout)
{
    struct timeval time;
    time.tv_sec = timeout;
    time.tv_usec = 0;
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &time, sizeof(time));
    //setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &time, sizeof(time));
}

int main()
{
    int serversock, clientsock;
    struct sockaddr_in echoserver, echoclient;
    if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        Die("Failed to create socket");
    }

    setRcvTimeout(serversock, 5);

    memset(&echoserver, 0, sizeof(echoserver));
    echoserver.sin_family = AF_INET;
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
    echoserver.sin_port = htons(PORT);

    if (bind(serversock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) {
        Die("Failed to bind the server socket");
    }
    if (listen(serversock, MAXPENDING) < 0) {
        Die("Failed to listen on server socket");
    }

    while (1) {
        unsigned int clientlen = sizeof(echoclient);
        if ((clientsock = accept(serversock, (struct sockaddr *) &echoclient, &clientlen)) < 0 ) {
            Die("Failed to accept client connection");
        }
        fprintf(stdout, "Client connected:%s/n", inet_ntoa(echoclient.sin_addr));
        HandleClient(clientsock);
    }
}

