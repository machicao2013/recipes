#include "network_util.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>

#define NETWORK_ERR_LEN 256
#define NETWORK_CONNECT_NONE 0
#define NETWORK_CONNECT_NONBLOCK 1

static void setError(char *err, const char *fmt, ...) {
    if (!err) {
        return;
    }
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(err, NETWORK_ERR_LEN, fmt, ap);
    va_end(ap);
}


int setNonBlock(char *err, int fd) {
    int flags;
    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        setError(err, "fcntl(F_GETFL): %s", strerror(errno));
        return -1;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        setError(err, "fcntl(F_SETFL): %s", strerror(errno));
        return -1;
    }
    return 0;
}

int setTcpNoDelay(char *err, int fd) {
    int yes = 1;
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
        setError(err, "setsockopt TCP_NODELAY: %s", strerror(errno));
        return -1;
    }
    return 0;
}

int setSendBufferSize(char *err, int fd, int bufferSize) {
    if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &bufferSize, sizeof(bufferSize)) == -1) {
        setError(err, "setsockopt SO_SNDBUF: %s", strerror(errno));
        return -1;
    }
    return 0;
}

int setTcpKeepAlive(char *err, int fd) {
    int yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes)) == -1) {
        setError(err, "setsockopt SO_KEEPALIVE: %s", strerror(errno));
        return -1;
    }
    return 0;
}

/*
 *  hostname to ip
 */
int resolve(char *err, char *host, char *ipbuf) {
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    if (inet_aton(host, &sa.sin_addr) == 0) {
        struct hostent *he;
        he = gethostbyname(host);
        if (he == NULL) {
            setError(err, "can't resolve: %s", host);
            return -1;
        }
        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
    }
    strcpy(ipbuf, inet_ntoa(sa.sin_addr));
    return 0;
}

int setReuseAddr(char *err, int fd) {
    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        setError(err, "setsockopt SO_REUSEADDR: %s", strerror(errno));
        return -1;
    }
    return 0;
}

static int createSocket(char *err, int domain) {
    int s;
    s = socket(domain, SOCK_STREAM, IPPROTO_TCP);
    if (s == -1) {
        setError(err, "creating socket: %s", strerror(errno));
        return -1;
    }
    return s;
}

static int tcpGenericConnect(char *err, char *addr, int port, int flags) {
    int s;
    struct sockaddr_in sa;

    if ((s = createSocket(err, PF_INET)) == -1) {
        return -1;
    }
    sa.sin_family = PF_INET;/*{{{*/
    sa.sin_port = htons(port);
    if (inet_aton(addr, &sa.sin_addr) == 0) {
        struct hostent *he;
        he = gethostbyname(addr);
        if (he == NULL) {
            setError(err, "can't resolve: %s", addr);
            close(s);
            return -1;
        }
        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
    }
    if (flags & NETWORK_CONNECT_NONBLOCK) {
        if(setNonBlock(err, s) != 0) {
            return -1;
        }
    }
    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == EINPROGRESS && (flags & NETWORK_CONNECT_NONBLOCK)) {
            return s;
        }
        setError(err, "connect: %s", strerror(errno));
        close(s);
        return -1;
    }/*}}}*/
    return s;
}

int tcpConnect(char *err, char *addr, int port) {
    return tcpGenericConnect(err, addr, port, NETWORK_CONNECT_NONE);
}

int tcpNonBlockConnect(char *err, char *addr, int port) {
    return tcpGenericConnect(err, addr, port, NETWORK_CONNECT_NONBLOCK);
}

/*
 *  like read(2) but make sure 'count' is read before to return
 *  unless error or EOF condition is encountered
 */
int readAll(int fd, char *buf, int count) {
    int nread = 0, totlen = 0;
    while(totlen != count) {
        nread = read(fd, buf, count - totlen);
        if (nread == 0) {
            return totlen;
        }
        if (nread == -1) {
            return -1;
        }
        totlen += nread;
        buf += nread;
    }
    return totlen;
}

/*
 *  like write(2) but make sure 'count' is write before to return
 *  unless error is encountered
 */
int writeAll(int fd, char *buf, int count) {
    int nwrite = 0, totlen = 0;
    while (totlen != count) {
        nwrite = write(fd, buf, count - totlen);
        if (nwrite == 0) {
            return totlen;
        }
        if (nwrite == -1) {
            return -1;
        }
        totlen += nwrite;
        buf += nwrite;
    }
    return totlen;
}

static int tcpListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
    if (bind(s, sa, len) == -1) {
        setError(err, "bind: %s", strerror(errno));
        close(s);
        return -1;
    }
    if (listen(s, 511) == -1) {
        setError(err, "listen: %s", strerror(errno));
        close(s);
        return -1;
    }
    return 0;
}

/*
 *  Create a tcp server. if bindaddr is NULL, bind any address
 */
int createTcpServer(char *err, int port, char *bindaddr) {
    int s;
    struct sockaddr_in sa;

    s = createSocket(err, PF_INET);
    if (s == -1) {
        return -1;
    }

    memset(&sa, 0, sizeof(sa));
    sa.sin_family = PF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bindaddr && (inet_aton(bindaddr, &sa.sin_addr) == 0)) {
        setError(err, "invalid bind address");
        close(s);
        return -1;
    }
    if (tcpListen(err, s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        return -1;
    }
    return s;
}

static int genericAccept(char *err, int s, struct sockaddr *sa, socklen_t *len) {
    int fd;
    while(1) {
        fd = accept(s,sa,len);
        if (fd == -1) {
            if (errno == EINTR)
                continue;
            else {
                //log
                return -1;
            }
        }
        break;
    }
    return fd;
}

int tcpAccept(char *err, int s, char *ip, int *port) {
    int fd;
    struct sockaddr_in sa;
    socklen_t salen = sizeof(sa);
    if ((fd = genericAccept(err,s,(struct sockaddr*)&sa,&salen)) == -1)
        return -1;

    if (ip) strcpy(ip,inet_ntoa(sa.sin_addr));
    if (port) *port = ntohs(sa.sin_port);
    return fd;
}

int getPeerName(int fd, char *ip, int *port) {
    struct sockaddr_in sa;
    socklen_t slen = sizeof(sa);

    if (getpeername(fd, (struct sockaddr*)&sa, &slen) == -1) {
        *port = 0;
        ip[0] = '?';
        ip[1] = '\0';
        return -1;
    }
    if (ip) {
        strcpy(ip, inet_ntoa(sa.sin_addr));
    }
    if (port) {
        *port = ntohs(sa.sin_port);
    }
    return 0;
}

int getSockName(int fd, char *ip, int *port) {
    struct sockaddr_in sa;
    socklen_t slen = sizeof(sa);

    if (getsockname(fd, (struct sockaddr*)&sa, &slen) == -1) {
        *port = 0;
        ip[0] = '?';
        ip[1] = '\0';
        return -1;
    }
    if (ip) {
        strcpy(ip, inet_ntoa(sa.sin_addr));
    }
    if (port) {
        *port = ntohs(sa.sin_port);
    }
    return 0;
}
