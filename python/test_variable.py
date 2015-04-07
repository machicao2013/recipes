#!/usr/bin/python
# -* - coding: UTF-8  -* -

i , j = 5, 10

print("i = %d, j = %d" % (i,j))

def func1():
    i, j = 11, 12
    print("i = %d, j = %d" % (i,j))

func1()

print("i = %d, j = %d" % (i,j))
