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

int str_length(char *s) {
    int i = 0;
    while( s[i] != '\0' )
        i++;
    return i;
}

char * strdel(char *s, int pos, int n) {
    int lung = str_length(s);
    if( n > lung )
        return s;
    char *sol = malloc(lung - n + 1);
    strcpy(sol, s);
    for( int i = 0 ; i + pos < lung - n + 1 && pos + i + n < lung ; i++) {
        sol[i + pos] = s[pos + i + n];
    }
    sol[lung - n] = '\0';
    return sol;
}

char * strins(char *s1, int pos, char *s2) {
    int l1 = str_length(s1), l2 = str_length(s2);
    char *sol = malloc(l1 + l2 + 1);
    strcpy(sol, s1);
    strcpy(sol + pos, s2);
    strcpy(sol + pos + l2, s1 + pos);
    return sol;
}

int eq_mask(char *sir, char *masca) {
    int l1 = str_length(sir), l2 = str_length(masca);
    if( l1 != l2 )
        return 0;
    for( int i = 0 ; i < l1 ; i++ ) {
        if( masca[i] != '?' && masca[i] != sir[i] )
            return 0;
    }
    return 1;

}

int eqcuv(char *cuv, char **tablou) {
    for( int i = 0 ; tablou[i] != NULL ; i++ )
        if( strcmp(cuv, tablou[i]) == 0 )
            return 1;
    return 0;
}


int main(void) {
    char *tablou[100] = {"curs1", "curs2", "curs3"};
	char *cuv1 = "curs2", *cuv2 = "curs5";
	printf("curs2 %s in tablou\n",(eqcuv(cuv1, tablou)) ? "este" : "nu este");
	printf("curs5 %s in tablou\n",(eqcuv(cuv2, tablou)) ? "este" : "nu este");

    
}