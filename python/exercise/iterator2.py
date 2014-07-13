#!/usr/bin/python
# -* - coding: UTF-8  -* -

class TestIterator(object):
    """docstring for TestIterator"""
    value = 0
    def __init__(self):
        super(TestIterator, self).__init__()
    def next(self):
        self.value += 1
        if self.value > 10:
            raise StopIteration
        return self.value
    def __iter__(self):
        return self

ti = TestIterator()
print list(ti)
