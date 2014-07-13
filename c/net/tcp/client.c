#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int clientfd;
    char buffer[1024] = {0};
    struct sockaddr_in s_add;
    unsigned short portnum = 8888;

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == clientfd)
    {
        printf("socket fail ! \r\n");
        return -1;
    }

    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr= inet_addr("127.0.0.1");
    s_add.sin_port=htons(portnum);
    // printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

    if(-1 == connect(clientfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        printf("connect fail !\r\n");
        return -1;
    }
    // printf("connect ok !\r\n");

    sprintf(buffer, "hello world %d\r\n", 1);

    send(clientfd, buffer, strlen(buffer), 0);
    recv(clientfd, buffer, 1024, 0);
    printf("recv: %s", buffer);

    close(clientfd);
    return 0;
}
