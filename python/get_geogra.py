#!/usr/bin/python
# -* - coding: UTF-8  -* -

import urllib2, string
from urllib2 import Request, urlopen

def position():
    url1 = 'http://61.4.185.48:81/g/'
    try:
        page1 = urllib2.urlopen(url1)
    except Exception, e:
        if hasattr(e, 'reason'):
            print 'check you network'
            page1 = None
        elif hasattr(e, 'code'):
            print 'check you network'
            page1 = None
    if page1:
        data1 = page1.read()
        print data1
        #city_code = data1[data1.index('d=') + 2:data1.index('d=') + 11]
        #print city_code
position()
