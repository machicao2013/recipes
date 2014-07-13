#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
@author: homer
@see: ithomer.net
'''

import socket

# Address
HOST = ''
PORT = 8700

text_content = '''
HTTP/1.x 200 OK
Content-Type: text/html

<head>
    <title>hello ithomer</title>
</head>
<html>
    <p>hello, Python Server</p>
    <img src="./transaction.png"/>
    <form name="input" action="/" method="post">
        First name:<input type="text" name="firstname"><br>
        <input type="submit" value="Submit">
    </form>
</html>
'''

f = open('./transaction.png', 'rb')
pic_content = '''
HTTP/1.x 200 OK
Content-Type: image/png
'''
pic_content = pic_content + f.read()

# Configure socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))

# Serve forever
while True:
    s.listen(3)
    conn, addr = s.accept()
    request = conn.recv(1024)       # 1024 is the receiving buffer size
    method = request.split(' ')[0]
    src = request.split(' ')[1]

    print 'Connected by', addr
    print 'Request is:', request

    # if GET method request
    if method == 'GET':
        if src == '/test.jpg':      # if ULR is /test.jpg
            content = pic_content
        else:
            content = text_content
        conn.sendall(content)       # send message
    # if POST method request
    if method == 'POST':
        form = request.split('\r\n')
        idx = form.index('')        # Find the empty line
        entry = form[idx:]          # Main content of the request

        value = entry[-1].split('=')[-1]
        conn.sendall(text_content + '\n <p>' + value + '</p>')
        ######
        # More operations, such as put the form into database
        # ...
        ######
    # close connection
    conn.close()
