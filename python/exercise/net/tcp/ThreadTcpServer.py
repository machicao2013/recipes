#!/usr/bin/python
# -* - coding: UTF-8  -* -

import socket
import threading
import SocketServer

class ThreadedTCPRequestHandler(SocketServer.BaseRequestHandler):
    def handle(self):
        """docstring for handle"""
        data = self.request.recv(1024)
        cur_thread = threading.current_thread()
        response = "{}: {}".format(cur_thread.name, data)
        self.request.sendall(response)

class ThreadTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass

def client(ip, port, message):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    sock.connect((ip, port))
    try:
        sock.sendall(message)
        response = sock.recv(1024)
        print 'Recvied: {}'.format(response)
    finally:
        sock.close()

if __name__ == '__main__':
    HOST, PORT = 'localhost', 0

    server = ThreadTCPServer((HOST, PORT), ThreadedTCPRequestHandler)
    ip, port = server.server_address

    # start a thread with the server -- that thread will then start one
    # more thread for each request
    server_thread = threading.Thread(target = server.serve_forever)

    server_thread.daemon = True
    server_thread.start()

    print "server loop running in thread: ", server_thread.name

    client(ip, port, 'hello world 1!')
    client(ip, port, 'hello world 2!')
    client(ip, port, 'hello world 3!')
    client(ip, port, 'hello world 4!')
