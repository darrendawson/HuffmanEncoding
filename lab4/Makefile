CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Werror -std=c99 
OBJECTS = increment.o

.PHONY: all
all: increment

increment: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o increment -lpthread  

increment.o: increment.c
	$(CC) $(CFLAGS) -c increment.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) increment 
