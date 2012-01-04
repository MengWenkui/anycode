#!/usr/bin/python

'''
Make a recycle bin for your system
Author: ZhangYoudong
Date: 2012-01-04
'''

import os
import sys


target = ''
for arg in sys.argv[1:]:
    if(arg[0] != '-'):
        target = arg

command = ''
if(target == ''):
    command += 'rm'
    for arg in sys.argv:
        command += ' ' + arg
else:
    command += 'mv ' + target + ' /tmp/huishouzhan'

os.system(command)



