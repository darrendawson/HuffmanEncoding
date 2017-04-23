/* parfait is the runner
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bv.h"
#include "sieve.h"

//---findPerfectNumbers

void findPerfectNums(bitV* primes, uint32_t *perfectNums)
{
  uint32_t numberofPNs = 0; // keeps track of how many perfect nums found

  printf("------------------\n");
  for(uint32_t i=2; i<14; i++)
  {
    if(valBit(primes, i) == 1)
    {
      // is a prime
      // formula: perfect num = 2^(p-1)*(2^p - 1)
      perfectNums = (uint32_t*)
	realloc(perfectNums, sizeof(uint32_t) * (numberofPNs + 1));

      //
      uint32_t cPNum = pow(2, i-1)*(pow(2,i) - 1);
      printf("cPNum: %d\n", cPNum);
      perfectNums[numberofPNs] = cPNum;
      numberofPNs++;
    }
  }
  printf("------------------\n");
}

//---MAIN----------------------------------------------------------------
int main()
{
  bitV* primes = newVec(10000); // create bitvector
  int bitValue = 0;
  
  // currentPrimes is used for prime factors
  uint32_t *currentPrimes;
  currentPrimes = (uint32_t*)calloc(1, sizeof(uint32_t));
  currentPrimes[0] = 2;
  uint32_t numOfPrimes = 0;

  
  sieve(primes); // create primes

  uint32_t *perfectNums;
  perfectNums = (uint32_t*)calloc(1, sizeof(uint32_t));
  findPerfectNums(primes, perfectNums);

  //---
  printf("perfect: %d, %d, %d, %d\n", perfectNums[0], perfectNums[1],
	 perfectNums[2], perfectNums[3]);
  //---


  for(uint32_t i=2; i<20; i++)
  {
    bitValue = valBit(primes, i); // determines if num is prime
    if(bitValue == 0)
    {
      
      // DETERMINE PRIME FACTORS
      printf("%d C ", i);

      uint32_t currentNumber = i;
      uint32_t j = 0;
      while(currentNumber != 1) // will end when all factors found
      {
	
	if(currentNumber % currentPrimes[j] == 0)
	{
	  // current prime number is a factor
	  printf("%d ", currentPrimes[j]);
	  currentNumber = currentNumber/currentPrimes[j];
	}
	else
	{
	  // current prime number is not a factor, move on
	  j++;
	}
      }
      printf("\n");
      // END DETERMINE PRIME FACTORS
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
  free(perfectNums);
  free(currentPrimes);
  delVec(primes);
  return 0;
}
