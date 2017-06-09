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

//---convert32BitToInt---------------------------------------------------

// converts 32 bit string into int
uint32_t convert32BitToInt(char *bits)
{
  uint32_t result = 0;

  result |= ((uint8_t)(bits[0]) << 24);
  result |= ((uint8_t)(bits[1]) << 16);
  result |= ((uint8_t)(bits[2]) << 8);
  result |= (uint8_t)(bits[3]);

  return result;
}

//---convert16BitToInt---------------------------------------------------

// converts 16 bit string into an int
uint16_t convert16BitToInt(char *bits)
{
  uint16_t result = 0;

  result |= ((uint8_t)(bits[0]) << 8);
  result |= ((uint8_t)(bits[1]));
  //printf("[%01x][%01x]\n", bits[0], bits[1]);
  
  return result;
}

//---convert64BitToInt---------------------------------------------------

// converts a 64 bit string into an int
uint64_t convert64BitToInt(char *bits)
{
  uint64_t result = 0;
 
  result = convert32BitToInt(bits) << 31;
  result = convert32BitToInt(bits+4);
  
  return result;
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

  // get magic numbers
  if (file != NULL)
  {
    fread(buffer, 1, 4, file);

    // set newMagic Num
    newMagicNumber = convert32BitToInt(buffer);

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
void getInfo(char *filePath, uint64_t *sizeOfOriginal, uint16_t *sizeOfTree,
	     char **treeInstructions)
{
  FILE *file = fopen(filePath, "rb");
  char *buffer;
  long fileSize;

  // get size of file
  fseek(file, 0, SEEK_END);
  fileSize = ftell(file);
  rewind(file);

  // allocate memory and read file
  buffer = (char*)calloc(fileSize, sizeof(char));
  fread(buffer, 1, fileSize, file);
  
  // get original file size | bytes [4-11]
  *sizeOfOriginal = convert64BitToInt(buffer + 4);
  
  // get size of tree | bytes [12-13]
  *sizeOfTree = convert16BitToInt(buffer + 12);
  
  // get encoded tree instructions
  //   start at byte 14, get next sizeOfTree bytes
  *treeInstructions = (char*)calloc(*sizeOfTree, sizeof(char));
  for (int i = 0; i < *sizeOfTree; i++)
  {
    (*treeInstructions)[i] = buffer[14 + i];
  }


  printf("Size of Original: %lu\n", *sizeOfOriginal);
  printf("Size of Tree: %d\n", *sizeOfTree);
  
  free(buffer);
  fclose(file);
  return;
}

//---convertFileToBitVector----------------------------------------------

// opens a file, converts file's bits into bit vector
void convertFileToBitVector(char *filepath, bitV **vector)
{
  FILE *file;
  long fileSize;
  char *buffer;
  //uint8_t currentByte;

   
  // open file
  file = fopen(filepath, "r");

  // get size of file
  fseek(file, 0, SEEK_END);
  fileSize = ftell(file);
  rewind(file);

  *vector = newBitVector(fileSize *10);

  // allocate memory and read file
  buffer = (char*)calloc(1, sizeof(char)*fileSize);
  fread(buffer, 1, fileSize, file);

  // set bits
  for (int i = 0; i < fileSize; i++)
  {
    appendUInt8(*vector, (uint8_t)buffer[i]);
    
    //currentByte = (uint8_t)buffer[i];
    //histogram[currentByte] += 1;
    //(*size)++;
  }

  fclose(file);
  free(buffer);
  return;
}

//=======================================================================
//---MAIN----------------------------------------------------------------

int main(int argc, char *argv[])
{
  //-------------------------------------------
  // 1) Declare Variables
  //-------------------------------------------
  char *targetFilePath = NULL; // file to decode
  //char *destination = NULL; // output file name
  
  uint32_t magicNumber = 0xdeadd00d;
  uint64_t sizeOfOriginalFile = 0;

  char *treeInstructions = NULL;
  uint16_t sizeOfTree = 0;
  treeNode *tree = NULL;
  
  bitV *encodedFile = NULL;
  uint32_t currentBitIndex;

  //printf("Step 1 complete\n");

  //-------------------------------------------
  // 2) Parse Arguments
  //-------------------------------------------
  parseArguments(argc, argv, &targetFilePath);
  //printf("Step 2 complete\n");

  //-------------------------------------------
  // 3) Get Information
  //-------------------------------------------
  if (!checkValidFile(targetFilePath, magicNumber))
  {
    printf("This isn't an encoded file. It cannot be decompressed\n");
    return 1;
  }

  // get info from file
  getInfo(targetFilePath, &sizeOfOriginalFile, &sizeOfTree,
	  &treeInstructions);
  // convert file into bitvector to process
  convertFileToBitVector(targetFilePath, &encodedFile);

  //printf("Step 3 complete\n");
  
  //-------------------------------------------
  // 4) rebuild the tree
  //-------------------------------------------
  tree = rebuildTree(treeInstructions, sizeOfTree-1);
  //printf("Step 4 complete\n");

  //-------------------------------------------
  // 5) decode
  //-------------------------------------------
  // find starting index for encoded file's bits
  currentBitIndex = 111 + sizeOfTree*8; 

  for (uint32_t i = 0; i < sizeOfOriginalFile; i++)
  {
    decode(tree, &currentBitIndex, encodedFile);
  }
  
  //printf("Step 5 complete\n");

  //---------------------------------------------------------------------
  // exit program
  //---------------------------------------------------------------------
  free(treeInstructions);
  deleteBitVector(encodedFile);
  deleteTree(tree);
  targetFilePath = NULL;
  
  return 0;
}
