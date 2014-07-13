#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H
int setNonBlock(char *err, int fd);
int setTcpNoDelay(char *err, int fd);
int setSendBufferSize(char *err, int fd, int bufferSize);
int setTcpKeepAlive(char *err, int fd);
int resolve(char *err, char *host, char *ipbuf);
int setReuseAddr(char *err, int fd);
int tcpConnect(char *err, char *addr, int port);
int tcpNonBlockConnect(char *err, char *addr, int port);
int readAll(int fd, char *buf, int count);
int writeAll(int fd, char *buf, int count);
int createTcpServer(char *err, int port, char *bindaddr);
int tcpAccept(char *err, int s, char *ip, int *port);
int getPeerName(int fd, char *ip, int *port);
int getSockName(int fd, char *ip, int *port);
#endif
