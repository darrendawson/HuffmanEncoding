/* Darren Dawson, dwdawson@ucsc.edu
   Assignment 0: Left Right Center
   CMPS12b
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//if more than 1 player has money, return true
//if only 1 player has money, return false
int stillPlaying(int money[], int numPlayers)
{
  int playersLeft = 0;
  for(int i=0; i<numPlayers; i++)
  {
    if(money[i]>0)
    {
      playersLeft++;
    }
  }
  if(playersLeft>1)
  {
    return 1; //true, still playing
  }
  return 0; //false, done playing
}

//Returns index of player that has non-zero sum of money
//This function only called after determining the game is over
int getWinnerIndex(int money[], int numPlayers)
{
  for(int i=0; i<numPlayers; i++)
  {
    if(money[i]>0)
    {
      return i;
    }
  }
  return -1;
}

//Returns int value of next index
//next index loops back to 0 when past array bounds
int nextIndex(int index, int numPlayers)
{
  int resultIndex;
  if(index>=(numPlayers-1))
  {
    resultIndex = 0;
  } else {
    resultIndex = index + 1;
  }
  return resultIndex;
}

//---------------------------------------------------------
// MAIN
//---------------------------------------------------------

int main(void)
{
  // <Variable declarations>
  int seed;
  int numPlayers;
  bool playing = true;

  //variables about die
  //typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
  //faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
  //int randomNum;

  //variables concerning players
  int index = 0;  //keeps track of which player's turn currently on
  /*
  const char *names[] = {"Whoopi", "Dale", "Rosie", "Jimmie", "Barbara",
			 "Kyle", "Raven", "Tony", "Jenny", "Clint"};
  */

  // end variable declaration ---------------------
  
  // <User IO>
  //Get seed from user, set random seed
  printf("Random Seed: ");
  scanf("%d", &seed);
  srand(seed);
  
  //Get number of players
  printf("Number of players: ");
  scanf("%d", &numPlayers);

  //Create money array the size of numPlayers
  int money[numPlayers];
  for(int i=0;i<numPlayers;i++)
  {
    money[i] = 3;  //everyone starts off with $3
  }
  // end user IO ---------------------------------

  // <Play Game Loop>
  do
  {
    //player turn, if still in game
    if(money[index]>0)
    {
      money[index] = money[index] - 1;
      printf("%d", index);
      printf(": ");
      printf("%d", money[index]);
      printf("\n");
    }
    index = nextIndex(index, numPlayers);
    
    //if only 1 player has money, playing=false
    playing = stillPlaying(money, numPlayers);
  } while(playing);

  //Congratulate the winner
  printf("Winner: ");
  printf("%d", getWinnerIndex(money, numPlayers));
  
  //TEST STUFF BELOW ----------------------------
  //print out random numbers
  /*
  for(int i=0;i<10;i++)
  {
    randomNum = rand()%6;
    int move = die[randomNum];
    printf("[%d] Acquired Random number: %d\n", i, randomNum);
    printf("%d", move);
  }
  */
  

  //printf(names[0]);
  //printf("%d", die[5]);

  
  //End program
  printf("\n");
  return 0;
}




