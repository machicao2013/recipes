#!/usr/bin/python
# -* - coding: UTF-8  -* -

class MapTableNameToSQL(object):
    '''
        mapping tablename to create table sql accroding to fileName
    '''
    def __init__(self, fileName):
        super(MapTableNameToSQL, self).__init__()
        #fileName = 'result.sql'
        self.fileName = fileName
        self.create_table_sqls = {}

    def initMap(self):
        f = open(self.fileName, 'r')#{{{
        first_table = True
        cur_create_table_sql = ""

        while True:
            line = f.readline()
            if line:
                if line.startswith("**"):
                    if not first_table:
                        self.create_table_sqls[tableName] = cur_create_table_sql
                    line = f.readline()
                    pos = line.find(":")
                    tableName = (line[pos+1:]).strip()
                    line = f.readline()
                    pos = line.find(":")
                    cur_create_table_sql = (line[pos+1:]).lstrip()
                    first_table = False
                else:
                    cur_create_table_sql += line
            else:
                    break
        f.close()#}}}

    def getAll(self):
        return self.create_table_sqls

    def getSQL(self, tableName):
        if tableName in self.create_table_sqls:
            return self.create_table_sqls[tableName]
        else:
            return None

    def getTotalCount(self):
        return len(self.create_table_sqls)

if __name__ == '__main__':
    mapping = MapTableNameToSQL('result.sql')
    mapping.initMap()
    print mapping.getSQL("sd_url_info_modify")
    print mapping.getSQL("sd_url_info_modify_2")

