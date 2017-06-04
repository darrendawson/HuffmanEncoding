# include "priorityqueue.h"

//---newHuffPQueue-------------------------------------------------------

// creates a new queue
huffPQueue *newHuffPQueue(uint32_t newSize)
{
  huffPQueue *q = (huffPQueue*)calloc(1, sizeof(huffPQueue));
  q->entries = (treeNode**)calloc(newSize, sizeof(treeNode*));

  q->size = newSize;
  return q;
}

//---deleteHuffPQueue----------------------------------------------------

// deletes a queue and all its entries
void deleteHuffPQueue(huffPQueue *q)
{
  for (uint32_t i = 0; i < q->size; i++)
  {
    free(q->entries[i]);
  }
  free(q->entries);
  free(q);
  return;
}

//---enqueueHuffPQueue---------------------------------------------------

// adds item to queue in sorted order (by frequency of tree)
// smallest->largest
// returns true if enqueueing works
bool enqueueHuffPQueue(huffPQueue *q, treeNode *tree)
{
  uint32_t index = q->head;
  treeNode *toInsert = tree;
  treeNode *holding; // temp variable that holds next item to insert

  if (fullHuffPQueue(q))
  {
    printf("\nCAN'T ENQUEUE\n");
    return false;
  }

  // 1) find where to insert
  // after this loop, index will be at the first spot where
  //    toInsert needs to be inserted

  if (q->entries[index] != NULL)
  {
    while ((toInsert->frequency > q->entries[index]->frequency)
	   && index != q->tail)
    {
      index = (index + 1) % q->size;
      if (q->entries[index] == NULL)
      {
	break; 
      }
    }
  }
  

  // 2) insertion loop
  for (; index != (q->tail + 1) % q->size; index = (index + 1) % q->size)
  {
    holding = q->entries[index];
    q->entries[index] = toInsert;
    toInsert = holding;
  }

  // when enqueueing, tail increments
  q-> tail = (q->tail + 1) % q->size;

  return true;
}

//---dequeueHuffPQueue---------------------------------------------------

// pops value off head, increments head
treeNode *dequeueHuffPQueue(huffPQueue *q)
{
  treeNode *result = NULL;

  // only run if there's something to dequeue
  if (!emptyHuffPQueue(q))
  {
    result = q->entries[q->head];
    q->entries[q->head] = NULL;
    q->head = (q->head + 1) % q->size;
  }

  return result;
}

//---emptyHuffPQueue-----------------------------------------------------

// returns true if empty
// [ |h, t| | ] is empty
bool emptyHuffPQueue(huffPQueue *q)
{
  return q->head == q->tail;
}

//---fullHuffPQueue------------------------------------------------------

// returns true if tail is one slot behind the tail (if full)
// [t|h| ....] is full
bool fullHuffPQueue(huffPQueue *q)
{
  return (q->tail + 1) % q-> size == q->head;
}

//---printHuffPQueue-----------------------------------------------------

// prints the queue
void printHuffPQueue(huffPQueue *q)
{
  printf("\nHUFFPQUEUE-------\n");
  printf("Head: %d\n", q->head);
  printf("Tail: %d\n", q->tail);

  for (uint32_t i = q->head; i != q->tail; i = (i+1) % q->size)
  {
    printf("Root: %d, Frequency: %lu\n", q->entries[i]->symbol,
	   q->entries[i]->frequency);
  }
  printf("------HUFFPQUEUE\n");
  return;
}
