#!/usr/bin/python
# -* - coding: UTF-8  -* -

import socket, logging
import select, errno

logger = logging.getLogger("network-server")

def initLog():
    logger.setLevel(logging.DEBUG)

    fh = logging.FileHandler("network-server.log")
    #fh.setLevel(logging.DEBUG)
    fh.setLevel(logging.ERROR)
    ch = logging.StreamHandler()
    ch.setLevel(logging.ERROR)

    formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
    fh.setFormatter(formatter)
    ch.setFormatter(formatter)

    logger.addHandler(fh)
    logger.addHandler(ch)

if __name__ == '__main__':
    initLog()

    try:
        listen_fd = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    except socket.error, msg:
        logger.error("create socket failed")

    try:
        listen_fd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except socket.error, msg:
        logger.error("setsockopt SO_REUSEADDR failed")

    try:
        listen_fd.bind(('', 1234))
    except socket.error, msg:
        logger.error("bind failed")

    try:
        listen_fd.listen(10)
    except socket.error, msg:
        logger.error(msg)

    try:
        epoll_fd = select.epoll()
        epoll_fd.register(listen_fd.fileno(), select.EPOLLIN)
    except socket.error, msg:
        logger.error(msg)

    connections = {}
    addresses = {}
    datalist = {}

    while True:
        epoll_list = epoll_fd.poll()

        for fd, events in epoll_list:
            if  fd == listen_fd.fileno():
                conn, addr = listen_fd.accept()
                logging.debug("accept connection from %s, %d, fd = %d" % (addr[0], addr[1], conn.fileno()))
                conn.setblocking(0)
                epoll_fd.register(conn.fileno(), select.EPOLLIN | select.EPOLLET)
                connections[conn.fileno()] = conn
                addresses[conn.fileno()] = addr
            elif select.EPOLLIN & events:
                datas = ''#{{{
                while True:
                    try:
                        data = connections[fd].recv(10)
                        if not data and not datas:
                            epoll_fd.unregister(fd)
                            connections[fd].close()
                            del connections[fd]
                            logger.debug("%s, %d closed" % (addresses[fd][0], addresses[fd][1]))
                            break
                        else:
                            datas += data
                    except socket.error, msg:
                        if msg.errno == errno.EAGAIN:
                            logger.debug("%s receive %s" % (fd, datas))
                            datalist[fd] = datas
                            epoll_fd.modify(fd, select.EPOLLET | select.EPOLLOUT)
                            break
                        else:
                            epoll_fd.unregister(fd)
                            connections[fd].close()
                            del connections[fd]
                            logger.error(msg)#}}}
            elif select.EPOLLHUP & events:
                epoll_fd.unregister(fd)
                connections[fd].close()
                del connections[fd]
                logger.debug("%s, %d closed" % (addresses[fd][0], addresses[fd][1]))
            elif select.EPOLLOUT & events:
                sendLen = 0
                while True:
                    sendLen += connections[fd].send(datalist[fd][sendLen:])
                    if sendLen == len(datalist[fd]):
                        break
                epoll_fd.modify(fd, select.EPOLLIN | select.EPOLLET)
            else:
                continue



