CC = gcc
CFLAGS = -Wall -g -O0 -std=gnu11
LDFLAGS = -lm

all: main

main: main.o ex.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

ex.o: ex.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main