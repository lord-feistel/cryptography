from Crypto.Hash import HMAC, SHA256

secret = b'Swordfish'
h = HMAC.new(secret, digestmod=SHA256)
h.update(b'Hello')
print (h.hexdigest())