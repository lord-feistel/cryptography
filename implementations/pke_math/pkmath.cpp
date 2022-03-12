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


int main()
{

    s_int s = 0 ;
    s_int t = 0 ;

    cout << "The greatest common divisor between 973 and 301 : " << endl << gcd(973, 301) << endl ; 

    EEA(973, 301, s, t);
    cout << "The s and t for  973 and 301 : " << endl << s << " "<< t << endl ; 

    return 0 ;

}
