#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <fcntl.h>
#include<sys/types.h>
#include <errno.h>
#include<sys/socket.h>
#include<stdlib.h>
#include <stdbool.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 1234
#define MAXDATASIZE 10

int main()
{
    int sockfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t addrlen;
    int num;
    char buf[MAXDATASIZE];

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Creatingsocket failed.");
        exit(1);
    }

    //set non-block
    int flag = fcntl(sockfd, F_GETFL);
    fcntl(sockfd, F_SETFL, flag | O_NONBLOCK);

    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr= htonl (INADDR_ANY);
    if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("Bind()error.");
        exit(1);
    }

    addrlen=sizeof(client);
    while(1)
    {
        while(true)
        {
            //在调用recvfrom接收包的时候，一个包只能够接收一次，所以buf必须足够的大，否则会buf之外的数据会被丢弃
            num =recvfrom(sockfd,buf,MAXDATASIZE - 1,0,(struct sockaddr*)&client,&addrlen);
            if (num < 0)
            {
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    perror("recvfrom() error\n");
                    exit(1);
                } else {
                    sleep(1);
                    continue;
                }
            }
            if (num == 0) {
                break;
            }
            buf[num] = '\0';
            printf("You got a message (%s) from client.\nIt's ip is%s, port is %d.\n",buf,
                inet_ntoa(client.sin_addr),htons(client.sin_port));

        }

        sendto(sockfd,"Welcometo my server.\n",22,0,(struct sockaddr *)&client,addrlen);
        if(!strcmp(buf,"bye"))
            break;
    }
    printf("end ============\n");
    close(sockfd);
    return 0;
}

