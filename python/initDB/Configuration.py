#!/usr/bin/python
# -* - coding: UTF-8  -* -

class Configuration(object):
    def __init__(self, confName):
        super(Configuration, self).__init__()
        self.confName = confName
        self.cf = ConfigParser.ConfigParser()
        cf.read(self.confName)

    def getValue(self, section, key):
        return self.cf.cf.get("db", "db_host")
