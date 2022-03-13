
#include "tests.h"

void TESTE_EUCLIDES()
{
    uint_fast64_t result = gcd(973, 301);
    assert(result == 7);

}

void TESTE_EXTENDED_EUCLIDES()
{
    int_fast64_t  s = 0 ;
    int_fast64_t  t = 0 ;

    EEA(973, 301, s, t);
    assert(s ==13 && t == -42);

}

void TESTE_MODULAR_INVERSION()
{

    int_fast64_t  number = 12 ;
    int_fast64_t  module = 67 ;

    auto result = module_inverse(number,module);
 
    assert(get<0>(result) == true);
    assert(get<1>(result) == 28);

    result = module_inverse(1693, 271);
    
    assert(get<0>(result) == true);
    assert(get<1>(result) == 89);

 
}

void TESTE_EULER_PHI()
{
    auto n =  Phi(5);
    assert(n == 4);

}


void TESTE_EULER_INVERTION()
{
    auto inverted = euler_inversion(2, 7);
    
    //checking inversion
    assert( ( (2 * inverted) % 7 == 1) );

}


    




