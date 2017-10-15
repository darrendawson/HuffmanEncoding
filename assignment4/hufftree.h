# ifndef _HUFFMAN_H
# define _HUFFMAN_H

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>

# include "bitvector.h"

typedef struct binaryTree treeNode;

struct binaryTree
{
  uint8_t symbol;
  uint64_t frequency;
  bool leaf;
  treeNode *left, *right;
};

typedef struct huffStack
{
  uint32_t size;
  uint32_t top;
  treeNode **entries;
} huffStack;

//---TREE----------------------------------------------------------------

// New node, with symbols, leaf or not, a count associated with it
treeNode *newNode(uint8_t, bool, uint64_t);

// Deletes a node
void deleteNode(treeNode *);

// Delete a tree
void deleteTree(treeNode *);

// join two subtrees
treeNode *join(treeNode *, treeNode *);

// creates instructions to recreate tree (this is for encoder)
void generateTreeInstructions(treeNode *, char *, int *);

// recreate a tree from instructions (this is for decoder)
treeNode *rebuildTree(char *, int);

// steps tree using huff code until it finds corresponding byte
void decode(treeNode *, uint32_t *, bitV *, bitV *);


//---STACK---------------------------------------------------------------

// create a new huff stack of determined size
huffStack *newHuffStack(uint32_t);

// delete a huff stack
void deleteHuffStack(huffStack *);

// push a tree to the top of the stack
void pushHuffStack(huffStack *, treeNode *);

// pop a tree off of stack
treeNode *popHuffStack(huffStack *);

// returns true if stack is empty
bool emptyHuffStack(huffStack *);

// returns true if stack is full
bool fullHuffStack(huffStack *);

//---debugging-----------------------------------------------------------

// code written by Darrell Long for debugging purposes
static inline void spaces(int c)
{
  for (int i = 0; i < c; i += 1)
  {
    putchar(' ');
  }
  return;
}

void printTree(treeNode *t, int depth);


# endif
