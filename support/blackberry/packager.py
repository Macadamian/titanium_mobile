#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Appcelerator Titanium Mobile
# Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License
# Please see the LICENSE included with this distribution for details.
#
# Blackberry Application Script
#

import os, sys, platform, subprocess

class BlackberryPackager(object):
	def __init__(self, command):
		self.command = command
		
	def package(self):
		try:
			subprocess.check_output(self.command, stderr = subprocess.STDOUT)
		except subprocess.CalledProcessError, cpe:
			print >>sys.stderr, cpe, cpe.output
			return
		except OSError, e:
			print >>sys.stderr, e
			return


if __name__ == '__main__':

	if platform.system() == 'Windows':
		command = ['blackberry-nativepackager.bat']
	else
		command = ['blackberry-nativepackager']
	for n in range(1, len(sys.argv)):
		command.append(sys.argv[n])

	packager = BlackberryPackager(command)
	packager.package()