/*
  Darren Dawson, dwdawson@ucsc.edu
  CMPS 12b: Assignment 2 - sorts

  Statistics:
   - size of the array
   - number of moves required (each time you transfer an element)
   - number of comparisons required between elements
 */

# include <stdio.h>
# include <unistd.h>
# include <getopt.h>
# include <stdint.h>
# include <stdlib.h>

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
  printf("\n");
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
  
  //Create array of random numbers
  srand(randomSeed);
  createNumArray(&numArray, sizeOfArray);

  printArray(&numArray, 30);
  
  //printf("Size of Array: %d\nRandom Seed: %d\n", sizeOfArray, randomSeed);
  //printf("nums to print: %d", numsToPrint);

  free(numArray);
  return 0;
}
