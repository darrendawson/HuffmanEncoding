# include "hashtable.h"

//---getHashedIndex------------------------------------------------------

// hashes a word according to salt from table
uint32_t getHashedIndex(hTable *table, char *key)
{
  uint32_t index = 0;
  char keyToHash[100]; // create buffer room

  if(strlen(key) < 60)
  {
    // add salt to key
    sprintf(keyToHash, "%s%d%d%d%d", key, table->s[0], table->s[1],
	    table->s[2], table->s[3]);

    // hash it
    index = hash((uint8_t*)(keyToHash)) % table->tableSize;
  }
  return index;
}

//---createNewTable------------------------------------------------------

// return pointer to a new table
hTable *createNewTable(uint32_t size, uint32_t *salt, int move)
{
  hTable *table;
  table = (hTable*)calloc(1, sizeof(hTable));

  // allocate memory for words
  table->words = (listNode**)calloc(size, sizeof(listNode*));

  // allocate memory for numSeeks and findLLCalls
  table->numSeeks = (int*)calloc(1, sizeof(int));
  table->findLLCalls = (int*)calloc(1, sizeof(int));

  // set up other parts of table
  table->tableSize = size;
  table->s[0] = salt[0];
  table->s[1] = salt[1];
  table->s[2] = salt[2];
  table->s[3] = salt[3];
  table->moveToFront = move;
  table->numSeeks[0] = 0;

  return table;
}

//---addWordToTable------------------------------------------------------

// adds a word to table
// if there's already something in index, creates a linked list
void addWordToTable(hTable *table, char *old, char *new)
{
  uint32_t index = getHashedIndex(table, old);
  if (table->words[index] == NULL)
  {
    table->words[index] = newNode(old, new); // !!!!!!
  }
  else
  {
    table->words[index] = insertLL(table->words[index], old,new);
  }
}

//---deleteTable---------------------------------------------------------

// goes through each index and deletes tables
void deleteTable(hTable *table)
{
  for (uint32_t i = 0; i < table->tableSize; i++)
  {
    if (table->words[i] != NULL)
    {
      delLL(table->words[i]);
    }
  }
  free(table->numSeeks);
  free(table->findLLCalls);
  free(table->words);
  free(table);
}

//---checkMembership-----------------------------------------------------

// returns 1 if text is in the hash table
int checkTableMembership(hTable *table, char *text)
{
  uint32_t index = getHashedIndex(table, text);
  //printf("INDEX OF %s: %d\n", text, index);
  listNode *found = findLL(&(table->words[index]), text, table->numSeeks,
			   table->findLLCalls, table->moveToFront);
  
  if (found == NULL)
  {
    return 0;
  }
  return 1;
}

//---getNewSpeak---------------------------------------------------------

// returns the new speak variant of word
char *getNewSpeak(hTable *table, char *text)
{
  uint32_t index = getHashedIndex(table, text);
  listNode *found = findLL(&(table->words[index]), text,table->numSeeks,
			   table->findLLCalls, table->moveToFront);

  if (found != NULL)
  {
    return found->newspeak;
  }
  return NULL;
}

//---printList-----------------------------------------------------------

// prints a list
void printTable(hTable *table)
{
  for (uint32_t i = 0; i < table->tableSize; i++)
  {
    if (table->words[i] != NULL)
    {
      //printf("%d: ", i);
      printLL(table->words[i], table->numSeeks);
      printf("\n");
    }
  }
}

//---printOldSpeak------------------------------------------------------

// prints oldspeaks only for list
void printOldSpeak(hTable *table)
{
  for (uint32_t i = 0; i< table->tableSize; i++)
  {
    if (table->words[i] != NULL)
    {
      printf("%s\n", table->words[i]->oldspeak);
    }
  }
}

//---isEmpty------------------------------------------------------------

// returns 1 if table is empty
int isEmpty(hTable *table)
{
  int isEmpty = 1;
  for (uint32_t i = 0; i < table->tableSize && isEmpty == 1; i++)
  {
    if (table->words[i] != NULL)
    {
      isEmpty = 0;
    }
  }
  return isEmpty;
}
