/*
  Darren Dawson, dwdawson@ucsc.edu
  Lab 1, cmps12m
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>

//-----------------------------------------------------------------------
// FUNCTIONS

//---printArgs----------------------------------------

// prints out command line arguments
void printArgs(int argc, char **argv)
{
  for(int i=1; i < argc; ++i)
  {
    printf("%s\n", argv[i]);
  }
}

//---printValueToStandardOut--------------------------

// prints to standard out 
void printValueToStandardOut(uint8_t value)
{
  int fd = 1;
  ssize_t bytesWritten;
  bytesWritten = write(fd, &value, 1);

  if(bytesWritten != 1)
  {
    perror("cat");
    exit(errno);
  }
}

int openFileReadOnly(char *filename)
{
  int fd;
  fd = open(filename, O_RDONLY);
  if(fd == -1)
  {
    perror("cat");
    exit(errno);
  }
  return fd;
}

void closeFile(int fd)
{
  int closed;
  closed = close(fd);
  if(closed != 0)
  {
    perror("cat");
    exit(errno);
  }
}

//-----------------------------------------------------------------------
// RUN/MAIN
//-----------------------------------------------------------------------

int main(int argc, char **argv)
{
  // CAT FILES LOOP
  for(int i=1;i < argc; i++)
  {
    //open file
    int fd = openFileReadOnly(argv[i]);     
    
    //read file
    uint8_t value;
    int charsRead = 0;
    while((charsRead = read(fd, &value, 1))>0)
    {
      printValueToStandardOut(value);
    }

    //close file
    closeFile(fd);
    
  } // END CAT FILES LOOP
  return 0; // end program
}
