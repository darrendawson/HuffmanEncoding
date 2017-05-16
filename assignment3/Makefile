CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = banhammer.o aes.o

.PHONY: all
all: banhammer

banhammer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o banhammer  

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

aes.o: aes.c
	$(CC) $(CFLAGS) -c aes.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) banhammer 
