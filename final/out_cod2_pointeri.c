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

void foo(int *x, void *y) {
    printf("%d ",(char*)x  - (char*)y );
    ++x;
}

int main(){
    int i, *p;
    p = calloc(10, sizeof(int));
    void *p1 = p;
    for ( int i = 0 ; i < 10 ; i++, p++ ) {
        foo(p, p1);
    }
    return 0;
}