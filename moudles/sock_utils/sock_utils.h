#ifndef _NC_UTIL_H_
#define _NC_UTIL_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <netinet/in.h>
#include <netinet/tcp.h>

/*
 * Wrapper to workaround well known, safe, implicit type conversion when
 * invoking system calls.
 */
#define bool int
#define true  1
#define false 0
#define nc_gethostname(_name, _len) \
    gethostname((char *)_name, (size_t)_len)

#define nc_atoi(_line, _n)          \
    _nc_atoi((uint8_t *)_line, (size_t)_n)

int       nc_set_blocking(int sd);
int       nc_set_nonblocking(int sd);
int       nc_set_reuseaddr(int sd);
int       nc_set_tcpnodelay(int sd);
int       nc_set_linger(int sd, int timeout);
int       nc_set_sndbuf(int sd, int size);
int       nc_set_rcvbuf(int sd, int size);
int       nc_get_soerror(int sd);
int       nc_get_sndbuf(int sd);
int       nc_get_rcvbuf(int sd);

int       _nc_atoi(uint8_t * line, size_t n);
bool      nc_valid_port(int n);

/*
 * Wrappers to send or receive n byte message on a blocking
 * socket descriptor.
 */
#define nc_sendn(_s, _b, _n)    \
    _nc_sendn(_s, _b, (size_t)(_n))

#define nc_recvn(_s, _b, _n)    \
    _nc_recvn(_s, _b, (size_t)(_n))

/*
 * Wrappers to read or write data to/from (multiple) buffers
 * to a file or socket descriptor.
 */
#define nc_read(_d, _b, _n)     \
    read(_d, _b, (size_t)(_n))

#define nc_readv(_d, _b, _n)    \
    readv(_d, _b, (int)(_n))

#define nc_write(_d, _b, _n)    \
    write(_d, _b, (size_t)(_n))

#define nc_writev(_d, _b, _n)   \
    writev(_d, _b, (int)(_n))

ssize_t   _nc_sendn(int sd, const void *vptr, size_t n);
ssize_t   _nc_recvn(int sd, void *vptr, size_t n);

int64_t   nc_usec_now(void);
int64_t   nc_msec_now(void);

#endif
