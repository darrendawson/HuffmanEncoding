/*
  Darren Dawson, dwdawson@ucsc.edu
  priority queue of huff trees
 */

# ifndef _Priority_Queue
# define _Priority_Queue

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "hufftree.h"

typedef struct huffPQueue
{
  uint32_t size;
  uint32_t head, tail;
  treeNode **entries;
} huffPQueue;

// creates a new queue
huffPQueue *newHuffPQueue(uint32_t);

// deletes a queue
void deleteHuffPQueue(huffPQueue *);

// adds an item to queue in sorted order
bool enqueueHuffPQueue(huffPQueue *, treeNode *);

// returns the smallest number in queue
treeNode *dequeueHuffPQueue(huffPQueue *);

// returns true if queue is empty
bool emptyHuffPQueue(huffPQueue *);

// returns true if queue is full
bool fullHuffPQueue(huffPQueue *);

// prints the root of each item in queue
void printHuffPQueue(huffPQueue *);

#endif
