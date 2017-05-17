// bf.h - bloom filter
// this header was provided by Darrell Long
// names of functions have been made more descriptive

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

# include "hash.h"


typedef struct bloomF {
  uint8_t *v; // Vector
  uint32_t l; // length
  uint32_t s; // salt (was s[4])
} bloomF;


// Each function has its own hash functions, determined by salt
uint32_t hashFilter(char *key)
{
  // add salt to key

  // hash it
  uint32_t index = hash((uint8_t*)key);
  return index;
}

//---newFilter-----------------------------------------------------------

// creates new bloom filter of (length, hash function)
struct bloomF *newFilter(uint32_t length, uint32_t *hashFunction)
{
  bloomF *filter;
  
  // allocate filter in memory
  filter = (bloomF*)calloc(1, sizeof(bloomF)); 

  // create vector array in memory
  filter->v = (uint8_t*)calloc(length/8+1, sizeof(uint32_t));
  filter->l = length;
  filter->s = *hashFunction; // salt? used to be a uint32_t *

  return filter;
}

//---deleteFilter--------------------------------------------------------

// delete a bloom filter
void deleteFilter(bloomF *filter)
{
  free(filter->v); // free bit vector memory
  free(filter); // free data structure
}

//---getBitValue---------------------------------------------------------

// returns value of bit in bloom filter
uint32_t getBitValue(bloomF *filter, uint32_t index)
{
  uint8_t bitValue = 0; // what gets returned
  uint8_t digit = index % 8; // get which digit you want to find
  uint8_t bitVector = (filter->v)[index/8]; // get bitVector from array

  // and bitVector with 0x1 << digit
  bitValue = bitVector & 0x1 << digit;
  if(bitValue > 0)
  {
    return 1;
  }
  return 0;
}

//---getLength-----------------------------------------------------------

// returns length of bloom filter
uint32_t getLength(bloomF *filter)
{
  return filter->l;
}

//---numBits-------------------------------------------------------------

// return number of bits set to 1 in filter
uint32_t numBits(bloomF *filter)
{
  uint32_t numberOfBits = 0;
  for (uint32_t i = 0; i < filter->l; i++)
  {
    if (getBitValue(filter, i) == 1) // found a bit
    {
      numberOfBits++;
    }
  }
  return numberOfBits;
}

//---setBit--------------------------------------------------------------

// sets an entry in bloom filter at key
void setBit(bloomF *filter, char *key)
{
  // index = hashed index % length
  uint32_t index = hashFilter(key) % (filter->l);
  printf("index: %d\n", index % (filter->l));
  filter->v[index/8] |= 0x1 << index%8;
  return;
}

//---clearBit------------------------------------------------------------

// clears an entry in bloom filter
void clearBit(bloomF *filter, char *key)
{
  uint32_t index = hashFilter(key) % (filter->l);
  printf("remove index: %d\n", index % (filter->l));
  filter->v[index/8] &= ~(0x1 << index%8);
  return;
}

//---checkMembership-----------------------------------------------------

// check membership in bloom filter
uint32_t checkMembership(bloomF *filter, char *key)
{
  if (getBitValue(filter, hashFilter(key) % (filter->l)) == 1)
  {
    return 1;
  }
  return 0;
}

//---printFilter---------------------------------------------------------

// prints bloom filter
uint32_t printFilter(bloomF *filter)
{
  for (uint32_t i = 0; i < (filter->l); i++)
  {
    printf("%d", getBitValue(filter, i));
  }
  return 1;
}
