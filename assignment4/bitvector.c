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

//---getByteValue--------------------------------------------------------

// returns byte at certain index
uint8_t getByteValue(bitV *vector, uint32_t index)
{
  uint8_t byteValue = 0;
  for (int i = 0; i < 8; i++)
  {
    byteValue |= getBitValue(vector, (index+1)*8 - i - 1) << (i);
  }
  //printf("%u\n", byteValue);
  return byteValue;
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

//---appendUInt32--------------------------------------------------------

// adds an int to the end of  a bit vector
void appendUInt32(bitV *vector, uint32_t bits)
{
  for (int i = 31; i >= 0; i--)
  {
    // if bit at i in int is set to 1 -> appendBit(true)
    if (bits & (1 << i))
    {
      appendBit(vector, true);
    }
    else
    {
      appendBit(vector, false);
    }
  }
  return;
}

//---appendUInt64--------------------------------------------------------

// adds an int to the end of a bit vector
void appendUInt64(bitV *vector, uint64_t bits)
{
  for (int i = 63; i >= 0; i--)
  {
    // if bit at i in int is set to 1 -> appendBit(true)
    if (bits & (1 << i))
    {
      appendBit(vector, true);
    }
    else
    {
      appendBit(vector, false);
    }
  }
  return;
}

//---appendUInt16--------------------------------------------------------

// adds an int to the end of  a bit vector
void appendUInt16(bitV *vector, uint16_t bits)
{
  for (int i = 15; i >= 0; i--)
  {
    // if bit at i in int is set to 1 -> appendBit(true)
    if (bits & (1 << i))
    {
      appendBit(vector, true);
    }
    else
    {
      appendBit(vector, false);
    }
  }
  return;
}

//---appendUInt8---------------------------------------------------------

// adds an int to end of bit vector
void appendUInt8(bitV *vector, uint8_t bits)
{
  for (int i  = 7; i >=0; i--)
  {
    if (bits & (1 <<i))
    {
      appendBit(vector, true);
    }
    else
    {
      appendBit(vector, false);
    }
  }
  return;
}

//---appendString--------------------------------------------------------

// adds a string's bits to the end of bit vector
void appendString(bitV *vector, char *string, uint32_t size)
{
  uint8_t currentByte;

  //printf("Append String!\n");
  // go through byte by byte
  for (uint32_t i = 0; i < size; i++)
  {
    currentByte = string[i];

    // add bits
    for (int i = 7; i >= 0; i--)
    {
      if (currentByte & (1 << i))
      {
	//printf("1");
	appendBit(vector, true);
      }
      else
      {
	//printf("0");
	appendBit(vector, false);
      }
    }
    //printf("\n");
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
  if (vector != NULL)
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
  }
  //printf("\n");
  return;
}
