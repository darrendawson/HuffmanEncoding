/*
  Darren Dawson, dwdawson@ucsc.edu
  CMPS 12b: Assignment 2 - sorts

  Statistics to print out:
   - size of the array
   - number of moves required (each time you transfer an element)
   - number of comparisons required between elements
 */

# include <stdio.h>
# include <unistd.h>
# include <getopt.h>
# include <stdint.h>
# include <stdlib.h>

# include "minsort.h"
# include "bubblesort.h"
# include "mergesort.h"
# include "quicksort.h"
# include "insertionsort.h"

//---parseArguments------------------------------------------------------

//  Uses command line arguments to set up program
void parseArguments(int argc, char *argv[], int *sorts,
		    uint32_t *sizeOfArray,
		    uint32_t *randomSeed, uint32_t *numsToPrint)
{
  char arg; // use for arguments
  while ((arg = getopt(argc, argv, "AmbiqMp:r:n:")) != -1)
  {
    switch (arg)
    {
      case 'A': // all sorting algorithms
	sorts[0] = 1;
	sorts[1] = 1;
	sorts[2] = 1;
	sorts[3] = 1;
	sorts[4] = 1;
	break;
      case 'm': // minSort
	sorts[0] = 1;
	break;
      case 'b': // bubble sort
	sorts[1] = 1;
	break;
      case 'i': // insertionSort
	sorts[2] = 1;
	break;
      case 'q': // quickSort
	sorts[3] = 1;
	break;
      case 'M': // mergeSort
	sorts[4] = 1;
	break;
      case 'p': // print first n elements of array
	*numsToPrint = (uint32_t) atoi(optarg);
	break;
      case 'r': // set random seed to n
	*randomSeed = (uint32_t) atoi(optarg);
	break;
      case 'n': // set array size to n
	*sizeOfArray = (uint32_t) atoi(optarg);
	break;
    }
  }  
}

//---createNumArray------------------------------------------------------

// creates array of random numbers of certain size
void createNumArray(uint32_t **numArray, uint32_t sizeOfArray)
{
  int bitMask = 0x00ffffff; // limit numbers to 24 bits

  // allocate in memory
  *numArray = (uint32_t*)calloc(sizeOfArray, sizeof(uint32_t));

  
  // set ints in array to random numbers
  for (uint32_t i=0; i < sizeOfArray; i++)
  {
    (*numArray)[i] = (uint32_t)(rand() & bitMask);
  }
}

//---printArray----------------------------------------------------------

// prints the first n numbers in an array
void printArray(uint32_t **numArray, uint32_t numsToPrint)
{
  int newLine = 0;
  //print 7 numbers in each row
  for(uint32_t i=0; i < numsToPrint; i++)
  {
    printf("%10d", (*numArray)[i]);
    if (newLine == 6)
    {
      printf("\n");
      newLine = 0;
    }
    else
    {
      newLine++;
    }
  }
  printf("\n\n");
}

//---MAIN----------------------------------------------------------------

int main(int argc, char *argv[])
{
  uint32_t sizeOfArray = 100;
  uint32_t randomSeed = 8062022;
  uint32_t numsToPrint = 100;
  uint32_t *sizeOfArrayP = &sizeOfArray;
  uint32_t *randomSeedP = &randomSeed;
  uint32_t *numsToPrintP = &numsToPrint;

  int sorts[5] = {0, 0, 0, 0, 0}; // determines what sorts to run
  uint32_t *numArray; // array of random numbers to be sorted

  // Use command line arguments to set up array
  parseArguments(argc, argv, sorts, sizeOfArrayP,
		 randomSeedP, numsToPrintP);

  // make sure we can only print up to the size of the array
  if (sizeOfArray < numsToPrint)
  {
    numsToPrint = sizeOfArray; 
  }

  // PRINT THE SORTED FUNCTIONS
  if (sorts[0] == 1)
  {
    // min sort
    printf("Min Sort\n");
    printf("%d elements\n", numsToPrint);
    srand(randomSeed);
    createNumArray(&numArray, sizeOfArray);
    minSort(numArray, sizeOfArray);
    
    printArray(&numArray, numsToPrint);
    free(numArray);
  }
  if (sorts[1] == 1)
  {
    // bubble sort
    printf("Bubble Sort\n");
    printf("%d elements\n", numsToPrint);
    srand(randomSeed);
    createNumArray(&numArray, sizeOfArray);
    bubbleSort(numArray, sizeOfArray);
    
    printArray(&numArray, numsToPrint);
    free(numArray);
  }
  if (sorts[2] == 1)
  {
    // insertion sort
    printf("Insertion Sort\n");
    printf("%d elements\n", numsToPrint);
    srand(randomSeed);
    createNumArray(&numArray, sizeOfArray);
    insertionSort(numArray, sizeOfArray);
    
    printArray(&numArray, numsToPrint);
    free(numArray);
  }
  if (sorts[3] == 1)
  {
    // quick sort
    int moves = 0;
    int comparisons = 0;
    
    printf("Quick Sort\n");
    printf("%d elements\n", numsToPrint);
    srand(randomSeed);
    createNumArray(&numArray, sizeOfArray);
    quickSort(numArray, 0, sizeOfArray, &moves, &comparisons);
    printf("%d moves\n%d comparisons\n", moves, comparisons);

    printArray(&numArray, numsToPrint);
    free(numArray);
  }
  if(sorts[4] == 1)
  {
    // merge sort
    int moves = 0;
    int comparisons = 0;
    
    printf("Merge Sort\n");
    printf("%d elements\n", numsToPrint);
    srand(randomSeed);
    createNumArray(&numArray, sizeOfArray);
    mergeSort(numArray, sizeOfArray, &moves, &comparisons);
    printf("%d moves\n%d comparisons\n", moves, comparisons);

    printArray(&numArray, numsToPrint);
    free(numArray);
  }
 
  return 0;
}
