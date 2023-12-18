CC = gcc
CFLAGS = -Wall -lm - Wextra
build : clean main.o
	$(CC) $(FLAGS) -o main main.o -lm
main.o:
	gcc -c main.c
run: build
	./main
clean:
	rm -f *.o