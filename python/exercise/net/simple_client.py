#!/usr/bin/python
# -* - coding: UTF-8  -* -

import socket

HOST = '127.0.1.1'
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)

s.connect((HOST, PORT))

print s.recv(1024)
