def gcdExtended(a, b):  
    # Base Case  
    if a == 0 :   
        return b,0,1
             
    gcd,x1,y1 = gcdExtended(b%a, a)  
        
    x = y1 - (b//a) * x1  
    y = x1  
     
    return gcd,x,y 
      
def rsa(p,q, e):
	n = p * q
	phi = (p-1) * (q -1)
	gcd,x,y = gcdExtended(phi, e)
	return y, e, phi , n
	
	
private , public, private_mod, public_mod =  rsa(47,43, 5)
print ('private key:', private, 'private mod:', private_mod)
print ('public key:', public, 'public mod:', public_mod)

m = 4
print('message : ' , m)
x = (m**public) % public_mod
print('encrypted:', x)

y = (x**private) % public_mod

print('decrypted:', y)









	
	
