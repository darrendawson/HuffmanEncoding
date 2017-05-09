CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Werror -std=c99 
OBJECTS = gdbLab.o

.PHONY: all
all: gdbLab

gdbLab: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o gdbLab -lm  

gdbLab.o: gdbLab.c
	$(CC) $(CFLAGS) -c gdbLab.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) gdbLab 
