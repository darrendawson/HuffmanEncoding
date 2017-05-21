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
# include <float.h>

# include "aes.h"
# include "hash.h"
# include "bf.h"
# include "hashtable.h"

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

//---SetUpFilters--------------------------------------------------------

// reads badspeak.txt to set up filter
// from man page
void setUpBadSpeakFilters(bloomF *filter1, bloomF *filter2, int *dict)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  
  fp = fopen("badspeak.txt", "r");
  if (fp != NULL)
  {
    while ((read = getline(&line, &len, fp)) != -1) {
      setBit(filter1, line);
      setBit(filter2, line);
      (*dict)++; // for stats
    }
  }

  fclose(fp);  
  free(line);
}


// reads newspeak.txt and adds first word in each line to filters
void setUpNewSpeakFilters(bloomF *filter1, bloomF *filter2, int *trans)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char oldspeak[30];
  
  fp = fopen("newspeak.txt", "r");
  if (fp != NULL)
  {
    while ((read = getline(&line, &len, fp)) != -1) {
      sscanf(line, "%s", oldspeak);
      setBit(filter1, oldspeak);
      setBit(filter2, oldspeak);
      (*trans)++;
    }
  }

  fclose(fp);  
  free(line);
}

//---setUpTable----------------------------------------------------------

// read from a file, newspeak, split into two words and add to hash table
void setUpTable(hTable *table)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  char oldspeak[30];
  char newspeak[30];
  
  fp = fopen("newspeak.txt", "r");
  if (fp != NULL)
  {
    while ((read = getline(&line, &len, fp)) != -1) {
      sscanf(line, "%s%s", oldspeak, newspeak);
      //printf("[%s, %s]\n", oldspeak, newspeak);
      addWordToTable(table, oldspeak, newspeak); 
    }
  }

  fclose(fp);  
  free(line);
}

//---checkInput----------------------------------------------------------

// opens a text file from standard in
// checks each word against bloom filters and hashtable to find problems
// compiles lists of words that are (banned) or (should be changed)
void checkInput(bloomF *filter1, bloomF *filter2, hTable *table,
		hTable *bannedWords, hTable *wordsToChange, int *text)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  // go through file, line by line
  while ((read = getline(&line, &len, stdin)) != -1) {

    //break up line into words based off spaces
    // get first word of line
    char *word = strtok(line, " ");

    // loop through words
    while (word != NULL)
    {
      (*text) += 1; // for stats
      
      // only check a word if it's in the bloom filters
      if (checkMembership(filter1, word) == 1 ||
	  checkMembership(filter2, word) == 1)
      {
	
	// if checkTableMembership() returns something, it has a
	// newspeak variant and we want to add it
	if (checkTableMembership(table, word) == 1)
	{
	  // only add word to wordsToChange if it isn't already there
	  if (checkTableMembership(wordsToChange, word) == 0)
	  {
	    // add to wordsToChange
	    char *newspeak = getNewSpeak(table, word);
	    addWordToTable(wordsToChange, word, newspeak);
	  }
	}
	else
	{
	  // if not in table, then the word is a complete violation
	  //bannedWords[i] = word;
	  //printf("%s is BANNED\n", word);
	  if (checkTableMembership(bannedWords, word) == 0)
	  {
	    addWordToTable(bannedWords, word, "");
	  }
	}

      }
     
      word = strtok(NULL, " "); // move on to next word
    }
  }

  free(line);
}

//---Print Stuff---------------------------------------------------------

// prints out thoughtcrime message and errors
void printThoughtCrimes() {
  printf("Dear Comrade,\n\nYou have chosen to use degenerate words ");
  printf("that may cause hurt\nfeelings or cause your comrades to ");
  printf("think unpleasant thoughts.\nThis is doubleplus bad. To ");
  printf("correct your wrongthink and\nsave community consensus we ");
  printf("will be sending you to joycamp\nadministered by Miniluv.\n\n");
  printf("Your errors:\n\n");
}


// prints out words that were flagged and changed to newspeak
void printGoodSpeak() {
  printf("Dear Comrade,\n\n");
  printf("Submitting your text helps to preserve feelings and prevent\n ");
  printf("badthink. Some of the words that you used are not goodspeek.\n ");
  printf("The list shows how to turn oldspeak words into newspeak.\n\n");
}



// prints words that are banned or need to be changed
// prints a letter to user
void printResults(hTable *bannedWords, hTable *wordsToChange)
{
  // check if they had any banned words
  if (isEmpty(bannedWords) != 1)
  {
    // there are banned words -> joycamp!
    printThoughtCrimes();
    printOldSpeak(bannedWords);
    printf("\n\nThink on these words during your vacation!\n\n");
  }

  if (isEmpty(wordsToChange) != 1)
  {
    if (isEmpty(bannedWords) == 1)
    {
      // we only want to display the gentle reminder letter
      // if the user is not going to joy camp
      printGoodSpeak();
    }
    printTable(wordsToChange);
  }
}

// prints out statistics about text
void printStatistics(int seeks, float average, int dictionary,
		     int translations, int text,
		     float filter1, float filter2) {
  printf("Statistics\n");
  printf("Seeks: %d\tAverage: %f\n", seeks, average);
  printf("Dictionary: %d\tTranslations: %d\n", dictionary, translations);
  printf("Text: %d\n", text);
  printf("Densities: %f,   %f", filter1, filter2);
}

//=====================================================================
//---MAIN--------------------------------------------------------------||
//=====================================================================
int main(int argc, char *argv[]) {

  //----------------------
  // 1) DECLARE VARIABLES |
  //----------------------
  
  // parameters
  int hashSize = 10000;
  int bloomSize = 10485776; // 2^20 default size
  int moveToFront = 0;
  int printLetter = 1; // if 1, print normal output

  // statistics  
  int seeks = 0; // number of nodes inspected in LL  
  float average = 0; // (times findLL called) / seeks 
  int dictionary = 0; // number of entries in badspeak.txt
  int translations = 0; // number of lines in newspeak.txt
  int text = 0; // number of words read from stdin
  
  // ratio of set bits to unset bits in filter
  float filter1Density = 0; 
  float filter2Density = 0;
  
  
  // set up salts for filter 1, filter 2, and hash table
  uint32_t salt1[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a};
  uint32_t salt2[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a};
  uint32_t saltH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe};

  // bloom filters and hash tables
  bloomF *filter1;
  bloomF *filter2;
  hTable *table;

  // list of violations
  hTable *wordsToChange; // words that should be newspeak
  hTable *bannedWords; // words that are just straight up banned
  wordsToChange = createNewTable(hashSize, saltH, moveToFront);
  bannedWords = createNewTable(hashSize, saltH, moveToFront);
  
  //---------------------------------------
  // 2) get instructions from command line |
  //---------------------------------------
  parseArguments(argc, argv, &printLetter, &hashSize,
		 &bloomSize, &moveToFront);

  //-------------------------
  // 3) set up bloom filters |
  //-------------------------
  filter1 = newFilter(bloomSize, salt1);
  filter2 = newFilter(bloomSize, salt2);
  
  // hash the filters
  setUpBadSpeakFilters(filter1, filter2, &dictionary);
  setUpNewSpeakFilters(filter1, filter2, &translations);
  
  //----------------------
  // 4) set up hash table |
  //----------------------
  table = createNewTable(hashSize, saltH, moveToFront);
  setUpTable(table); // hash it with oldspeak newspeak

  
  //----------------------------
  // 5) open up input, check it |
  //----------------------------
  checkInput(filter1, filter2, table, bannedWords, wordsToChange, &text);
  
  //------------------
  // 6) print results |
  //------------------

  if (printLetter == 1)
  {
    printResults(bannedWords, wordsToChange);
  }
  else
  {
    // calculate stats
    seeks = table->numSeeks[0] + wordsToChange->numSeeks[0] +
      bannedWords->numSeeks[0];
    average = table->findLLCalls[0] + wordsToChange->findLLCalls[0] +
      bannedWords->findLLCalls[0];
    average = (float)(average)/(float)(seeks);
    
    filter1Density = findPercentFull(filter1);
    filter2Density = findPercentFull(filter2);

    // print stats
    printStatistics(seeks, average, dictionary, translations, text,
		    filter1Density, filter2Density);
  }


  //-------------------------------------
  // Exit Program
  //-------------------------------------
  deleteFilter(filter1);
  deleteFilter(filter2);
  deleteTable(table);
  deleteTable(wordsToChange);
  deleteTable(bannedWords);
  printf("\n");
  return 0;
}
