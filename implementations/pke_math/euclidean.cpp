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
_int gcd (_int A, _int B)
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
            gcd(A, B) = As + t
*/

s_int EEA(s_int a, s_int b, s_int & x, s_int &y)
{

    // go till the last iteration
    //after come back taking the parts    
    if(a == 0)
    {
        x = 0 ;
        y = 1;

        return b;
    }

    s_int X1 ; 
    s_int Y1 ;
    s_int d = EEA(b % a, a, X1, Y1);

    // x = y - (b/a)x
    // y = x    
    x = Y1 - ( (_int)(b / a) ) * X1;
    y = X1;

return d;
}
