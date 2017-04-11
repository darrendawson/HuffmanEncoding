/* Darren Dawson, dwdawson@ucsc.edu
   Assignment 0: Left Right Center
   CMPS12b
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// function prototypes
int stillPlaying(int money[], int numPlayers);
int getWinnerIndex(int money[], int numPlayers);
int getNumRolls(int money);
int nextIndex(int index, int numPlayers);
int previousIndex(int index, int numPlayers);

int main(void)
{
  // <Variable declarations>
  int seed;             // user input determines random seed
  int numPlayers;	
  int pot = 0;		
  int winnerIndex;	
  bool playing = true;  // false if game over
  int* money = NULL;    // pointer to money array

  //variables about die
  typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
  faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

  //variables concerning players
  int index = 0;  //keeps track of which player's turn currently on
  const char *names[] = {"Whoopi", "Dale", "Rosie", "Jimmie", "Barbara",
			 "Kyle", "Raven", "Tony", "Jenny", "Clint"};
  

  // end variable declaration ---------------------
  
  // <User IO>
  //Get seed from user, set random seed
  printf("Random Seed: ");
  scanf("%d", &seed);
  srand(seed);
  
  //Get number of players
  do
  {
    printf("Number of players [2-10]: ");
    scanf("%d", &numPlayers);
    //bound numPlayers to [2,10]
  } while(numPlayers <= 1 || numPlayers > 10);

  //Create money array the size of numPlayers
  money = (int*) calloc(numPlayers, sizeof(int));
  
  for(int i=0;i<numPlayers;i++)
  {
    money[i] = 3;  //everyone starts off with $3
  }
  // end user IO ---------------------------------

  // <Play Game Loop>
  do
  {
    //take player turn, if still in game
    if(money[index]>0)
    {
      //print current player's name
      printf("%s rolls... ", names[index]);
      
      //determine number of rolls current player takes
      int numRolls = getNumRolls(money[index]);

      //Roll dice numRolls times
      for(int i=0; i<numRolls; i++)
      {
	//roll the die
	int randomNum = rand()%6;

	//performs action based off die roll
	switch(die[randomNum])
	{
	  case LEFT:  
	    //give money to person on left
	    money[index] = money[index] - 1;
	    money[previousIndex(index, numPlayers)] =
	      money[previousIndex(index, numPlayers)] + 1;
	    
	    printf(" gives $1 to ");
	    printf(names[previousIndex(index, numPlayers)]);
	    break;
	    
	  case RIGHT:
	    //give money to person on right
	    money[index] = money[index] - 1;
	    money[nextIndex(index, numPlayers)] =
	      money[nextIndex(index, numPlayers)] + 1;
	    
	    printf(" gives $1 to ");
	    printf(names[nextIndex(index, numPlayers)]);
	    break;
	    
	  case CENTER:
	    //give money to pot
	    money[index] = money[index] - 1;
	    pot = pot + 1;
	    printf(" puts $1 in the pot");
	    break;
	    
	  case PASS:
	    printf(" gets a pass");
	    break;
	}
      }
      printf("\n"); // new line before next turn
    }
    //move on to the next player
    index = nextIndex(index, numPlayers);
    
    //if only 1 player has money, game over
    playing = stillPlaying(money, numPlayers);
  } while(playing);

  // end game loop -------------------------------

  //Congratulate the winner
  winnerIndex = getWinnerIndex(money, numPlayers);
  printf("%s wins the $%d pot with $%d left in the bank!\n", names[winnerIndex], pot, money[winnerIndex]);

  //End program
  free(money); //yes plz
  return 0;
}

//----------------------------------------------------------
// Functions!
//----------------------------------------------------------

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

//takes in a number, returns number of rolls player has to take
int getNumRolls(int money)
{
  // if money>=3, player takes 3 rolls
  // else, return rolls = money
  return (money > 3) ? 3 : money;
}

//Returns int value of next index (player to right)
//next index loops back to 0 when past array bounds
int nextIndex(int index, int numPlayers)
{
  if(index>=(numPlayers-1))
  {
    return 0;
  }
  return (index + 1);
}

//returns int value of player to the left
//Loops to max when at 0
int previousIndex(int index, int numPlayers)
{
  if(index<=0)
  {
    return (numPlayers-1);
  }
  return (index-1);
}



