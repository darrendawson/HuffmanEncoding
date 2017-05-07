/*
  minsort.c is a minsort algorithm
  the code here was provided by Darrell Long, the instructor
   - I did not write this code
   Darren Dawson, dwdawson@ucsc.edu
   cmps 12b, Assignment 2
 */

# include "minsort.h"
# include <stdint.h>
# include <stdio.h>

//---minIndex------------------------------------------------------------

// returns
uint32_t minIndex(uint32_t a[], uint32_t first,
		  uint32_t last, int *comparisons)
{
  uint32_t smallest = first; // Assume the first is the least
  for (uint32_t i = first; i < last; i+= 1)
  {
    smallest = a[i] < a[smallest] ? i : smallest;
    (*comparisons)++;
    /*
      if (a[i] < a[smallest])
        smallest = i
      else
        smallest = smallest
     */
  }
  return smallest;
}

//---minSort-------------------------------------------------------------

// sorts an array using minsort algorithm 
void minSort(uint32_t a[], uint32_t length)
{
  int moves = 0;
  int comparisons = 0;

  for (uint32_t i = 0; i < length - 1; i += 1)
  {
    uint32_t smallest = minIndex(a, i, length, &comparisons);
    if(smallest != i) // don't swap with itself
    {
      //swap
      uint32_t temp = a[i];
      a[i] = a[smallest];
      a[smallest] = temp;
      moves += 3;
    }
  }
  printf("%d moves\n%d compares\n", moves, comparisons);
  return;
}
