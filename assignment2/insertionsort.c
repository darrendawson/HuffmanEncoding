# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

# include "insertionsort.h"

void insertionSort(uint32_t *array, int size)
{
  int indexSmallest = 0;
  uint32_t temp;
  int moves = 0;
  int comparisons = 0;
  
  if (size < 2)
  {
    printf("0 moves\n0 comparisons\n");
    return;
  }

  for (int i = 0; i < size; i++)
  {
    indexSmallest = i;

    // find smallest
    for (int j = i+1; j < size; j++)
    {
      if (array[j] < array[indexSmallest])
      {
	indexSmallest = j;
      }
      comparisons++;
    }
    
    // swap smallest to front
    temp = array[i];
    array[i] = array[indexSmallest];
    array[indexSmallest] = temp;
    moves += 3;
  }
  printf("%d moves\n%d comparisons\n", moves, comparisons);
  return;
}
