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


# include "aes.h"
# include "hash.h"
# include "bf.h"


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

//---Read Files----------------------------------------------------------

void readFile()
{
  /*
  FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

   fp = fopen("/etc/motd", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

   while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

   free(line);
   exit(EXIT_SUCCESS); */
}

//---Print Stuff---------------------------------------------------------

// prints out thoughtcrime message and errors
// thought Crimes contains
// thoughtCrimes, numCrimes
void printThoughtCrimes() {
  printf("Dear Comrade,\n\nYou have chosen to use degenerate words ");
  printf("that may cause hurt\nfeelings or cause your comrades to ");
  printf("think unpleasant thoughts.\nThis is doubleplus bad. To ");
  printf("correct your wrongthink and\nsave community consensus we ");
  printf("will be sending you to joycamp\nadministered by Miniluv.\n\n");
  printf("Your errors:\n\n");

  /*
  for (int i = 0; i< numCrimes; i++) {
    // print out thoughtCrimes
    } */
}


// prints out words that were flagged and changed to newspeak
void printGoodSpeak() {
  printf("Dear Comrade,\n\n");
}


// prints out statistics about text
void printStatistics() {
  printf("Statistics\n");
}

//---MAIN----------------------------------------------------------------

int main(int argc, char *argv[]) {

  
  // DECLARE VARIABLES-------
  int printLetter = 1;
  int hashSize = 10000;
  int bloomSize = 10485776; // 2^20 default size
  int moveToFront = 0;
  //--------------------------

  // 1) get instructions from command line
  parseArguments(argc, argv, &printLetter, &hashSize,
		 &bloomSize, &moveToFront);

  // 2) set up bloom filter/ hash

  // 3) get user string

  // 4) go through string word by word, checking filter/hash
  //    save flagged words to two different 

  /*
  // !!! TEST HASH
  uint8_t *testChars = (uint8_t*)"test";
  uint32_t test = hash(testChars);
  printf("hash: %d\n", test);
  // !!!
  */

  //--------------

  uint32_t testFunction = 1;
  bloomF *filter = newFilter(hashSize, &testFunction);

  setBit(filter, "hello");
  setBit(filter, "helo");
  setBit(filter, "hel");

  printf("hello: %d\n",checkMembership(filter, "hello"));
  clearBit(filter, "hello");
  printf("hello: %d\n",checkMembership(filter, "hello"));
  printFilter(filter);
  printf("\n");

  readFile();

  
//-----------------

  
  //---print results---
  if (printLetter == 1)
  {
    printThoughtCrimes();
  }
  else
  {
    printStatistics();
  }

  //---exit program---
  deleteFilter(filter);

  
  return 0;
}
