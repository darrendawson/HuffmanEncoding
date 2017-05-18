/*
  Darren Dawson, dwdawson@ucsc.edu
  CMPS 12b, Assignment 3
 banhammer scrubs text
 */

# define _GNU_SOURCE // so file reading works on linux
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <getopt.h>
# include <stdint.h>

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

// reads a file to set up filter
// from man page
void setUpFilters(bloomF *filter1, bloomF *filter2, char *filePath)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  
  fp = fopen(filePath, "r");
  if (fp != NULL)
  {
    while ((read = getline(&line, &len, fp)) != -1) {
      setBit(filter1, line);
      setBit(filter2, line);
    }
  }
  
  free(line);
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
  // parameters
  int printLetter = 1;
  int hashSize = 10000;
  int bloomSize = 10485776; // 2^20 default size
  int moveToFront = 0;

  // set up salts for filter 1, filter 2, and hash table
  uint32_t salt1[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a};
  uint32_t salt2[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a};
  //uint32_t saltH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe};

  bloomF *filter1;
  bloomF *filter2;
  //--------------------------

  // 1) get instructions from command line
  parseArguments(argc, argv, &printLetter, &hashSize,
		 &bloomSize, &moveToFront);

  // 2) set up bloom filter
  filter1 = newFilter(hashSize, salt1);
  filter2 = newFilter(hashSize, salt2);
  setUpFilters(filter1, filter2, "badspeak.txt");

  // 3) set up hash table 
  
  // 4) get user string

  // 5) go through string word by word, checking filter/hash
  //    save flagged words to two different 


  //--------------
  
  printFilter(filter1);
  printf("\n\n");
  printFilter(filter2);

  //-----------------


  /*
  //---print results---
  if (printLetter == 1)
  {
    printThoughtCrimes();
  }
  else
  {
    printStatistics();
  }
  */
  //---exit program---
  deleteFilter(filter1);
  deleteFilter(filter2);
  printf("\n");
  return 0;
}
