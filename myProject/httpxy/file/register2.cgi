#!/usr/bin/python
#coding:utf-8

import sys,os
length = os.getenv('Content-Length')

if length:
	postdata = sys.stdin.read(int(length))
	print "Content-type:text/html\n"
	print '<html>'
	print postdata
else:
	print "Content-type:text/html\n"
	print 'no found'
