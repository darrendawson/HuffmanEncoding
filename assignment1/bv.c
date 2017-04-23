/*
  bv.c - fills out bv.h (bit vector)
  Darren Dawson, dwdawson@ucsc.edu
  cmps 12b,  Assignment 1
 */

#include "bv.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//---newVect-------------------------------------------------------------

// creates a new bit vector of specified length
// code for newVect was lectured on in class
// returns pointer to the bitvector we created
bitV* newVec(uint32_t newSize)
{
  bitV *t;
  t = (bitV*)calloc(1, sizeof(bitV)); // create bitV t in memory

  //create bitvector array in memory
  t->v = (uint8_t*)calloc(newSize/8+1, sizeof(uint32_t)); 
  t->l = newSize; // assign l as size of bitvector
  return t;
}

//---delVec--------------------------------------------------------------

// deletes a vector (without memory leak)
// delete things it points to, then delete it
void delVec(bitV *vector)
{
  free(vector->v); // free the bit vector array 
  free(vector); // free the bit vector data type
}


//---one-----------------------------------------------------------------

// sets bit in bit vector to 1
void one(bitV *vector)
{
  // l = length of bit vector
  for(uint32_t i=0; i < vector->l; i++)
  {
    setBit(vector, i);
  }
 
}

//---setBit--------------------------------------------------------------

// make bit at specified index to 1
// this code was lectured on in class
void setBit(bitV *vector, uint32_t index)
{
  vector->v[index/8] |= 0x1 << index%8;
  return;
}

//---clrBit--------------------------------------------------------------

// sets bit at specified index to 0
// this function was lectured on in class
void clrBit(bitV *vector, uint32_t index)
{
  vector->v[index/8] &= ~(0x1 << index%8);
  return;
}

//---valBit--------------------------------------------------------------

// returns value of bit at index
uint8_t valBit(bitV *vector, uint32_t index)
{
  uint8_t bitValue = 0; // what gets returned
  uint8_t digit = index % 8; // get which digit you want to find
  uint8_t bitVector = (vector->v)[index/8]; // get bitVector from array

  // and bitVector with 0x1 << digit
  bitValue = bitVector & 0x1 << digit;
  if(bitValue > 0)
  {
    return 1;
  }
  return 0;
}


//---lenVec------------------------------------------------------------

// returns length of vector
uint32_t lenVec(bitV *vector)
{
  return vector->l;
}

