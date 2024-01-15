CFLAGS=-Wall -Werror

.PHONY: clean run-bitpacking run-planner

main: main.c timelib.c
	gcc main.c timelib.c $(CFLAGS) -o main

run-main: main
	./main

run-bitpacking: bitpacking
	./bitpacking

run-planner: planner
	./planner

bitpacking: bitpacking.c timelib.c
	gcc bitpacking.c timelib.c $(CFLAGS) -o bitpacking

planner: planner.c timelib.c
	gcc planner.c timelib.c $(CFLAGS) -o planner

clean:
	rm -f bitpacking planner
