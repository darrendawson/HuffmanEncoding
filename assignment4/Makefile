CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g -lm
ENCODEOBJECTS = encode.o bitvector.o hufftree.o priorityqueue.o
DECODEOBJECTS = decode.o bitvector.o hufftree.o priorityqueue.o

.PHONY: all
all: encode decode

encode: $(ENCODEOBJECTS)
	$(CC) $(CFLAGS) $(ENCODEOBJECTS) $(CFLAGS) -o encode

decode: $(DECODEOBJECTS)
	$(CC) $(CFLAGS) $(DECODEOBJECTS) $(CFLAGS) -o decode  

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

bitvector.o: bitvector.c
	$(CC) $(CFLAGS) -c bitvector.c

hufftree.o: hufftree.c
	$(CC) $(CFLAGS) -c hufftree.c

priorityqueue.o: priorityqueue.c
	$(CC) $(CFLAGS) -c priorityqueue.c


.PHONY: clean
clean:
	rm -f $(ENCODEOBJECTS) $(DECODEOBJECTS) encode decode
