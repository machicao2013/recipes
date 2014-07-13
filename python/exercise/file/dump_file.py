#!/usr/bin/python
# -* - coding: UTF-8  -* -

try:
    import cPickle as pickle
except Exception, e:
    import pickle
d = dict(name='Bob', age = 20, score=88)
print pickle.dumps(d)

with open('dump.txt', 'wb') as f:
    pickle.dump(d, f)
