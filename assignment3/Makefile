CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = banhammer.o aes.o hash.o bf.o hashtable.o linkedlist.o 

.PHONY: all
all: banhammer

banhammer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o banhammer  

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

aes.o: aes.c
	$(CC) $(CFLAGS) -c aes.c

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) -c hashtable.c

linkedlist.o: linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c


.PHONY: clean
clean:
	rm -f $(OBJECTS) banhammer 
