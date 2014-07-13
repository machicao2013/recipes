#!/usr/bin/python
# -* - coding: UTF-8  -* -

import os

lists = ['Welcom to this file', 'This is nothing here except', 'This stupid haiku']

with open('somefile.txt', 'w') as f:
    f.writelines(lists)

with open('somefile.txt', 'a') as f:
    f.write(os.linesep)
    for string in lists:
        f.write(string)
        f.write(os.linesep)
