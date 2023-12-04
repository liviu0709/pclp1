CFLAGS=-Wall -Werror

.PHONY: run-task1 run-task2 clean1 clean2

run-task1: task1
	./task1

task1: task1.c
	gcc task1.c $(CFLAGS) -o task1

run-task2: task2
	./task2

task2: task2.c
	gcc task2.c $(CFLAGS) -o task2

clean1: 
	rm -f task1

clean2: 
	rm -f task2