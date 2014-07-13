#!/usr/bin/python
# -* - coding: UTF-8  -* -

class Bird(object):
    """docstring for Bird"""
    def __init__(self, age = 20):
        super(Bird, self).__init__()
        self.age = age

class SongBird(Bird):
    """docstring for SongBird"""
    def __init__(self, song):
        super(SongBird, self).__init__()
        self.song = song

songBird = SongBird('haha')
print songBird.age
