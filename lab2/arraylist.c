/*
  Darren Dawson, dwdawson@ucsc.edu
  CMPS 12M: lab 2
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void printArray(uint32_t *array, int numElements)
{
  for(int i=0; i<numElements; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");
}
//------------------------------
int main()
{
  int playing = 1;          // 0 if user wants to quit
  char action;              // user input to determine next action
  uint32_t *array;          // int arraylist
  int size = 1;             // number of ints allocated in memory for list
  int numElements = 0;      // number of ints currently in list
  int nextInt;              // user number to be added to end of list

  array = (uint32_t*)calloc(1, sizeof(uint32_t));
  
  while(playing == 1)
  {
    int newSize;
    
    // GET ACTION
    printf("Action? (Insert, Print, or Quit): ");
    scanf(" %c", &action);

    // PERFORM ACTION
    if (action == 'Q' || action == 'q') //-------------------------------
    {
      // QUIT PROGRAM
      playing = 0;
      printf("\n"); // new line before quiting
    }
    else if (action == 'I' || action == 'i') //--------------------------
    {
      // INSERT
      
      // get number from user
      printf("Enter an Integer: ");
      scanf("%d", &nextInt);

      // reallocate memory if we would be over running the array
      if (numElements == size)
      {
	size = size * 2; // double size of array
	newSize = sizeof(uint32_t)*size;
	array = realloc(array, newSize);
      }
      
      array[numElements] = nextInt; // add to end of array
      numElements++; // increment the number of things in array
    }
    else if (action == 'P' || action == 'p') //--------------------------
    {
      // PRINT
      printf("Length = %d: ", numElements);
      printArray(array, numElements);
    }
  }

  // EXIT PROGRAM
  free(array);
  return 0;
}
