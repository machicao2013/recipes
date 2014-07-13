#!/usr/bin/python
# -* - coding: UTF-8  -* -

import fileinput

for line in fileinput.input(inplace = False):
    line = line.rstrip()
    num = fileinput.lineno()
    print '%-40s # %2i' % (line, num)

# ./fileinput_test1.py file1 file2
