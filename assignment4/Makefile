CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = encoder.o 

.PHONY: all
all: encoder

encoder: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o encoder  

encoder.o: encoder.c
	$(CC) $(CFLAGS) -c encoder.c


.PHONY: clean
clean:
	rm -f $(OBJECTS) encoder 
