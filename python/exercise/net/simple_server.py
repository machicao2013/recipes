#!/usr/bin/python
# -* - coding: UTF-8  -* -

import socket

HOST  = socket.gethostname()
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
s.bind((HOST, PORT))

s.listen(5)
while True:
    conn, addr = s.accept()
    print 'Got connection from ', addr
    conn.send('Thank you for connection')
    conn.close()
