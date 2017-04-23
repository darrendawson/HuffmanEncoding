/* parfait is the runner
   Darren Dawson, dwdawson@ucsc.edu
   CMPS 12b, assignment 1
   The Sieve function was not written by me, it was provided
     by the cmps12b instructor, darrel long.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bv.h"
#include "sieve.h"

//---findPerfectNumbers--------------------------------------------------

// finds the perfect numbers, adds them to int array
void findPerfectNums(bitV* primes, uint32_t *perfectNums)
{
  uint32_t numberofPNs = 0; // keeps track of how many perfect nums found

  for(uint32_t i=2; i<20; i++)
  {
    if(valBit(primes, i) == 1)
    {
      // is a prime
      // formula: perfect num = 2^(p-1)*(2^p - 1)
      perfectNums = (uint32_t*)
	realloc(perfectNums, sizeof(uint32_t) * (numberofPNs + 1));

      //
      uint32_t cPNum = pow(2, i-1)*(pow(2,i) - 1);
      perfectNums[numberofPNs] = cPNum;
      numberofPNs++;
    }
  }
}

//---bubbleSort----------------------------------------------------------

void bubbleSort(uint32_t *factors, uint32_t size)
{
  uint32_t temp;
  for(uint32_t i = 0; i<(size-1); i++)
  {
    for(uint32_t j = 0; j<(size-1-i); j++)
    {
      if(factors[j] > factors[j+1])
      {
	temp = factors[j];
	factors[j] = factors[j+1];
	factors[j+1] = temp;
      }
    }
  }
}

//---MAIN----------------------------------------------------------------
int main(int argc, char *argv[])
{
  uint32_t totalSize = 0; // how many numbers we want to check to
  // set size of loop (variable of how many numbers to process)
  if(argc<=1)
  {
    // no command line argument -> set default
    totalSize = 100001;
  }
  else
  {
    totalSize = atoi(argv[1]) + 1; // set size to first num in command line 
  }
  
  bitV* primes = newVec(totalSize); // create bitvector
  int bitValue = 0;
  
  // currentPrimes is used to store prime numbers up to a number
  uint32_t *currentPrimes;
  currentPrimes = (uint32_t*)calloc(1, sizeof(uint32_t));
  currentPrimes[0] = 2;
  uint32_t numOfPrimes = 0;
  
  sieve(primes); // create primes

  // find indexes of perfect numbers
  uint32_t perfectIndex = 0; // used to track how many perfect numbers
                             // the program has already counted
  uint32_t *perfectNums;     // perfectNums = array of perfect nums
  perfectNums = (uint32_t*)calloc(1, sizeof(uint32_t));
  findPerfectNums(primes, perfectNums);
  


  
  // LOOP THROUGH REAL NUMBERS----------
  for(uint32_t i=2; i<totalSize; i++)
  {
    bitValue = valBit(primes, i); // determines if num is prime
    if(bitValue == 0) //composite
    {	 
      // Composite -> DETERMINE PRIME FACTORS
      uint32_t currentNumber = i;
      uint32_t j = 0; // loop limit
      printf("%d C: ", i);

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

      
      // CHECK IF PERFECT NUM
      if(i == perfectNums[perfectIndex])
      {
	uint32_t *factors;
	factors = (uint32_t*)calloc(1, sizeof(uint32_t));
	uint32_t numOfFactors = 0;
	
	uint32_t currentNumber = i;
	printf("%d E: 1 ", i);

	//--- get factors
	for(uint32_t j = 0; j<numOfPrimes; j++) 
	{
	
	  if(currentNumber % currentPrimes[j] == 0)
	  {
	    factors[numOfFactors] = currentPrimes[j];
	    numOfFactors++;


	    //check to see if currentnum/prime is a prime
	    if(valBit(primes, currentNumber/currentPrimes[j]) == 0)
	    {
	      factors[numOfFactors] = currentNumber/currentPrimes[j];
	      numOfFactors++;
	    }
	   

	    factors = (uint32_t*)
	      realloc(factors, sizeof(uint32_t) * (numOfFactors + 2));
	  }
	} // end get factors---

	bubbleSort(factors, numOfFactors); // sort for size
	
	for(uint32_t i=0; i<numOfFactors; i++)
	{
	  printf("%d ", factors[i]); // print out factors 
	}

	// move on
	free(factors);
	perfectIndex++;
	printf("\n");
      }
      //END CHECK IF PERFECT NUM


      
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
