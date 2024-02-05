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

/*
s[len - i] este 0 la inceput
s[len] = terminator
=> nu afiseaza nimic
*/

int main(){
    char p[20];
    char *s = "string";
    int len = strlen(s);
    int i;
    printf("%d %d\n", sizeof(s), sizeof(p));
    for ( i = 0 ; i < len ; i++ )
        p[i] = s[len - i];
    printf("Rez este: %s\n", p);
    printf("%d\n", len);
    return 0;
}