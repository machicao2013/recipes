/*
 * twemproxy - A fast and lightweight proxy for memcached protocol.
 * Copyright (C) 2011 Twitter, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "sock_utils.h"

int nc_set_blocking(int sd)
{
	int       flags;

	flags = fcntl(sd, F_GETFL, 0);
	if (flags < 0) {
		return flags;
	}

	return fcntl(sd, F_SETFL, flags & ~O_NONBLOCK);
}

int nc_set_nonblocking(int sd)
{
	int       flags;

	flags = fcntl(sd, F_GETFL, 0);
	if (flags < 0) {
		return flags;
	}

	return fcntl(sd, F_SETFL, flags | O_NONBLOCK);
}

int nc_set_reuseaddr(int sd)
{
	int       reuse;
	socklen_t len;

	reuse = 1;
	len = sizeof(reuse);

	return setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &reuse, len);
}

/*
 * Disable Nagle algorithm on TCP socket.
 *
 * This option helps to minimize transmit latency by disabling coalescing
 * of data to fill up a TCP segment inside the kernel. Sockets with this
 * option must use readv() or writev() to do data transfer in bulk and
 * hence avoid the overhead of small packets.
 */
int nc_set_tcpnodelay(int sd)
{
	int       nodelay;
	socklen_t len;

	nodelay = 1;
	len = sizeof(nodelay);

	return setsockopt(sd, IPPROTO_TCP, TCP_NODELAY, &nodelay, len);
}

int nc_set_linger(int sd, int timeout)
{
	struct linger linger;
	socklen_t len;

	linger.l_onoff = 1;
	linger.l_linger = timeout;

	len = sizeof(linger);

	return setsockopt(sd, SOL_SOCKET, SO_LINGER, &linger, len);
}

int nc_set_sndbuf(int sd, int size)
{
	socklen_t len;

	len = sizeof(size);

	return setsockopt(sd, SOL_SOCKET, SO_SNDBUF, &size, len);
}

int nc_set_rcvbuf(int sd, int size)
{
	socklen_t len;

	len = sizeof(size);

	return setsockopt(sd, SOL_SOCKET, SO_RCVBUF, &size, len);
}

int nc_get_soerror(int sd)
{
	int       status, err;
	socklen_t len;

	err = 0;
	len = sizeof(err);

	status = getsockopt(sd, SOL_SOCKET, SO_ERROR, &err, &len);
	if (status == 0) {
		errno = err;
	}

	return status;
}

int nc_get_sndbuf(int sd)
{
	int       status, size;
	socklen_t len;

	size = 0;
	len = sizeof(size);

	status = getsockopt(sd, SOL_SOCKET, SO_SNDBUF, &size, &len);
	if (status < 0) {
		return status;
	}

	return size;
}

int nc_get_rcvbuf(int sd)
{
	int       status, size;
	socklen_t len;

	size = 0;
	len = sizeof(size);

	status = getsockopt(sd, SOL_SOCKET, SO_RCVBUF, &size, &len);
	if (status < 0) {
		return status;
	}

	return size;
}

int _nc_atoi(uint8_t * line, size_t n)
{
	int       value;

	if (n == 0) {
		return -1;
	}

	for (value = 0; n--; line++) {
		if (*line < '0' || *line > '9') {
			return -1;
		}

		value = value * 10 + (*line - '0');
	}

	if (value < 0) {
		return -1;
	}

	return value;
}

bool nc_valid_port(int n)
{
	if (n < 1 || n > UINT16_MAX) {
		return false;
	}

	return true;
}

/*
 * Send n bytes on a blocking descriptor
 */
ssize_t _nc_sendn(int sd, const void *vptr, size_t n)
{
	size_t    nleft;
	ssize_t   nsend;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		nsend = send(sd, ptr, nleft, 0);
		if (nsend < 0) {
			if (errno == EINTR) {
				continue;
			}
			return nsend;
		}
		if (nsend == 0) {
			return -1;
		}

		nleft -= (size_t) nsend;
		ptr += nsend;
	}

	return (ssize_t) n;
}

/*
 * Recv n bytes from a blocking descriptor
 */
ssize_t _nc_recvn(int sd, void *vptr, size_t n)
{
	size_t    nleft;
	ssize_t   nrecv;
	char     *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		nrecv = recv(sd, ptr, nleft, 0);
		if (nrecv < 0) {
			if (errno == EINTR) {
				continue;
			}
			return nrecv;
		}
		if (nrecv == 0) {
			break;
		}

		nleft -= (size_t) nrecv;
		ptr += nrecv;
	}

	return (ssize_t) (n - nleft);
}

/*
 * Return the current time in microseconds since Epoch
 */
int64_t nc_usec_now(void)
{
	struct timeval now;
	int64_t   usec;
	int       status;

	status = gettimeofday(&now, NULL);
	if (status < 0) {
		log_error("gettimeofday failed: %s", strerror(errno));
		return -1;
	}

	usec = (int64_t) now.tv_sec * 1000000LL + (int64_t) now.tv_usec;

	return usec;
}

/*
 * Return the current time in milliseconds since Epoch
 */
int64_t nc_msec_now(void)
{
	return nc_usec_now() / 1000LL;
}
