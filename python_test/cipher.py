from Crypto.Cipher import AES
from Crypto.Cipher import ChaCha20
from  Crypto.Util import Counter
import binascii



def aes_teste(key,iv,):
	iv_gcm = iv[:12]
	alg=['128','192','256']
	key_increase = key[:8]
	
	for i in range(0,3):
		print('key size:' + alg[i])
		#nonce for CTR
		nonce = Counter.new(128, initial_value=int("00000000000000000000000000000000",16))
		print("ECB")
		cipher = AES.new(key, AES.MODE_ECB)
		enc_data = cipher.encrypt(data)
		print(binascii.hexlify(enc_data))
		print("CBC")
		cipher = AES.new(key, AES.MODE_CBC, iv)
		enc_data = cipher.encrypt(data)
		print(binascii.hexlify(enc_data))
		print("CTR")
		cipher = AES.new(key, AES.MODE_CTR, counter=nonce )
		enc_data = cipher.encrypt(data)
		print(binascii.hexlify(enc_data))
		print("GCM")
		cipher = AES.new(key, AES.MODE_GCM, iv_gcm )
		enc_data, tag = cipher.encrypt_and_digest(data)
		print(binascii.hexlify(enc_data) + b' tag: ' + binascii.hexlify(tag))
		print(' ')
		key = key + key_increase
		
def chacha_teste(chacha_key, iv):	
	iv_chacha = iv[:12]
	print('ChaCha20:')	
	cipher = ChaCha20.new(key=chacha_key, nonce=iv_chacha )
	enc_data = cipher.encrypt(data)
	print(binascii.hexlify(enc_data))



data = 			b"donughts!!!!!!!!"
key =			b"QATTEAMDONUGHTS!"
chacha_key =	b"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD"
iv =			b"DDDDDDDDDDDDDDDD"


aes_teste(key,iv)
chacha_teste(chacha_key,iv)






	
