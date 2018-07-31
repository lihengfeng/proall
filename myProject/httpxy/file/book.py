#!/usr/bin/python
#coding:utf-8
import sys,os
method= os.getenv('method')
params= os.getenv('params')

if method:
	print "Content-type:text/html\n"
	print '<html>'
	print '<head>'
	print '<title>BOOK</title>'
	print '</head>'
	print '<body>'
	print '<h2>'+method+'</h2>'
	print '<ul>'
	for data in params.split('&'):
		print  '<li>'+data+'</li>'
	print '</ul>'
	print '</body>'
	print '</html>'
else:
	print "Content-type:text/html\n"
	print 'no found'
