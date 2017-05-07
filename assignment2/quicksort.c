/*
  quicksort.c does a quicksort
  Darren Dawson, dwdawson@ucsc.edu
  CMPS 12b, assignment 1
 */

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# include "quicksort.h"

//---partition-----------------------------------------------------------

// reorders an array into [nums smaller, pivot, nums larger]
// returns index of pivot
int partition(uint32_t *array, int start, int end, int *moves, int *comparisons)
{
  uint32_t pivot = array[start];
  int sortedOnLeft = 0;
  int leftIndex = start + 1;
  int rightIndex = end-1;
  int swap = 0;
  
  // loop through until left == right
  while (leftIndex <= rightIndex)
  {

    // if array[left] > pivot
    //  --> swap with first candidate from right
    if (array[leftIndex] >= pivot)
    {
      
      swap = 1;
      while (swap == 1)
      {
	// find first num on right that satisfies if statement
	if (array[rightIndex] < pivot)
	{
	  // can swap them
	  int temp = array[rightIndex];
	  array[rightIndex] = array[leftIndex];
	  array[leftIndex] = temp;

	  swap = 0;
	  rightIndex--;
	  *moves += 3;
	}
	else
	{
	  // cant replace -> leave it there
	  rightIndex--;
	}
	(*comparisons)++;
      }
    }

    else
    {
      // don't swap
      array[sortedOnLeft+start] = array[leftIndex];
      leftIndex++;
      sortedOnLeft++;
      (*moves)++;
    }
    (*comparisons)++;
  }
  array[leftIndex-1] = pivot;
  (*moves)++;
  return leftIndex;
}

//---quickSort-----------------------------------------------------------

void quickSort(uint32_t *array, int start, int end, int *moves, int *comparisons)
{
  int pivot;
  
  if (end - start < 2)
  {
    return; // nothing to sort
  }

  pivot = partition(array, start, end, moves, comparisons);
  
  quickSort(array, start, pivot-1, moves, comparisons);
  quickSort(array, pivot+1, end, moves, comparisons);

  return;
}

