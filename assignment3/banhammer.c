/*
  Darren Dawson, dwdawson@ucsc.edu
  CMPS 12b, Assignment 3
 banhammer scrubs text
 */

# include <stdio.h>
# include <unistd.h>
# include <getopt.h>
# include <stdint.h>
# include <stdlib.h>

//---parseArguments------------------------------------------------------

// Uses command line flags to set up program
void parseArguments(int argc, char*argv[], int *printLetter,
		    int *hashSize, int *bloomSize, int *moveToFront)
{
  char arg; // use to hold argument

  while ((arg = getopt(argc, argv, "sh:f:mb")) != -1)
  {
    switch (arg)
    {
      case 's': // suppress letter from censor, print statistics
	*printLetter = 0;
	break;
	
      case 'h': // size specifies size of hash table
	*hashSize = (int) atoi(optarg);
	break;
	
      case 'f': // size specifies size of bloom filter
	*bloomSize = (int) atoi(optarg);
	break;
	
      case 'm': // use /move-to-front/ rule
	*moveToFront = 1;
	break;
	
      case 'b': // don't use /move-to-front/ rule
	*moveToFront = 0;
	break;
    }
  }
  
}

//---MAIN----------------------------------------------------------------

int main(int argc, char *argv[]) {

  // DECLARE VARIABLES-------
  int printLetter = 1;
  int hashSize = 10000;
  int bloomSize = 10485776; // 2^20 default size
  int moveToFront = 0;
  //--------------------------

  parseArguments(argc, argv, &printLetter, &hashSize,
		 &bloomSize, &moveToFront);

  printf("Print Letter: %d\nHash Size: %d\n", printLetter, hashSize);
  printf("Bloom Size: %d\nMoveToFront: %d\n", bloomSize, moveToFront);


  //---exit program---
  return 0;
}
