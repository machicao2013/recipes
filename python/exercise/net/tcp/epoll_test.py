#!/usr/bin/python
# -* - coding: UTF-8  -* -

import socket
import select
from select import epoll

HOST = 'localhost'
PORT = 1234

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.bind((HOST, PORT))
sock.listen(5)

epolling = epoll(5)
epolling.register(sock.fileno(), select.EPOLLIN)

conns = {}
data = {}

while True:
    events = epolling.poll(timeout = -1)   # wait indefinitely
    for event in events:
        if event[0] == sock.fileno():
            conn, addr = sock.accept()
            print addr, ' connected'
            epolling.register(conn.fileno(), select.EPOLLIN)
            conns[conn.fileno()] = conn
        elif event[1] & select.EPOLLIN:
            conn = conns[event[0]]
            data[event[0]] = conn.recv(1024)
            epolling.modify(event[0], select.EPOLLOUT)
        elif event[1] & select.EPOLLOUT:
            conn = conns[event[0]]
            conn.sendall(data[event[0]].upper())
            conn.close()
            del conns[event[0]]


