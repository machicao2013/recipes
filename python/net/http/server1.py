#!/usr/bin/python

import socket

HOST = ''
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(5)
while True:
    conn, addr = s.accept()
    request = conn.recv(2048)
    print request
