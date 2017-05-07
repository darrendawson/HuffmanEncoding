/*
  this is a bubble sort algorithm
  Darren Dawson, dwdawson@ucsc.edu
  cmps 12b, Assignment 2
 */

# include "bubblesort.h"
# include <stdint.h>
# include <stdio.h>

//---bubbleSort-------------------------------------------------------------

// bubble sort -> large numbers bubble up to top
void bubbleSort(uint32_t a[], uint32_t length)
{
  int moves = 0;
  int comparisons = 0;
  uint32_t endOfUnsorted = length - 1;
  
  // loop through array
  for (uint32_t i = 0; i < length; i++)
  {
    // largest number gets "bubbled" up to end of array
    for (uint32_t j = 0; j < endOfUnsorted; j++)
    {
      if (a[j] > a[j+1])
      {
	// swap
	uint32_t temp = a[j+1];
	a[j+1] = a[j];
	a[j] = temp;
	moves += 3;
      }
      comparisons++;
    }
    endOfUnsorted--;
  }
  
  printf("%d moves\n%d compares\n", moves, comparisons);
  return;
}
