#!/usr/bin/python
import sys


def test():
	postData=sys.stdin.read(15)
	for arg in postData.split('&'):
		print arg
	print"22222222" 

test()
