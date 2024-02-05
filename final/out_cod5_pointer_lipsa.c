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

int main(){
    int (pointer)(int, int, int);
    pointer = mul; // nu compileaza
    printf("%d %d\n", pointer(2, 3, 4), 2 * 3 * 4);
    return 0;
}