#!/usr/bin/python

import socket

HOST = ''
PORT = 5000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(1)
while 1:
    conn, addr = s.accept()
    print 'Connected by ', addr
    while 1:
        data = conn.recv(1024)
        if  not data:
            break
        conn.sendall(data)
    conn.close()
