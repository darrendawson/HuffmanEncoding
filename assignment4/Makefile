CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = encoder.o bitvector.o hufftree.o priorityqueue.o

.PHONY: all
all: encoder

encoder: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o encoder  

encoder.o: encoder.c
	$(CC) $(CFLAGS) -c encoder.c

bitvector.o: bitvector.c
	$(CC) $(CFLAGS) -c bitvector.c

hufftree.o: hufftree.c
	$(CC) $(CFLAGS) -c hufftree.c

priorityqueue.o: priorityqueue.c
	$(CC) $(CFLAGS) -c priorityqueue.c


.PHONY: clean
clean:
	rm -f $(OBJECTS) encoder 
