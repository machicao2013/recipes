#!/usr/bin/python
# -* - coding: UTF-8  -* -

mylist = ["http://www.baidu.com", "http://www.sohu.com", "ftp://www.sohu.com"]

# have error
for url in mylist:
    if url.startswith("http://"):
        mylist.remove(url)
    print(url)

print('=======================')

for url in mylist:
    print(url)

