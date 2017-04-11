Darren Dawson, dwdawson@ucsc.edu
Assignment 0: Left Right Center
04/11/17
CMPS12b 

------------------------
HOW TO RUN
------------------------
1) run $ make
2) run $ ./lrc

-----------------------
ABOUT
-----------------------
Files: lrc.c

functions:
 - int stillPlaying(int[], int): returns true if still playing (more than one player has money)
 - int getWinnerIndex(int[], int): returns index of the winner 
 - getNumRolls(int): returns number of rolls a player has to take in turn
 - nextIndex(int, int): returns the index of the player to the right (index +1)
	loops around so you don't run off the end of the array money[]
 - previousIndex(int, int): returns index of player to the left (index -1)
	loops so you don't run off end of array money[]

main()
 - get seed from user for random number generation
 - get number of players from user (between 2-10)
Gameloop 
 - If a player has money, they take a turn
 - determine number of dice to roll
 - roll the dice, follow rules concerning money on what each die roll means
 - print out the results using a switch statement
 - move on to next player

------------------------
HOW TO PLAY LRC
------------------------
Left, Right, Center is a game with rules as follows:

Some number of players 1 < k ≤ 10 sit around a table, each player has in her hand $3. There are three dice, and
each die has 6 faces and is labeled: 3 × •, 1 × L, 1 × R or 1 × C.
1. Beginning with player 1, roll the dice:
(a) If the player has $3 or more then she rolls three dice; if she has $2 then she rolls two dice; if she has only
$1 then she rolls one die; if she has no money then she must pass.
(b) If the player rolls L then she gives $1 for each L to the player on her left.
(c) If the player rolls R then she gives $1 for each R to the player on her right.
(d) If the player rolls C then she puts $1 for each C in the pot in the center.
(e) If the player rolls • then she ignores it.
2. Move to the next player in sequence.
3. Repeat until only one player has any money.
