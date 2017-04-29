Darren Dawson, dwdawson@ucsc.edu
CMPS 12m, lab 2

---Question 1----
A C-style string with n characters occupies n+1 bytes in memory.
This is because a char is the size of 1 byte, and every string needs a null termination character at the end.

The lab manual states that "This mistake happens often with null-termination characters on strings, because programmers
			     forget to allocate an extra byte beyond the prima facie length of their string"

On line 346, the tutorial callocs an array of chars without adding a null bit to the end
	It should be:
		 myString = calloc(stringSize + 1, sizeof(char));
	so as to allocate a String of the correct size 


---Question 2----
valgrind reveals that a chunk of memory that was allocated on line 445 of mallocTutorial was not freed properly.
This was in the function demonstrateRealloc()




---arraylist.c----
This is a program that was created in order to learn dynamic memory allocation.
It mirrors the functionality of an int arraylist, where you can:
 - add new ints
 - print out the list
 - quit

It uses calloc and realloc in order to allocate memory. It reallocs to twice the current size in order to optimize memory efficiency.

Thanks for reading my lab!
