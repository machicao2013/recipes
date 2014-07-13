#!/usr/bin/python
# -* - coding: UTF-8  -* -

d = {'a':1, 'b':2, 'c':3}
for key in d:
    print key
print '==========================='
for value in d.itervalues():
    print value
print '==========================='

for key, value in d.iteritems():
    print key,':',value

l = range(0,11,2)
for index,value in enumerate(l):
    print index, value
