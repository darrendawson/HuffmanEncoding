/* parfait is the runner
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
#include "sieve.h"


//---MAIN----------------------------------------------------------------
int main()
{
  bitV* primes = newVec(10000); // create bitvector
  int bitValue = 0;
  
  // int[] currentPrimes
  uint32_t *currentPrimes;
  currentPrimes = (uint32_t*)calloc(1, sizeof(uint32_t));
  currentPrimes[0] = 2;
  uint32_t numOfPrimes = 0;
  
  sieve(primes); // create primes

  for(uint32_t i=2; i<10000; i++)
  {
    bitValue = valBit(primes, i); // determines if num is prime
    if(bitValue == 0)
    {
      
      // determine prime factors
      printf("%d C ", i);
      //----
      uint32_t currentNumber = i;
      uint32_t j = 0;
      while(currentNumber != 1)
      {
	
	if(currentNumber % currentPrimes[j] == 0)
	{
	  // current prime number is a factor
	  printf("%d ", currentPrimes[j]);
	  currentNumber = currentNumber/currentPrimes[j];
	}
	else
	{
	  j++;
	}
      }
      printf("\n");
      //----
    } 
    else // if(bitValue == 1)
    {
      // number is prime
      // reallocate memory for currentPrimes array, add current num
      currentPrimes = (uint32_t*)
	realloc(currentPrimes, sizeof(uint32_t) * (numOfPrimes + 2));
      currentPrimes[numOfPrimes] = i;
      numOfPrimes++;
      printf("%d P\n", i);
    }
  }
 

  //exit program
  free(currentPrimes);
  delVec(primes);
  return 0;
}
