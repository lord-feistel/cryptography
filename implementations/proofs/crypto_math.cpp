/*
 *
 * Copyright (c) 2022 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 * 
 * @date    12/03/2022
 * @author  Antonio AKA Lord Feistel
 * 
 */


#include "crypto_math.h"



/**
*
 @version        1.0
 @author        Antonio (Lord Feistel)
 @brief
    The GCD Great Common Divisor can be calculated using
 factorization e.g the gcd ( 35, 15)

    35  = 5 * 7
    15  = 3 * 5

    thus, the

    gcd ( 35 , 15) = 5

    Nevertheless the factorization for a huge number can overwhelm the machine.
    The euclidean algorithm can be used. Before that something needs to be observed:

    35 = 5 * x ;  15 = 5 * y , lets call K = 5 then,

    gcd (Kx, Ky) = gcd(K (x-y), Ky)

    e.g. gcd (35, 15)  = gcb (20,15) = 5

    It is very important that Kx > Ky

    Therefore :

    gcd(A,B) =  gcd(A - B, B) = gcd(A - 2*B, B) = gcd(A * k, B)
    As observed recursivity maybe be used.

    On purpose to reach the minimal  numbers of iterations the modular operation  can be used as follows:
	gcd (A, B) = gcd (A mod B, B)

    For instance:

    gcd (973, 301) = gcd(301, 70) = gcd(70,21) =  gcd (21, 7) = 7


    gcd (611, 507)

    611 = 1 * 507 + 104 , reminder  = 104
    507 = 5 * 104 + 91 ,  reminder  = 91
    104 = 1 * 91  + 13 ,  remminder = 13
    13  = 1 * 13  + 0  ,  reminder  =  0 


 @param     A  parameter on gcd (A, B)
 @param     B  parameter on gcd (A, B)
 @return    Greatest Common divisor

*/



//show the steps in order to verify
//#define SHOW_STEPS
uint_fast64_t gcd (uint_fast64_t A, uint_fast64_t B)
{

            // bear in mind that in the A mod B
            // must A > B

            auto x = std::min(A, B);   
            auto y = std::max(A, B);   
            
            while(x > 0)
            {
                A = y % x;
                B = x;
#ifdef SHOW_STEPS
                cout << A <<" " << B << endl;
#endif
                 // bear in mind that in the A mod B
                 // must A > B
                 x = std::min(A, B);
                 y = std::max(A, B);
            }


    return y;

}



/**

 @version   1.0
 @author    Antonio (Lord Feistel)
 @brief 
            The most important application of Algorithm of euclides in PKE is to discover
            ther modular inversion. To achieve such result the EEA ( Extended Euclidean Algorithm)
            is used. This algorithm also is known as Diophantini equation.

            i) gcd (R0, R1) = S * R0 + T * R1 
            
            then
            
            gcd (888, 54 ) = 888 (s) + 54 (t)

            888 = 54 * 6 + 24
            54 = 24*2 + 6
            ----------------  (stop when is zero)
            24 = 6*4 + 0

            thus, 

            6 = 54 - 24 * 2 = 
            54 + 24*(-2) = 
            54 + (888 - 54 * 16) * -2 = 
            54 + (888 + 54 * (-16) ) * -2 = 
            54 + 888(-2) + 54(32) = 
            888(-2) + 54(33)

            therefore : 6 = 888(-2) + 54(33) = gcd (888, 54)
            consequently s = -2 and t = 33

            It's always possible to write a gcd in a linear combination as mentioned in i 

            How To Implement ? 

            i) gcd (a, a) = ax + by

            ii) gcd (a mod b , b) = (a mod b ) x + by  

            iii) a mod b = b -  (int)(b / a) * a 

            then 

            for each iteration

            gcd (a ,b) = ((b / a) * a)x + ay
            = bx - ((b / a) *ax) + ay
            = a((b / a)x + y) + xb

            NOTE :  consider (b/a) as (int)(b / a)

            thus,

            x = y - (b/a)x
            y = x    

            NOTE : on the last iteration x = 0 and y = 1 since result is b 
            e.g. last iteratior of gcd (49, 35) is gcd (0,7)

 @param     A  parameter on dio (A, B)
 @param     B  parameter on dio (A, B)
    
 @return    return s and t regarding the fact that a gcd result equation:
            gcd(A, B) = As + Bt
*/

int_fast64_t EEA(int_fast64_t a, int_fast64_t b, int_fast64_t & x, int_fast64_t &y)
{

    // go till the last iteration
    //after come back taking the parts    
    if(a == 0)
    {
        x = 0 ;
        y = 1;

        return b;
    }

    int_fast64_t X1 ; 
    int_fast64_t Y1 ;
    int_fast64_t d = EEA(b % a, a, X1, Y1);

    // x = y - (b/a)x
    // y = x    
    x = Y1 - ( (int_fast64_t)(b / a) ) * X1;
    y = X1;

return d;
}



/**

 @version   1.0
 @author    Antonio (Lord Feistel)
 @brief 
      
      When two numbers are relative prime gcd(a, b) = 1
      what is a condition for modular inversion operation
      thus, from the linear combination previous analized

      gcd(a ,b) = st + rt = 1

      where t will be the modular inverse of such number.

      e.g.

      12 ^ 1 mod 67 using EEA we get 
      
      −5 · 67 + 28 · 12 = 1

      then 12^-1 = 28 mod 67 because

      12 * 28 = 336 = 1 mod 67

      
      recalling:

      giving M mod Z   
      
      the modular inverse is a number which N which multiply
      M such:

      M * N = 1 mod Z

 
 
 @param     m       modular parameter
 @param     number  number which the inverse will be calculated
    
 @return    return if they are relative primes and the modular inverse in this case

 NOTE: it also can be used on the calculations of AES involving Galois field on GF ( 2^8 )



**/


tuple <bool , int_fast64_t>  module_inverse(int_fast64_t number, int_fast64_t mod)
{

    int_fast64_t  s = 0 ;
    int_fast64_t  t = 0 ;
    bool isCoprime = true;

    int_fast64_t gcd = EEA(number, mod,  t, s);



    // they are not coprime
    if(gcd != 1)
        isCoprime =  false;

    //handling negatives
    if(t < 0)
        t =  (t % mod + mod) % mod ;
    
    return make_tuple(isCoprime, t) ;
}


/**

 @version   1.0
 @author    Antonio (Lord Feistel)
 @brief 
            Euler phi (m) function is the number of relative primes of m
            on the interval from 0 to m

            Theorem:

            Let m have the following canonical factorization
            
            m = P1^e1 *  Pn^en
            
            where the Pi are distinct prime numbers and e i are positive integers,
            then

            phi(m) = SUM (Pi^ei Pi^(ei -1)).

            e.g.

            example 1234 

            factoring : 2 * 617     

            phi(1234) = (2^1 - 2^0 ) * (617^1 - 617^0) = 1 * 616
     
 
 @param     m       number which will have the relative primes counted
 @return            number of relative primes

 **/

int64_t Phi(int_fast64_t m)
{
    int n_co_primes = 0;

    for(auto i = 0 ; i < m; i++)
            if(gcd(i,m) == 1)
                n_co_primes++;

    return n_co_primes;
}

/**

 @version   1.0
 @author    Antonio (Lord Feistel)
 @brief 
           Another way to invert numbers

            Euler little Theorem:

            a^p = a mod p when p is prime and a is a integer 

            a^p-1 = 1 mod p 

            if 

            a * a^p-2 = 1

         
     
 
 @param     a      base
 @param     p      exponent
 @return           number of relative primes

 **/

uint64_t euler_inversion(uint64_t a, uint64_t p)
{

    auto expoenent =  pow(a,(p-2))  ;

    //pow return double
    uint64_t result = static_cast<int> (expoenent);
    
    return ( result % p );

}


/**

 @version   1.0
 @author    Antonio (Lord Feistel)
 @brief 
            Diffie-hellman key exchange

            calculate a common key for Bob and Alice 
            key choices

            As it's only a proof of concept the numbers will be 
            restricted to 64 bits. For a real DH, routine check
            other folders 


            Works like :

            Parameters : p and g
            Alice chooses d 
            Bob  chooses  e 

            Alices does g ^ d mod p
            and sends to bob
            
            Bob does g ^ e mod p      
            and sends to Alice


            After receive:

            Bob   = key_received ^ e mod p
            Alice = key_received ^ d mod p

            As (F ^a ) ^b = (F ^b ) ^a

            Both of them will share the same key

            The Diffie Hellman uses the DLP the difficult to solve the discrete logarithm problem
            which states that the hardness of discover log A on the base P
 

 @param     p               - the prime number used on the mod operation
 @param     g               -  the generator AKA base of exponential operation
 @param     alice_choice    - integer chose by alice
 @param     bob_choice      - integer chose by bob


 @return    key_bob     - generator power Bob's integer  choice 
            key_alice   - generator powerAlice's integer  choice       

 **/

 tuple_int_int Diffie_Hellman(u_int64_t p, u_int64_t g,uint64_t alice_choice,  uint64_t bob_choice)
{
    
 
    u_int64_t key_alice = ( (u_int64_t) pow(g,alice_choice) ) % p;
    u_int64_t key_bob = ( (u_int64_t) pow(g,bob_choice) ) % p;


    u_int64_t alice_calc_key = ( (u_int64_t) pow(key_bob,alice_choice) ) % p ;
    u_int64_t bob_calc_key =   ( (u_int64_t) pow(key_alice,bob_choice) ) % p ;

 
    return make_tuple(bob_calc_key, alice_calc_key);

}



/**

 @version   1.0
 @author    Antonio (Lord Feistel)
 @brief 
            Elgamal

            Elgamal uses Diffie Hellman to implement a Public Key system.
            Bear in mind that the Diffie hellman is a key exchange system, not a public
            key encryption system once both Bob and Alice share the same key.
      
            Following how it works supposing Alice wants to encrypt the message M
            and send to Bob.

            i ) Bob choose p and g as in Diffie-Hellman and also a d which will be used to decrypt the message
            and calculate:

            B = g^d mod p and send to Alice

            ii) Alice chooses an integer i and calculates 

            1 - The ephemeral key KE
            KE = g^i mod p

            2 - The Mask Key KM
            KM = B^i mod p 
            Note: B was received by bob

            3 - Encrypt the message
            C = M * KM

            4 - Send KE and  C to Bob

            iii ) message decrypt

            1 - Bob discover the KM
            KM = KE ^ d

            2 - Decrypting message
            M = ( KM^1 ) * C mod p        

 @param     M - The prime number used on the mod operation

 @return    tuple_int_int - tuple returing the encrypted and decrypted messages    

 **/
tuple_int_int elgamal(uint64_t M)
{

    //Bob chooses d and generates B
    u_int64_t g = 2;
    u_int64_t d = 11;
    u_int64_t p = 29;

    //and calculates B
    u_int64_t B = ( (u_int64_t) pow(g,d) ) % p;

    // send (g,p,B) to Alice

    // Alice chooses i
    u_int64_t i = 5;
    // Alice calculates KE
    // IMPORTANT KE is used only one time
    // All message a new i need to be chosen   
    u_int64_t KE = ( (u_int64_t) pow(g,i) ) % p;

    //Alice calculates KM
    u_int64_t KM = ( (u_int64_t) pow(B,i) ) % p;

    //ENCRYPTION
    uint64_t C = (KM * M ) % p;

    //sends (KE, C)

    //DECRYPTION

    //bobs calculates  KM

    uint64_t KM_calculated = ( (u_int64_t) pow(KE,d) ) % p;

    // bobs calculate KM^-1 gcd

    result_inv KM_inverted = module_inverse(KM_calculated, p);

    uint64_t DM = (C * get<1> (KM_inverted))  ;//% p; 
 
    return make_tuple(C, DM);

}

/**

 @version   1.0
 @author    Antonio (Lord Feistel)
 @brief 
            RSA

            Bob

            1-  Choose p and q
            2 - n = p*q
            3 - phi(n) = (p - 1) * (q - 1)
            4 - choose e = 3
            5 - d = e^-1 = d mod phi(n)

            where d is provate key and e and n are the public key

            Alice

            1 - encrypted message = message ^  e mod n


 @param     M - The message do be encrypted and  decrypted

 @return    tuple_int_int - tuple returing the encrypted 
            and decrypted messages    

NOTE : Read theory before and be aware of the limitations of parameters.

**/

tuple_int_int RSA( uint64_t M)
{

    //bob chooses p and q
    uint64_t p = 3;
    uint64_t q = 11;

    //get n
    u_int64_t n = p * q;
    
    // phi( n ) = q-1 * p -1
    u_int64_t phy = ( (q -1) * (p -1));

    //choose some e on this case 3
    u_int64_t e = 3;

    //lets calculate the inverse of e what will be our
    // private key

    result_inv private_key =  module_inverse(e, phy);

    u_int64_t d =  get<1>(private_key);

     //send to alice ( e , n)

    //alice enmcrypt with e 
    // M^e mod n
    
    u_int64_t y = ( (u_int64_t) pow(M,e) ) % n;

    //send to bob cipher message CM to bob
    
    //Bob decrypt
     u_int64_t DM = ( (u_int64_t) pow(y,d) ) % n;
    
    return std::make_tuple(DM,d);

}
