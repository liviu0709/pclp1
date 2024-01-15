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
#include <stdarg.h>


/*
Scrieti o functie cu numar variabil de parametri care afiseaza valoarea maxima / minima a parametrilor dati - 
va trebui sa se utilizeze o macro instructiune. 
Parametrii vor fi 'cititi' pana la intalnirea unei valori negative 
(nu trebuie luata in considerare la calcularea minimului/maximului).

Programul compilat fara definirea simbolul MAX va afisa minimul dintre parametrii, 
iar compilat cu -DMAX va afisa maximul dintre parametrii.
gcc -o ex1 -DMAX ex1.c
*/

int ex1(int num, ...) {
    va_list valist;
    va_start(valist, num);
    int x = 0;
    int sol = va_arg(valist, int);
    while ( x >= 0 ) {
        int x = va_arg(valist, int);
        if ( x < 0 )
            break;
        #ifdef MAX
        if( x > sol )
            sol = x;
        #else
        if ( x < sol )
            sol = x;
        #endif

    }
    va_end(valist);
    return sol;

}

/*
Scrieti o functie cu numar variabil de parametri care determina parametrul cu frecventa de aparitie maxima.
Daca sunt 2 parametrii cu aceesi frecventa, atunci se va afisa cel cu valoarea cea mai mica. 
Parametrii vor fi 'cititi' pana la intalnirea unei valori negative (nu trebuie luata in considerare)
*/

int ex2(int num, ...) {
    va_list valist;
    va_start(valist, num);
    int sol = 0;
    int *frec = calloc(1000, sizeof(int));
    frec[num]++;
    while( 1 ) {
        int x = va_arg(valist, int);
        if ( x < 0 )
            break;
        frec[x]++;
    }
    va_end(valist);
    for ( int i = 0 ; i < 1000 ; i++ )
        if ( frec[i] > frec[sol] )
            sol = i;
    for ( int i = 0 ; i < 1000 ; i++ )
        if ( frec[i] == frec[sol] )
            return i;
    return sol;
}

/*
Scrieti o functie cu numar variabil de parametri care scrie intr-un fisier parametrii, ordonati crescator.
Parametrii vor fi 'cititi' pana la intalnirea unei valori negative (acea valoare nu trebuie luata in considerare).
*/

void ex3(int num, ...) {
    va_list valist;
    va_start(valist, num);
    FILE *f = fopen("ex3.txt", "w");
    int *v = calloc(1000000, sizeof(int));
    int j;
    for ( j = 0 ; 1 ; j++ ) {
        int x = va_arg(valist, int);
        if ( x < 0 )
            break;
        v[j] = x;
    }
    va_end(valist);
    for ( int i = 0 ; i < j ; i++ )
        for ( int k = i + 1 ; k < j ; k++ )
            if ( v[i] > v[k] ) {
                int aux = v[i];
                v[i] = v[k];
                v[k] = aux;
            }
    for ( int i = 0 ; i < j ; i++ )
        fprintf(f, "%d ", v[i]);
    fclose(f);
    free(v);
}

/*
Sa se realizeze un program care in functie de starea simbolului NEIGHBOUR
sa determine cel mai mare numar prim mai mic sau egal cu un numar/ cel mai mic numar prim mai mare sau egal cu acel numar. 
Daca simbolul este definit se va calcula cel mai mare numar prim mai mic sau egal cu acel numar, 
iar in caz contrar cel mai mic numar prim mai mare sau egal cu numarul dat. 
Variabila n este data ca parametru in linia de comanda, 
iar definirea simbolului se va face utilizand o optiune de preprocesare a gcc-ului.
*/

int ePrim(int x) {
    for ( int i = 2 ; i * i <= x ; i++ )
        if ( x % i == 0 )
            return 0;
    return 1;
}

int ex4( int x ) {
    int sol = 0;
    #ifdef NEIGHBOUR
    for ( int i = x ; i >= 2 ; i-- ) {
        //printf("%d\n", i);
        if ( ePrim(i) )
            return i;
    }
    #else
    for ( int i = x ; i <= 1000000 ; i++ )
        if ( ePrim(i) )
            return i;
    #endif
    return sol;
}

int main(int NU_ESTI_BUN_DE_NIMIC, char* x[]) {
    //printf("%s\n", x[1]);
    printf("%d\n", ex4(atoi(x[1])));
}