/*
  Darren Dawson, dwdawson@ucsc.edu
  lab 4: multithreading
 */

# include <stdio.h>
# include <stdlib.h>
# include <getopt.h>
# include <pthread.h>

// global variables
int globalCounter;
pthread_mutex_t counterMutex;

//---parseArguments------------------------------------------------------

// uses command line flags to set up program
void parseArguments(int argc, char *argv[], int *numberOfThreads)
{
  char arg; // use to hold argument

  while ((arg = getopt(argc, argv, "n:")) != -1)
  {
    switch (arg)
    {
      case 'n': // set number of threads
	*numberOfThreads = (int) atoi(optarg);
    }
  }
}

//---increment-----------------------------------------------------------

// increments the global counter in a thread-safe fashion
void increment()
{
  // lock mutex so other threads wait in line to access increment()
  pthread_mutex_lock(&counterMutex); 
  
  globalCounter++;

  // unlock mutex so other threads can do their business
  pthread_mutex_unlock(&counterMutex); 
  return;
}

//---work----------------------------------------------------------------

// function a thread will perform
void *work(void *count)
{
  long timesToIncrement = (long)count;
  while (timesToIncrement > 0)
  {
    increment();
    timesToIncrement--;
    //printf("Times to Increment: %lu\n", timesToIncrement);
  }
  return NULL; // will delete the thread later
}

//=======================================================================
//---MAIN----------------------------------------------------------------

int main(int argc, char *argv[])
{
  //-------------------------------------
  // 1) Declare Variables
  //-------------------------------------
  int numberOfThreads = -1;
  pthread_t *threads = NULL;
  long *counts; // number of times to add to global count in a thread
  long timesToIncrementInThread = 1000; // 

  // initialize mutex
  pthread_mutex_init(&counterMutex, NULL);
  
  //-------------------------------------
  // 2) Parse Arguments
  //-------------------------------------
  parseArguments(argc, argv, &numberOfThreads);

  // make sure we have correct number of threads
  if (numberOfThreads < 1)
  {
    printf("Incorrect Arguments\n");
    printf("Specify positive number of threads with '-n' flag\n");
    return 1;
  } 
  //printf("Number of threads: %d\n", numberOfThreads);

  //------------------------------------
  // 3) Assign memory for threads
  //------------------------------------
  // dynamically allocate memory for threads
  threads = (pthread_t *)calloc(numberOfThreads, sizeof(pthread_t));

  
  // dynamically allocate memory for counts 
  counts = (long*)calloc(numberOfThreads, sizeof(long));

  // assign counts for each count because Darrell Long said that
  // the counts could feasibly be different even though we will never
  // do that in this program.... so here we go
  for (int i = 0; i < numberOfThreads; i++)
  {
    counts[i] = timesToIncrementInThread;
  }

  
  //------------------------------------
  // 4) Create and run threads
  //------------------------------------
  // dynamically create threads
  for (int i = 0; i < numberOfThreads; i++)
  {
    pthread_create(&threads[i], NULL, work, (void *)counts[i]);
  }

  // make sure all threads finish before moving on to end program
  for (int i = 0; i < numberOfThreads; i++)
  {
    // join prevents race conditions and forces program to wait
    // until all threads terminate
    pthread_join(threads[i], NULL);
  }

  //-----------------------------------
  // 5) Print result
  //-----------------------------------
  printf("%d\n", globalCounter);
  
  //---------------------------------------------------------------------
  // EXIT PROGRAM
  //---------------------------------------------------------------------

  pthread_mutex_destroy(&counterMutex);
  free(threads);
  free(counts);

  // free threads
  for (int i = 0; i < numberOfThreads; i++)
  {
    pthread_exit(&threads[i]);
  }

  return 0;
}
