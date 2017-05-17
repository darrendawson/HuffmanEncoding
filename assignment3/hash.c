# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include "aes.h"

// returns an int
// changed parameter from uint8_t * to char *
uint32_t hash(uint8_t *key)
{
  uint32_t  input[4] = { 0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a };
  uint32_t output[4];
  uint32_t sum = 0;
  size_t   keyLength = strlen(((char *)key));
  
  for (int i = 0; i < (int)keyLength; i += 16)
  {
    AES128_ECB_encrypt((uint8_t *) input, key + i, (uint8_t *) output);
    sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
  }
  return sum;
}
