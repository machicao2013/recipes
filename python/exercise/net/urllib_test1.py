#!/usr/bin/python
# -* - coding: UTF-8  -* -

import urllib
import re

webpage = urllib.urlopen('http://www.baidu.com')
text = webpage.read()
#m = re.search('<a .*? href=([^"]+).*?>.+</a>', text, re.IGNORECASE)
m = re.search('<a href="([^"]+)".*?>', text, re.IGNORECASE)
if m:
    print m.groups()
else:
    print 'no data'


