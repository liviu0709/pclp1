CC = gcc
CFLAGS = -Wall -lm
main: lab3.c
	$(CC) $(CFLAGS) -o main lab3.c functii.c -lm
run:
	./main < "Matrice n m"
clean:
	rm -f main