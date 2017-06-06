CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = encode.o bitvector.o hufftree.o priorityqueue.o

.PHONY: all
all: encode

encode: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o encode  

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

bitvector.o: bitvector.c
	$(CC) $(CFLAGS) -c bitvector.c

hufftree.o: hufftree.c
	$(CC) $(CFLAGS) -c hufftree.c

priorityqueue.o: priorityqueue.c
	$(CC) $(CFLAGS) -c priorityqueue.c


.PHONY: clean
clean:
	rm -f $(OBJECTS) encoder 
