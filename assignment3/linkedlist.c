#include "linkedlist.h"

//---newNode----------------------------------------------------------

// adds a new node to the beginning of list
listNode *newNode(char *old, char *new)
{
  listNode *newNode = (listNode *)calloc(1, sizeof(listNode));
  newNode->oldspeak = (char *)calloc(1, 25*sizeof(char));
  newNode->newspeak = (char *)calloc(1, 25*sizeof(char));

  // assign old and new
  strcpy(newNode->oldspeak, old);
  strcpy(newNode->newspeak, new);
  
  newNode->next = NULL;

  return newNode;
}

//---deleteNode----------------------------------------------------------

// just deletes a node
void delNode(listNode *node)
{
  // free insides of node first
  free(node->oldspeak);
  free(node->newspeak);
  free(node);
}

//---deleteList----------------------------------------------------------

// goes through and deletes every node, starting at beginning
void delLL(listNode *list)
{
  listNode *tempList;
  
  if (list != NULL)
  {
    while (list->next != NULL)
    {
      // create tempList so you can keep track of where the next node is
      tempList = list->next;
      delNode(list);
      list = tempList;
    }
    delNode(list);
  }
}

//---insertLL------------------------------------------------------------

// adds a node to front of list
listNode *insertLL(listNode *list, char *old, char *new)
{
  listNode *newHead = newNode(old, new);

  if (list != NULL)
  {
    newHead->next = list;
  }

  return newHead;
}

//---findLL--------------------------------------------------------------

// returns node that contains key
listNode *findLL(listNode *list, char *key, int *seek, int *findLLCount)
{ 
  listNode *tempList = list;
  
  if (tempList != NULL)
  {
    (*findLLCount)++; // for stats
    (*seek)++; // increment stat
    
    // checks in the case of a one node linked list
    if (strcmp(tempList->oldspeak, key) == 0)
    {
      return tempList;
    }

    // checks in case of multi node linked list
    while (tempList->next != NULL)
    {
      (*seek)++;
      
      // if key = oldspeak, we've found it!
      if (strcmp(tempList->oldspeak, key) == 0)
      {
	return tempList;
      }
      tempList = tempList->next;
    }
  }
  return NULL; // else, it doesn't exist
}

//---printLL-------------------------------------------------------------

// prints the list out
void printLL(listNode *list, int *seeks)
{
  listNode *tempList = list;

  while (tempList->next != NULL)
  {
    (*seeks)++; // for stats
    printf("%s -> %s\n", tempList->oldspeak, tempList->newspeak);
    tempList = tempList->next;
  }
  printf("%s -> %s", tempList->oldspeak, tempList->newspeak);
}
 
