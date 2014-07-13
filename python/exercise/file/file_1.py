#!/usr/bin/python
# -* - coding: UTF-8  -* -

with open('file_1.py', 'r') as f:
    # 不推荐，全部加载
    for line in f.readlines():
        print (line.strip())
