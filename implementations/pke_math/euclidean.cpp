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

#include "general.h"
#include "euclidean.h"



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
    cout << (t % mod + mod) % mod ;
    
    return make_tuple(isCoprime, t) ;
}
