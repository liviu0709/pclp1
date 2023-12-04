CC = gcc
CFLAGS = -Wall -lm
main: cod.c
	$(CC) $(CFLAGS) -o main cod.c -lm
debug:
	$(CC) $(CFLAGS) -g -o debug cod.c -lm
run:
	./main
clean:
	rm -f main debug