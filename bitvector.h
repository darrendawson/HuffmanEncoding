/*
  Darren Dawson, dwdawson@ucsc.edu
  Bit Vector that keeps track of which bits we care about
 */

# ifndef _Bit_Vector
# define _Bit_Vector

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct bitV
{
  uint8_t *bits; // the bitvector
  uint32_t lastBit; // index of last bit we care about
  uint32_t size; // total size of memory allocated
} bitV;

// create a new vector
bitV *newBitVector(uint32_t);

// delete a vector
void deleteBitVector(bitV *);

// set a bit
void setBit(bitV *, uint32_t);

// clear a bit
void clearBit(bitV *, uint32_t);

// get value of bit
bool getBitValue(bitV *, uint32_t);

// get byte
uint8_t getByteValue(bitV *, uint32_t);

// add bit to end of vector
void appendBit(bitV *, bool);

// add a code to end of vector
void appendCode(bitV *, bitV *);

// add an integer's bits to end of vector
void appendUInt32(bitV *, uint32_t);

void appendUInt64(bitV *, uint64_t);

void appendUInt16(bitV *, uint16_t);

void appendUInt8(bitV *, uint8_t);

void appendString(bitV *, char *, uint32_t);

// remove last bit of vector (that we care about)
void removeBitFromEnd(bitV *);

// opens a file, converts file's bits into bit vector
void convertFileToBitVector(char *, bitV **);

// saves bits in vector to a file
void dumpBitVectorToFile(bitV *, char *);

// prints the vector
void printBitVector(bitV *);

# endif
