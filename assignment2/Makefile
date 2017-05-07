CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = sorting.o minsort.o bubblesort.o mergesort.o quicksort.o insertionsort.o

.PHONY: all
all: sorting

sorting: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o sorting  

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

minsort.o: minsort.c
	$(CC) $(CFLAGS) -c minsort.c

bubblesort.o: bubblesort.c
	$(CC) $(CFLAGS) -c bubblesort.c

mergesort.o: mergesort.c
	$(CC) $(CFLAGS) -c mergesort.c

quicksort.o: quicksort.c
	$(CC) $(CFLAGS) -c quicksort.c

insertionsort.o: insertionsort.c
	$(CC) $(CFLAGS) -c insertionsort.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) sorting 
