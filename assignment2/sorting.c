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


//---MAIN----------------------------------------------------------------
int main(int argc, char *argv[])
{
  uint32_t sizeOfArray = 100;
  uint32_t randomSeed = 8062022;
  uint32_t numsToPrint = 100;

  uint32_t *sizeOfArrayP = &sizeOfArray;
  uint32_t *randomSeedP = &randomSeed;
  uint32_t *numsToPrintP = &numsToPrint;

  int sorts[5] = {0, 0, 0, 0, 0};

  // Use arguments to set up array
  parseArguments(argc, argv, sorts, sizeOfArrayP,
		 randomSeedP, numsToPrintP);

  
  //Create array of random numbers

  printf("Size of Array: %d\nRandom Seed: %d\n", sizeOfArray, randomSeed);
  printf("nums to print: %d", numsToPrint);

  return 0;
}
