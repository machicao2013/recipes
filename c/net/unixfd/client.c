/*
 * client.c -
 *
 * Copyright (C) 2014 Xunlei CO. Ltd
 *
 * Author: maxingsong (maxingsong@xunlei.com)
 * Create: 2014-05-09 11:25:22
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
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILE_NAME "1.txt"
#define CLI_PATH "/var/tmp/"
#define BUF_SIZE 1024

int cli_conn(const char* name)
{
    int fd;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        return -1;

    struct sockaddr_un un;
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s%05d", CLI_PATH, getpid());
    unlink(un.sun_path);
    int len = (int)((void*)&(un.sun_path) - (void*)&un) + strlen(un.sun_path);
    if (bind(fd, (struct sockaddr*)&un, len) < 0) {
        close(fd);
        return -2;
    }

    if(chmod(un.sun_path, S_IRWXU) < 0) {
        close(fd);
        return -3;
    }

    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, name);
    len = (int)((void*)&(un.sun_path) - (void*)&un) + strlen(un.sun_path);
    if (connect(fd, (struct sockaddr*)&un, len) < 0) {
        close(fd);
        return -4;
    }

    return fd;
}

int main()
{
    int fd;
    if ((fd = cli_conn(FILE_NAME)) < 0) {
        printf("connect error!\n");
        exit(fd);
    }

    char buffer[BUF_SIZE];
    printf("input:");
    scanf("%s", buffer);
    int len = send(fd, buffer, strlen(buffer), 0);
    if (len < 0) {
        printf("send error!\n");
        exit(len);
    }

    len = recv(fd, buffer, BUF_SIZE, 0);
    if (len < 0) {
        printf("recieve error!\n");
        exit(len);
    }

    buffer[len] = '\0';
    printf("receive[%d]:%s\n", (int)len, buffer);

    return 0;
}

