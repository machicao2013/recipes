#!/usr/bin/python
# coding: utf-8

def sunion(*multi_set):
    result = set()

    for s in multi_set:
        for elem in s:
            result.add(elem)
    return result

def sinter(*multi_set):
    sorted_multi_set = sorted(multi_set, lambda x, y: len(x) - len(y))

    result = sorted_multi_set[0].copy()

    for elem in multi_set[0]:
        for s in multi_set[1:]:
            if  (not elem in s):
                result.remove(elem)
                break
    return result

def sdiff_1(*multi_set):
    sorted_multi_set = sorted(multi_set, lambda x, y: len(x) - len(y))

    result = sorted_multi_set[0].copy();

    for elem in multi_set[0]:
        for s in sorted_multi_set[1:]:
            if elem in s:
                result.remove(elem)
                break
    return result



