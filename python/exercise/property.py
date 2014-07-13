#!/usr/bin/python
# -* - coding: UTF-8  -* -

class Rectangle(object):
    """docstring for Rectangle"""
    def __init__(self):
        super(Rectangle, self).__init__()
        self.height = 0
        self.width = 0

    def setSize(self, size):
        self.height, self.width = size

    def getSize(self):
        return (self.height, self.width)

    size = property(getSize, setSize)

r = Rectangle()
print r.height, r.width
r.height = 10
r.width = 20
print r.size
