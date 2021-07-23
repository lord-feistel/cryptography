#!/bin/python

import binascii
import sys
#from pysnow import *
import os
import sys
import argparse

splash = '''
  _   _   _   _   _   _     _   _   _   _   _   _  
 / \ / \ / \ / \ / \ / \   / \ / \ / \ / \ / \ / \ 
( S | i | m | p | l | e ) ( S | c | r | i | p | t )
 \_/ \_/ \_/ \_/ \_/ \_/   \_/ \_/ \_/ \_/ \_/ \_/ 

'''

	
def ReadFile():
	f = open("WB_REQ_NH.hex", "rb") 
	result = f.read()
	return result;


def build_menu(p):

	group = p.add_mutually_exclusive_group()
	direction = p.add_mutually_exclusive_group()

	#mutual excluson options
	group.add_argument('--F8', action='store_true', help="snow 3g F8")
	group.add_argument('--F9', action='store_true', help="snow 3g F9")
	
	direction.add_argument('--dec', action='store_true', help="decrypt operation")
	
	#extra parameters
	p.add_argument('--file', required=True, help="file to be used")
	p.add_argument('--key_file', required=True, help="key, IV, etc.")
	
	return p;


def main():

	if(len(sys.argv) < 2):
		print(splash)
		print('use --help to further information')
		exit();

	parser = argparse.ArgumentParser(description=splash,
		prog=sys.argv[0],
		formatter_class=argparse.RawDescriptionHelpFormatter)

	build_menu(parser)
	args = parser.parse_args()
	data = ReadFile(args.file)
	key_file = ReadFile(args.key_file)
	
	dir=0
	
	if (args.dec):
		dir=1
		
	param = key_file.split(';')	
	
	key =  int(param[0])
	count = int(param[1])
	bearer = int(param[0])
	bit_size = len(data) * 4 * 8
	
	if (args.F8):
		f8_out = snow_f8 (key, count, bearer, dir, data, bit_size)
	elif(args.F8):
		f9_out = snow_f8 (key, count, bearer, dir, data, bit_size)
	


if __name__ == "__main__": main()





