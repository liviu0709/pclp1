#include "structuri.h"
#include <stdlib.h>
#include <stdio.h>

void *inc(void *p, int size) {
    return ((int *) p) + size;
}

int main(void) {
    // double v[3] = {1, 2, 3};
    // double *p = inc(v, 1);
    // printf("%lf\n", *p);
    unsigned int b = 1;
    b <<= (1 & 2 & 3);
    printf("%d\n", b);
    
    b = 1 << 31;
    // 1000000000...
    // %u-> 2 ^ 31 * b0 + 2 ^ 30 * b1 + ... + 2 ^ 0 * b32
    // %d-> -2 ^ 31 * b0 + 2 ^ 30 * b1 + ... + 2 ^ 0 * b32
    printf("%u %d\n", b, b);
    return 0;
}