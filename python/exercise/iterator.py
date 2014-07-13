#!/usr/bin/python
# -* - coding: UTF-8  -* -

class Fibs(object):
    """docstring for Fibs"""
    def __init__(self):
        super(Fibs, self).__init__()
        self.a = 0
        self.b = 1
    def next(self):
        self.a, self.b = self.b, self.a + self.b
        return self.a
    def __iter__(self):
        return self

fibs = Fibs()
for f in fibs:
    if f < 30:
        print f
    else:
        break
