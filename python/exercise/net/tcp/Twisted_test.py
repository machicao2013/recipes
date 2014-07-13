from twisted.internet import reactor
from twisted.internet.protocol import Protocol, Factory

class SimpeLogger(Protocol):
    def connectionMade(self):
        print 'Got connection from ', self.transport.client

    def connectionLost(self, reason):
        print self.transport.client, ' disconnected'

    def dataReceived(self, data):
        sys.stdout.write(data)

if __name__ == '__main__':
    factory = Factory()
    factory.protocol = SimpeLogger

    reactor.listenTCP(1234, factory)
    reactor.run()
