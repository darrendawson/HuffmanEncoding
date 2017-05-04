CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = sorting.o

.PHONY: all
all: parfait

sorting: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o sorting  

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) sorting 
