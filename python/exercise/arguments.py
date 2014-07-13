#!/usr/bin/python
# -* - coding: UTF-8  -* -

# 可变参数
def calc(*numbers):
    sum = 0
    for n in numbers:
        sum += n
    return sum

print calc(1, 2, 3, 4)
print calc(1, 2, 3, 4, 5)
print calc(1, 2, 3, 4, 5, 6)

array = [1, 2, 3, 4, 5]
print calc(*array)

def person(name, age, **kv):
    print 'name: ', name, 'age: ', age, 'other:', kv

person('machicao', 30)
person('machicao', 30, city='shenzhen')
person('machicao', 30, city='shenzhen', gender='M')

kw = {'city':'beijing', 'job':'Engineer'}
person('machicao', 30, **kw)
