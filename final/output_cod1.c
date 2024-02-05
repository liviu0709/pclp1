#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f() {
    static int c;
    return ++c;
}

int main() {
    printf("%d\n", f());
    printf("%d\n", f()+f());
    return 0;
}

/*
outputul este:
1
5
(static face var c sa isi pastreze valoarea cand f e apelat iar)
*/