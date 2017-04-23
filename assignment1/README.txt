Darren Dawson, dwdawson@ucsc.edu
cmps 12b, Assignment 1 README

To execute: $ make parfait
	    $./parfait

This is a program that utilizes bitvectors in order to determine the prime factorizations of numbers up to a default 100,000. 
However, if a user passes in an int argument, the program will go up to that argument instead.

This program also identifies perfect numbers and provides the factors of those.

There are 3 files: parfait, bv, and sieve

 - parfait.c is the main file. It calls on bv.h and sieve.h in order to create a list of prime numbers.
	It then uses that list to efficiently find the prime factors of a given number. Because we already have the prime numbers,
	finding the prime factors is as simple as looking for a 0 remainder on currentNum%prime, and looping through the prime numbers
	up to the currentNum itself.

	parfait.c also includes a bubble sort and a findPerfectNums function in order to, well, find perfect numbers.
	I used the formula 
		n = p^(2-1)*(p^2-1) 
	in order to store the indexes of the perfect numbers. This way, I don't need to peform rigorous mathematical operations
	on each number. Instead, I only have to find the factors for the numbers I know that will  be perfect. This makes the 
	program much more efficient.

- bv.c handles bit vector manipulation. bv.h was written by the instructor, Darrel Long. As such, while the code in bv.c 
	is of my own creation, the datatype and function declarations are of his inception.
	The bitvector is an array of uint8_ts. bv.c contains the following functions:
	- newVec: creates a new bit vector
	- delVec: deletes a bit vector (by freeing its space in memory)
	- one: turns all bits in a vector to 1
	- setBit: makes a bit at designated index in bit vector equal to 1
	- clrBit: makes a bit at a designated index in bit vector equal to 0
	- valBit: returns the value of a bit at a designated index
	- lenVec: returns the length of a vector

- sieve.c finds all the prime numbers up to a point. It uses bv in order to clear the bits of non-prime numbers.
	This sieve uses the sieve of Erosthenas - I did not come up with this algorithm. I also did not write the code:
	again, Darrel Long provided the C code for the sieve of Erosthenas. This program uses that.


The general structure for parfait goes as follows.


Create bit vector with all the prime numbers up to a designated size
 - use the sieve for this

Determine the perfect numbers
 - store in array called perfectNumbers

Loop through the real numbers
 - if currentNum is prime -> print P and move on
 - if currentNum is composite -> print the prime factors
 - if currentNum is perfect -> print all factors


