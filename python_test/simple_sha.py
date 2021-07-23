from Crypto.Hash import SHA3_224
from Crypto.Hash import SHA3_256
from Crypto.Hash import SHA3_384
from Crypto.Hash import SHA3_512
import hashlib
import binascii


	
#sha256

def sha256(st):
	print('\nsha256:')
	result = hashlib.sha256(st).hexdigest()
	return result








input='AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
ipad ='CCCCCCCC' 
opad ='DDDDDDDD'

input = input + ipad
opad = opad.encode()
input=input.encode()




output = sha256(input)
output = output.encode()
print(output)
print(opad)


output = output + opad
print(output)

print(sha256(output))



