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


#ifndef __EUCLIDEAN__
#define __EUCLIDEAN__

#include "general.h"
#include <math.h>


//extend euclidean algorithm
int_fast64_t EEA(int_fast64_t a, int_fast64_t b, int_fast64_t & x, int_fast64_t &y);

//gcd using euclidean algorithm
uint_fast64_t gcd (uint_fast64_t A, uint_fast64_t B);

//it calculates the modular inverse of a number if exist
//using extend euclidean algorithm
tuple <bool , int_fast64_t>  module_inverse(int_fast64_t number, int_fast64_t mod);

// euler phi function
int64_t Phi(int_fast64_t m);

// using Euler theorem ro perform a modualr inversion
uint64_t euler_inversion(uint64_t a, uint64_t p);

// simple demonstration how works diffie hellman
// a class diffie hellman could be created to be ore elegant.
tuple_int_int Diffie_Hellman(u_int64_t p, u_int64_t g,uint64_t alice_choice,  uint64_t bob_choice);

//perform a simple demonstration of elgamal
// return the result of encryption and decryption
tuple_int_int elgamal(uint64_t M);

//perform RSA with small numbers
tuple_int_int RSA( uint64_t M);


#endif
