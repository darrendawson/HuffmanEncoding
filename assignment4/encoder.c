/*
  Darren Dawson
  dwdawson@ucsc.edu
  
 */

# include <stdio.h>
# include <stdlib.h>
# include <getopt.h>
# include <stdbool.h>
# include <stdint.h>

# include "bitvector.h"
# include "hufftree.h"

//---parseArguments------------------------------------------------------

// Uses command line flags to set up program
void parseArguments(int argc, char *argv[], char **filepath)
{
  char arg; // use to hold argument

  while ((arg = getopt(argc, argv, "i:")) != -1)
  {
    switch (arg)
    {
      case 'i': // suppress letter from censor, print statistics
        *filepath = (char*)optarg;
	break;	 
    }
  }
}

//---checkValidFile------------------------------------------------------

// returns true if file can be opened
// While slightly innefficient, this function is here to increase
// readability of the general program
bool checkValidFile(char *filepath)
{
  FILE *file = fopen(filepath, "r");
  if (file == NULL)
  {
    return false;
  }
  return true;
}

//---setHistogram--------------------------------------------------------

// reads a file and creates a frequency measure for bytes
void setHistogram(int *histogram, char *filepath)
{
  FILE *file;
  long fileSize;
  char *buffer;
  uint8_t currentByte;
  
  // open file
  file = fopen(filepath, "r");

  // get size of file
  fseek(file, 0, SEEK_END);
  fileSize = ftell(file);
  rewind(file);

  // allocate memory and read file
  buffer = (char*)calloc(1, sizeof(char)*fileSize);
  fread(buffer, 1, fileSize, file);

  // set histogram
  for (int i = 0; i < fileSize; i++)
  {
    currentByte = (uint8_t)buffer[i];
    histogram[currentByte] += 1;
  }
  histogram[0] += 1; // make sure there will always be a tree
  histogram[255] += 1; // This was Darrell Long's idea

  fclose(file);
  free(buffer);
  return;
}

//---printHistogram------------------------------------------------------

// prints a histogram
void printHistogram(int *histogram)
{
  int uniqueBytes = 0;
  int totalBytes = 0;
  
  printf("\nHistogram----\n");
  for (int i = 0; i < 256; i++)
  {
    if (histogram[i] != 0)
    {
      uniqueBytes++;
      totalBytes += histogram[i];
      printf("%d: %d\n", i, histogram[i]);
    }
  }
  printf("Unique Bytes: %d\n", uniqueBytes);
  printf("Total Bytes: %d\n", totalBytes);
  printf("----Histogram\n\n");
}

//=======================================================================
//---MAIN----------------------------------------------------------------

int main(int argc, char *argv[])
{
  //-----------------------
  // 1) Declare Variables
  //-----------------------
  char *filepath = NULL;
  int histogram[256] = {0};

  // ENCODED FILE
  // uint32_t magicNum = 0xdeadd00d;
  // size of original file
  // size of huff tree


  //---------------------
  // 2) Parse Arguments
  //---------------------
  parseArguments(argc, argv, &filepath);

  // make sure there is a filepath - if not, exit program
  if (filepath == NULL || !checkValidFile(filepath))
  {
    printf("Please input a correct file name to compress\n");
    return 1;
  }

  //----------------------
  // 3) set up histogram
  //----------------------
  setHistogram(histogram, filepath);


  // Exit program
  return 0;
}
