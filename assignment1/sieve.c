/*
  sieve fills in prototypes from sieve.h
  this program finds prime numbers

  I did not write the code for sieve
  This was given to us by Derrel Long
  It is the sieve of Erosthanus
 */

#include "sieve.h"
#include <math.h>

// sets bitvector to be 1 on index of prime numbers
void sieve(bitV *vector)
{
  one(vector); // assume all numbers are prime
  
  clrBit(vector, 0); // 0 isn't prime
  clrBit(vector, 1); // 1 isn't prime
  setBit(vector, 2); // 2 is prime
  for(uint32_t i = 2; i<= sqrtl(lenVec(vector)); i++)
  {
    if(valBit(vector, i)) // It's prime
    {
      for(uint32_t k = 0; (k+i)*i <= lenVec(vector); k++)
      {
	clrBit(vector, (k+i)*i); //Its multiples, composite
      }
    }
  }
}
