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

int main(void) {
    int d = 30;
    int *p = &d;
    printf("%d %d\n", d, *p);
    *p = 32;
    printf("%d %d\n", d, *p);
    /* Presupunem ca malloc-ul nu esueaza */
    p = malloc(sizeof(int));
    d = *p;
    p = &d;
    printf("%d %d\n", d, *p);
    free(p);
    return 0;
}
