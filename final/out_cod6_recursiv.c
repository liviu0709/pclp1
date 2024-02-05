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

void g(int a[], int x) {
    for ( int i = 0 ; i < 3 ; i++ )
        printf("%d ", a[i]);
    printf("\n");
}

int f(int a[], int x) {
    for ( int i = x ; i < 3 ; i++ ) {
        a[x] += 3;
        if ( x == 2 )
            g(a, x);
        else {
            f(a, x + 1);
            a[x + 1] = 0;
        }
    }
}

int main(){
    int a[3] = {0};
    f(a, 0);
    return 0;
}