#!/usr/bin/env python


from struct import *
import serial
import os, sys
from collections import namedtuple

"""
class SerailGateway():
	
	def __int__():
		SerailPort = '/dev/ttyBlue'
		SerialBaud = 115200
		SerialTimeout = 0.25
		try:
			''' Attempt to connect '''
			self.Serial = serial.Serial(SerailPort, SerialBaud, SerialTimeout)
		except:
			print "Failed to initialize Serial port"
			sys.exit(1)

	def packData:
		x = pack('ic')



if __name__ == '__main__':
"""

# Convert Float to hex
import struct

def check_length(s):
	'''
		Pad values where string translation trims leading zero (0)
	'''
	if len(s) & 1:
		return '0' + s
	else: 
		return s
def string_to_hex(s):
	'''
		Return string for translation
	'''
	s = check_length(s)
	return s.decode("hex")

def float_to_hex(f):
	''' 
		Convert floating point number to hex.
		Return hex value as string
		!! Return BIG ENDIAN
	'''
	return hex(struct.unpack('>I', struct.pack('<f', f))[0])[2:]

def int_to_hex(i):
	'''
		Convert integer value to hex
		Return hex value as string
		!! Convert to BIG ENDIAN
	'''
	return hex(struct.unpack('>I', struct.pack('<i', i))[0])[2:]

def uint_to_hex(u):
	'''
		Convert unsigned integer value to hex
		Return hex value as string
		!! Convert to BIG ENDIAN
	'''
	return hex(struct.unpack('>I', struct.pack('<I', u))[0])[2:]	

#if '__name__' = '__main__':

