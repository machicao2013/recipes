#!/usr/bin/python
# -* - coding: UTF-8  -* -

s = set([1,2,3])
print s
s.add(4)
print s
s.remove(4)
s2 = set([2, 3, 4])
print (s & s2)
print (s | s2)
