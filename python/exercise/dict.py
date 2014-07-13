#!/usr/bin/python
# -* - coding: UTF-8  -* -

d = {'hah':80, 'heh':70, 'ene':90}
print d['hah']
print d.get('mam')
print d.get('mam', 100)

d.pop('hah')
print d
