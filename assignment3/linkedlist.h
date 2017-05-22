// LinkedList.h

# ifndef _Linked_List
# define _Linked_List

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

typedef struct listNode listNode;

struct listNode
{
  char *oldspeak;
  char *newspeak;
  listNode *next;
};

// creates a new node and returns pointer to it
listNode *newNode(char *, char *);

// deletes a node, doesn't do any pointer dancing
void delNode(listNode *);

// deletes a list
void delLL(listNode *);

// calls newNode to create a node and stick it in front of list
listNode *insertLL(listNode *, char *, char *);

// searches a Linked List for a word and returns that node
listNode *findLL(listNode **, char *, int *, int *, int);

// prints out a list
void printLL(listNode *, int *);

#endif
