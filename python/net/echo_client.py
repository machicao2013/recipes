#!/usr/bin/python

import socket

HOST = 'localhost'
PORT = 5000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.sendall('hello world')
data = s.recv(1024)
s.close()
print 'Received ', repr(data)
