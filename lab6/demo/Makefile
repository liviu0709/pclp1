CC = gcc
CFLAGS = -Wall -std=gnu17 -O0
LDFLAGS = -lm

srcs = $(wildcard *.c)

all: $(srcs)
	$(CC) $(CFLAGS) -o lab6 $(srcs) $(LDFLAGS)

clean:
	rm -f lab6