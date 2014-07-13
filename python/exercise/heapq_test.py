#!/usr/bin/python
# -* - coding: UTF-8  -* -

from heapq import *
from random import shuffle

data = range(10)
shuffle(data)
heap = []
for n in data:
    heappush(heap, n)

print heap

heappush(heap, 0.5)
print heap

data = range(20)
shuffle(data)
heapify(data)
print data

print nlargest(5, data)
print nsmallest(5, data)
