/*
  mergesort.c is a mergesort algorithm that fills out mergesort.h
  Darren Dawson, dwdawson@ucsc.edu
  CMPS 12b, assignment 2
 */

# include <stdlib.h>
# include <stdint.h>
# include "mergesort.h"

//---merge---------------------------------------------------------------

// merges two sorted lists together
void merge(uint32_t *fullArray, uint32_t *leftArray, uint32_t *rightArray,
	   int sizeLeft, int sizeRight, int *moves, int *comparisons)
{
  int mergeIndex = 0; // increments with every push
  int leftIndex = 0; // increments when number from left is pushed
  int rightIndex = 0; // increments when number from right is pushed

  
  // compare num from left Array and num from right Array
  // -> add number that is smaller
  while (leftIndex < sizeLeft || rightIndex < sizeRight)
  {
    // check to see if we are still comparing two numbers
    if (leftIndex == sizeLeft)
    {
      // no numbers in leftArray left -> add next right number
      fullArray[mergeIndex] = rightArray[rightIndex];
      rightIndex++;
    }
    else if (rightIndex == sizeRight)
    {
      // no numbers in rightArray left -> add next left number
      fullArray[mergeIndex] = leftArray[leftIndex];
      leftIndex++;
    }

    //compare the numbers in left and right
    else if (leftArray[leftIndex] < rightArray[rightIndex])
    {
      // left is smaller -> add left
      fullArray[mergeIndex] = leftArray[leftIndex];
      leftIndex++;
    }
    else
    {
      // right is smaller (or equal) -> add right
      fullArray[mergeIndex] = rightArray[rightIndex];
      rightIndex++;
    }

    // increment mergeIndex
    mergeIndex++;
    *moves += 1; // we did 1 move
    *comparisons += 1; // we did 1 comparison
  }
}


//--assignValues---------------------------------------------------------

// copies values from fullArray[start..end] to halfArray
void assignValues(uint32_t *halfArray, uint32_t *fullArray,
		  int start, int end, int *moves)
{
  int size = end - start;
  int fullArrayIndex = start;
  for (int i = 0; i < size; i++, fullArrayIndex++)
  {
    halfArray[i] = fullArray[fullArrayIndex];
    *moves += 1; // we do 1 move per translation of values
  }
}

//---mergeSort-----------------------------------------------------------

// recursively sorts a list by splitting it into halves
// sorts halves, bubbles up with sorted list
// compares sorted lists to reduce innefficiency
void mergeSort(uint32_t *array, int size, int *moves, int *comparisons)
{
  int middle = size/2;
  
  // declare temporary arrays
  uint32_t *leftArray;
  uint32_t *rightArray;

  if (size < 2)
  {
    return; // nothing to sort
  }

  // allocate temp arrays in memory
  leftArray = (uint32_t*)calloc(middle, sizeof(uint32_t));
  rightArray = (uint32_t*)calloc(size-middle, sizeof(uint32_t));

  // assign values to the halves
  assignValues(leftArray, array, 0, middle, moves);
  assignValues(rightArray, array, middle, size, moves);

  // perform recursive function -> split left and right again
  mergeSort(leftArray, middle, moves, comparisons);
  mergeSort(rightArray, size-middle, moves, comparisons);

  merge(array, leftArray, rightArray, middle, size-middle,
	moves, comparisons);
  
  // Free memory
  free(leftArray);
  free(rightArray);
}
