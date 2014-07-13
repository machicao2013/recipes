#!/usr/bin/python
# -* - coding: UTF-8  -* -

L = ['mam', 'hah', 'heh']
print L[0], L[1], L[2]

r = []
n = 3
for i in range(n):
    r.append(L[i])
print r

a = L[0:3]
print L
a[2] = 400
print L
