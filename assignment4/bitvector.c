# include "bitvector.h"

//---newBitVector--------------------------------------------------------

// creates a new bit vector
bitV *newBitVector(uint32_t newSize)
{
  bitV *vector = (bitV*)calloc(1, sizeof(bitV));

  vector->bits = (uint8_t*)calloc(newSize/8 + 1, sizeof(uint32_t));
  vector->size = newSize;
  vector->lastBit = -1; // account for off by one error

  return vector;
}

//---deleteBitVector-----------------------------------------------------

// deletes a bit vector
void deleteBitVector(bitV *vector)
{
  free(vector->bits);
  free(vector);
  return;
}

//---setBit--------------------------------------------------------------

// sets bit at index to be equal to 1
void setBit(bitV *vector, uint32_t index)
{
  vector->bits[index/8] |= 0x1 << index%8;
  return;
}

//---clearBit------------------------------------------------------------

// sets bit at index to be equal to 0
void clearBit(bitV *vector, uint32_t index)
{
  vector->bits[index/8] &= ~(0x1 << index%8);
  return;
}

//---getBitValue---------------------------------------------------------

// returns value of bit at index, true if 1
bool getBitValue(bitV *vector, uint32_t index)
{
  uint8_t bitValue = 0;
  uint8_t byte = (vector->bits)[index/8];

  bitValue = byte & 0x1 << (index % 8);
  if (bitValue != 0)
  {
    return true;
  }
  return false;
}

//---appendBit-----------------------------------------------------------

// attach a bit to end of vector, increment lastBit
void appendBit(bitV *vector, bool set)
{
  vector->lastBit += 1; // increment location of last bit (we care about)

  if (set)
  {
    setBit(vector, vector->lastBit);
  }
  else
  {
    clearBit(vector, vector->lastBit);
  }
  return;
}

//---appendCode----------------------------------------------------------

// adds one bitvector to the end of another
void appendCode(bitV *vector, bitV *code)
{
  for (uint32_t i = 0; i <= code->lastBit; i++)
  {
    appendBit(vector, getBitValue(code, i));
  }
  return;
}

//---removeBitFromEnd----------------------------------------------------

// removes the very last bit we care about
void removeBitFromEnd(bitV *vector)
{
  vector->lastBit -= 1;
  return;
}

//---printBitVector------------------------------------------------------

// prints the vector (up to the index we care about)
void printBitVector(bitV *vector)
{
  if (vector->lastBit != (uint32_t)-1)
  {
    for (uint32_t i = 0; i <= vector->lastBit && i < vector->size; i++)
    {
      printf("%d", getBitValue(vector, i));
    }
  }
  else
  {
    printf("Empty");
  }
  printf("\n");
  return;
}
