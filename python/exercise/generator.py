#!/usr/bin/python
# -* - coding: UTF-8  -* -

def gen():
    for x in xrange(4):
        tmp = yield x
        if tmp == 'hello':
            print 'world'
        else:
            print str(tmp)
