CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = arraylist.o

.PHONY: all
all: arraylist

arraylist: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o arraylist -g 

arraylist.o: arraylist.c
	$(CC) $(CFLAGS) -c arraylist.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) arraylist 
