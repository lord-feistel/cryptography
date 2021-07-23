from Crypto.Hash import SHA3_224
from Crypto.Hash import SHA3_256
from Crypto.Hash import SHA3_384
from Crypto.Hash import SHA3_512
import hashlib
import binascii


#md5
def md5(st):
	print('md5')
	result = hashlib.md5(st).hexdigest()
	print(result)
	
############################################################################	
	
#sha256
def sha1(st):
		print('\nsha1:')
		result = hashlib.sha1(st).hexdigest()
		print(result)
	
############################################################################
	
	
#sha256

def sha256(st):
	print('\nsha256:')
	result = hashlib.sha256(st).hexdigest()
	print(result)


#sha224

def sha224(st):
	print('\nsha224:')
	result = hashlib.sha224(st).hexdigest()
	print(result)

#sha384

def sha384(st):
	print('\nsha384:')
	result = hashlib.sha384(st).hexdigest()
	print(result)


#sha512

def sha512(st):
	print('\nsha512:')
	result = hashlib.sha512(st).hexdigest()
	print(result)

############################################################################

def sha3_224(st):
	print('\nsha3 224:')
	h_obj = SHA3_224.new()
	h_obj.update(st)
	print (h_obj.hexdigest())

def sha3_256(st):
	print('\nsha3 256:')
	h_obj = SHA3_256.new()
	h_obj.update(st)
	print (h_obj.hexdigest())
	
	
def sha3_384(st):
	print('\nsha3 384:')
	h_obj = SHA3_384.new()
	h_obj.update(st)
	print (h_obj.hexdigest())	

	
def sha3_512(st):
	print('\nsha3 512:')
	h_obj = SHA3_512.new()
	h_obj.update(st)
	print (h_obj.hexdigest())	






input='AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
input=input.encode()


#md5
md5(input)

#sha1
sha1(input)

#sha2
sha224(input)
sha256(input)
sha384(input)
sha512(input)

#sha3
sha3_224(input)
sha3_256(input)
sha3_384(input)
sha3_512(input)



