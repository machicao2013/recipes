#!/usr/bin/env python
import random, string, sys

def random_str(randomlength=15):
    a = list(string.ascii_letters)
    random.shuffle(a)
    return ''.join(a[:randomlength])

def generate(size, length):
    for i in range(0, size):
        print random_str(length)

def run():
    if (len(sys.argv) != 3):
        print "Usage: ", sys.argv[0], "count", "string_len"
        sys.exit()
    count = int(sys.argv[1])
    length = int(sys.argv[2])
    generate(count, length)

run()

