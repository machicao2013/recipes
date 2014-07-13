#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int listenfd,clientfd;
    struct sockaddr_in server_addr,client_addr;
    socklen_t sin_size;
    unsigned short portnum=8888;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listenfd)
    {
        printf("socket fail ! \r\n");
        return -1;
    }

    bzero(&server_addr,sizeof(struct sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(portnum);

    if(-1 == bind(listenfd,(struct sockaddr *)(&server_addr), sizeof(struct sockaddr)))
    {
        printf("bind fail !\r\n");
        return -1;
    }

    if(-1 == listen(listenfd,5))
    {
        printf("listen fail !\r\n");
        return -1;
    }

    char recvbuf[1024];
    sin_size = sizeof(struct sockaddr_in);

    while(1)
    {
        clientfd = accept(listenfd, (struct sockaddr *)(&client_addr), &sin_size);
        if(-1 == clientfd)
        {
            printf("accept fail !\r\n");
            return -1;
        }

        // don't need receive all 1024 bytes, if it receive some bytes(less than 1024),
        // it will receive
        ssize_t len = read(clientfd, recvbuf, 1024);
        recvbuf[len] = '\0';

        printf("recv: %s", recvbuf);
        send(clientfd, recvbuf, strlen(recvbuf), 0);
        close(clientfd);
    }
    close(listenfd);
    return 0;
}

