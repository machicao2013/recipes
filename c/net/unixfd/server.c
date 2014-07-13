/*
 * server.c -
 *
 * Copyright (C) 2014 Xunlei CO. Ltd
 *
 * Author: maxingsong (maxingsong@xunlei.com)
 * Create: 2014-05-09 11:23:32
 *
 * History:
 * --------
 * 2014-05-09    v1.0    maxingsong (maxingsong@xunlei.com)
 *     1. Initial revision.
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define FILE_NAME "1.txt"
#define BUF_SIZE 1024

int serv_listen(const char* name)
{
    int fd;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        return -1;

    unlink(name);
    struct sockaddr_un un;
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, name);
    int len = (int)((void*)&(un.sun_path) - (void*)&un) + strlen(un.sun_path);
    if (bind(fd, (struct sockaddr*)&un, len) < 0) {
        close(fd);
        return -2;
    }

    if (listen(fd, 128) < 0) {
        close(fd);
        return -3;
    }

    return fd;
}

int serv_accept(int listenfd)
{

    int fd;
    struct sockaddr_un un;
    socklen_t len = sizeof(un);

    if ((fd = accept(listenfd, (struct sockaddr*)&un, &len)) < 0)
        return -1;

    ((char*)(&un))[len] = '\0';
    unlink(un.sun_path);

    return fd;
}

int main()
{
    int fd;
    if ((fd = serv_listen(FILE_NAME)) < 0) {
        printf("listen error!\n");
        exit(fd);
    }

    while(1) {
        int sclient = serv_accept(fd);
        if (sclient < 0) {
            printf("accept error!\n");
            exit(sclient);
        }

        char buffer[BUF_SIZE];
        ssize_t len = recv(sclient, buffer, BUF_SIZE, 0);
        if (len < 0) {
            printf("recieve error!\n");
            close(sclient);
            continue;
        }

        buffer[len] = '\0';
        printf("receive[%d]:%s\n", (int)len, buffer);
        if (len > 0) {
            if('q' == buffer[0]) {
                printf("server over!\n");
                exit(0);
            }

            char* buffer2 = "I'm a server!";
            len = send(sclient, buffer2, strlen(buffer2), 0);
            if (len < 0)
                printf("send error!\n");
        }
        close(sclient);
    }

    return 0;
}

