CC = gcc
CFLAGS = -Wall -std=gnu11
LDLIBS = -lm

srcs = $(wildcard *.c)
target = main

all: build

build: $(target)

$(target): $(srcs)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)