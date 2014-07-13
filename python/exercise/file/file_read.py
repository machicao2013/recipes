#!/usr/bin/python
# -* - coding: UTF-8  -* -

file_name = 'file_read.py'

# method 1
with open(file_name, 'r') as f:
    line = f.readline()
    while line:
        print line.rstrip()
        line = f.readline()

# method 2
for line in open(file_name):
    print line.rstrip()

# method 3
with open(file_name, 'r') as f:
    while True:
        lines = f.readlines(10000)
        if not lines:
            break
        for line in lines:
            print line.rstrip()
