#!/usr/bin/python
# -* - coding: UTF-8  -* -

l = [x * x for x in range(1,11)]
print l
l = [x * x for x in range(1, 11) if x % 2 == 0]
print l

l = [m + n for m in 'ABC' for n in 'XYZ']
print l
