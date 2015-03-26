#!/usr/bin/python
# -* - coding: UTF-8  -* -

file = open('test_remove.py', 'r')

for line in file:
    # words = line.strip('\n').split(' ')
    # for word in words:
    #     if word.strip() != "":
    #         print(word)
    print line.strip()
