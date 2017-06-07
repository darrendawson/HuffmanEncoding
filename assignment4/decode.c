/*
  Darren Dawson
  dwdawson@ucsc.edu
  Huffman Decoder
 */

# include <stdio.h>
# include <stdlib.h>
# include <getopt.h>
# include <stdbool.h>
# include <stdint.h>
# include <math.h>

# include "bitvector.h"
# include "hufftree.h"
# include "priorityqueue.h"



//---parseArguments------------------------------------------------------

// Uses command line flags to set up program
void parseArguments(int argc, char *argv[],
		    char **filepath)
{
  char arg; // use to hold argument

  while ((arg = getopt(argc, argv, "i:o:v")) != -1)
  {
    switch (arg)
    {
      case 'i': // input file
        *filepath = (char*)optarg;
	break;
      case 'o': // output destination
	//*destination = (char*)optarg;
	break;
      case 'v': // verbose mode
	//*verbose = true;
	break;
	
    }
  }
  return;
}

//---checkValidFile------------------------------------------------------

// returns true if file is an encoded file
// find files magic num -> if same as ours, then return true
bool checkValidFile(char *filePath, uint32_t magicNumber)
{
  FILE *file = fopen(filePath, "r");
  char buffer[4];
  bool result = false;
  uint32_t newMagicNumber = 0;


  // open file
  file = fopen(filePath, "rb");
  
  if (file != NULL)
  {
    fread(buffer, 1, 4, file);

    // set newMagic Num
    newMagicNumber |= ((uint8_t)(buffer[0]) << 24);
    newMagicNumber |= ((uint8_t)(buffer[1]) << 16);
    newMagicNumber |= ((uint8_t)(buffer[2]) << 8);
    newMagicNumber |= (uint8_t)(buffer[3]);

    fclose(file);
  }

  // if the magic numbers are the same, we have an encoded file
  if (magicNumber == newMagicNumber)
  {
    result = true;
  }
  
  return result;
}

//---getInfo-------------------------------------------------------------

// extracts vital information from file


//=======================================================================
//---MAIN----------------------------------------------------------------

int main(int argc, char *argv[])
{
  //-------------------------------------------
  // 1) Declare Variables
  //-------------------------------------------
  char *encodedFilePath = NULL; // file to decode
  //char *destination = NULL; // output file name
  
  uint32_t magicNumber = 0xdeadd00d;


  //-------------------------------------------
  // 2) Parse Arguments
  //-------------------------------------------
  parseArguments(argc, argv, &encodedFilePath);


  //-------------------------------------------
  // 3) Get Information
  //-------------------------------------------
  if (!checkValidFile(encodedFilePath, magicNumber))
  {
    printf("This isn't an encoded file. It cannot be decompressed\n");
    return 1;
  }

  
  //---------------------------------------------------------------------
  // exit program
  //---------------------------------------------------------------------

  return 0;
}
