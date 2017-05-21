// bf.h - bloom filter
// this header was provided by Darrell Long
// names of functions have been made more descriptive

# ifndef _BloomFilter
# define _BloomFilter

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <float.h>

# include "hash.h"

typedef struct bloomF {
  uint8_t *v; // Vector
  uint32_t l; // length
  uint32_t s[4]; // salt
} bloomF;

// Each function has its own hash functions, determined by salt
uint32_t hashFilter(bloomF *, char *); // used to be (bloom F*, char *)

// creates new bloom filter of (length, hash function)
struct bloomF *newFilter(uint32_t, uint32_t *);

// delete a bloom filter
void deleteFilter(bloomF *);

// returns value of bit in bloom filter
uint32_t getBitValue(bloomF *, uint32_t);

// returns length of bloom filter
uint32_t getLength(bloomF *);

// return number of bits in bloom filter
uint32_t numBits(bloomF *);

// sets an entry in bloom filter at key
void setBit(bloomF *, char *);

// clears an entry in bloom filter
void clearBit(bloomF *, char *);

// check membership in bloom filter
uint32_t checkMembership(bloomF *, char *);

// prints bloom filter
uint32_t printFilter(bloomF *);

// returns percent that filter is filled
float findPercentFull(bloomF *);


# endif
