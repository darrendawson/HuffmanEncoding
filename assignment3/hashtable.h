// hashtable.h

// bf.h - bloom filter
// this header was provided by Darrell Long
// names of functions have been made more descriptive

# ifndef _Hash_Table
# define _Hash_Table

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include "hash.h"
# include "linkedlist.h"

typedef struct hTable {
  listNode **words; // the table
  uint32_t s[4]; // salt
  uint32_t tableSize;
  int moveToFront; // if 1, move to front is activated
} hTable;

// returns index
uint32_t getHashedIndex(hTable *, char *);

// create new table
hTable *createNewTable(uint32_t, uint32_t *, int);

// adds word to table
void addWordToTable(hTable *, char *, char *);

// delete table
void deleteTable(hTable *);

// returns 1 if word is in table
int checkTableMembership(hTable *, char *);

// returns new speak version of oldspeak
char *getNewSpeak(hTable *, char *);

// prints a table
void printTable(hTable *table);

// prints out only oldspeak
void printOldSpeak(hTable *table);

// returns 1 if table is empty
int isEmpty(hTable *table);

# endif
