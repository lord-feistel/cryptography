import binascii
#need to install pycrypto or dont work
from Crypto.Cipher import AES


s_box = (
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16,
)

inv_s_box = (
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D,
)

Round_keys = [

'000102030405060708090a0b0c0d0e0f',
'd6aa74fdd2af72fadaa678f1d6ab76fe',
'b692cf0b643dbdf1be9bc5006830b3fe',
'b6ff744ed2c2c9bf6c590cbf0469bf41',
'47f7f7bc95353e03f96c32bcfd058dfd',
'3caaa3e8a99f9deb50f3af57adf622aa',
'5e390f7df7a69296a7553dc10aa31f6b',
'14f9701ae35fe28c440adf4d4ea9c026',
'47438735a41c65b9e016baf4aebf7ad2',
'549932d1f08557681093ed9cbe2c974e',
'13111d7fe3944a17f307a78b4d2b30c5'

]

'''
 
 if would be in C++ we could define as a macro 
 
'''

# AUXILIARY FUNCTIONS

def xor(a, b):
    _result = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]
    for i in range(0, 4):
        for j in range(0, 4):
            _result[i][j] = a[i][j] ^ b[i][j]
    return _result

def KeyToByte(k):
    L=[]
    for i in k:
        L.append(binascii.unhexlify(i))
    return L


def Multiplication(n, m):
    '''
    Explanation :
    multiplication by 2 :
    (n left shift 1) mod 0x1b ( as suggested in  the paper or books )
    multiplication by 3 :
    n = 2 * n + n  e. g
    3 * 2 = 2 * 2 + 2 = 6
    as = operation is xor
    (n left shift 1)  + n  mod 0x1b
    '''
    if m == 2 :
        r = ((n << 1) & 0xff)
        if (n & 0x80):
            r = r ^ 0x1b
        return  r
    elif m == 3 :
        r = (n << 1) & 0xff
        r = r ^ n
        if (n & 0x80) :
            r = r ^ 0x1b
        return  r
    else :
        return n


def ShiftLine(s, n):

    for k in range(0,n):
        tmp = s[0]
        for i in range(1,len(s)):
            s[i-1]  = s[i]
        s[len(s) - 1] = tmp

    return s


def SboxReturn(b):
    a = (b & 0x0f)
    c = (b & 0xf0) >> 4
    _index = c * 16 + a
    return int(s_box[_index])

def bytes2matrix(text):
    """ Converts a 16-byte array into a 4x4 matrix.  """
    return [list(text[i:i+4]) for i in range(0, len(text), 4)]

def matrix2bytes(matrix):
    """ Converts a 4x4 matrix into a 16-byte array.  """
    return bytes(sum(matrix, []))

def InvMatrix(m):

    m_inv = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]


    for i in range(0, len(m)):
        for j in range(0,len(m)):
            m_inv[i][j] = m[j][i]

    return m_inv

def MatrixElementMul(x , y):

    element = 0

    for i in range(0,4):
        r = Multiplication(x[i], y[i])
        element  = element ^  r

    return element

# MAIN FUNCTIONS

def ByteSub(state):
    for i in range(0, 4):
        for j in range(0, 4):
            state[i][j]  = SboxReturn(state[i][j])
    return state

def ShiftRown(state):
        state = InvMatrix(state)

        ShiftLine(state[1], 1)
        ShiftLine(state[2], 2)
        ShiftLine(state[3], 3)

        state = InvMatrix(state)

        return state

def xtime( x):
  return ((x<<1) ^ (((x>>7) & 1) * 0x1b))



def MixColumn(state):

    Mix_Collum_result = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]

    Mix_Collum_matrix = [
        [2, 3, 1, 1],
        [1, 2, 3, 1],
        [1, 1, 2, 3],
        [3, 1, 1, 2]

    ]

    #state = InvMatrix(state)

    for i in range(0,4):
        for j in range(0,4):
            Mix_Collum_result[i][j] = MatrixElementMul(state[i], Mix_Collum_matrix[j])

    return Mix_Collum_result



def PrepareInputs(s):

    _out=[]
    result = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]

    c = 0

    for i in range(0,len(s),2):
        _out.append(int(s[i:i+2], 16))


    for i in range(0,len(result)):
        for j in range(0,len(result)):
            result[i][j] = _out[4 *i + j]


    return result


if __name__ == "__main__":

    input = '6bc1bee22e409f96e93d7e117393172a'

    I = PrepareInputs(input)
    K = PrepareInputs(Round_keys[0])

    _input = xor(I,K)

    for i in range(1,11):
        S = ByteSub(_input)
        T = ShiftRown(S)
        if i < 10:
            F = MixColumn(T)
        else:
            F = T
        K = PrepareInputs(Round_keys[i])
        _input = xor(F, K)

    st = ''
    for i in range(0,4):
        for j in range(0,4):
		
            st = st +  str("{:02x}".format(_input[i][j]))

    print(st.encode())

    cipher = AES.new(binascii.unhexlify(b'000102030405060708090a0b0c0d0e0f'), AES.MODE_ECB)
    print ( binascii.hexlify(cipher.encrypt(binascii.unhexlify(b'6bc1bee22e409f96e93d7e117393172a'))))
	




