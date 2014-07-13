#!/usr/bin/env python
import sys,os
from stat import *

def getAllSize(path, prefix):
	totalSize = 0
	for item in os.listdir(path):
		subpath = os.path.join(path, item)
		#print subpath
		if os.path.isfile(subpath) and item.startswith(prefix):
			totalSize += os.path.getsize(subpath)
		#mode = os.stat(subpath).st_mode
		#if S_ISREG(mode) && subpath.startswith(prefix):
		#	totalSize += os.path.getsize(subpath)
	return totalSize

if __name__ == "__main__":
	curpath = os.getcwd()
	print curpath
	totalSize = getAllSize(curpath, "statistic.log_20140311")
	totalSize += getAllSize(curpath, "al_traceroute.log_20140311")
	print "total size is %fG"% (totalSize/1024.0/1024/1024)
