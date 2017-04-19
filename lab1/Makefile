CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = cat.o
OBJECTS2 = hello.o

.PHONY: all
all: cat hello

cat: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o cat

hello: $(OBJECTS2)
	$(CC) $(CFLAGS) $(OBJECTS2) $(CFLAGS) -o hello

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c

hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c 

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(OBJECTS2) cat hello
