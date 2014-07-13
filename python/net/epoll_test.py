#!/usr/bin/python
# -* - coding: UTF-8  -* -

import socket
import select

HOST = 'localhost'
PORT = 9999

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.bind((HOST, PORT))
sock.listen(5)

epolling = select.epoll(6)
epolling.register(sock, select.EPOLLIN)

while True:
    events = epolling.poll(timeout = -1)
    for event in events:
        print "received ", event[0]
        if event[0] == sock:
             conn, addr = sock.accept()
             conn.sendall('welcom to our server')
             conn.close()
