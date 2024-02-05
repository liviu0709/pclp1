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

typedef struct {
    char *nume;
    char cnp[14];
    char conturi[50][25];
    int nrCrtConturi;
} TPers;

typedef struct {
    char src[25];
    char dest[25];
    int timestamp;
    double suma;
} TTranzactie;

typedef struct {
    int nrCrtTranzactii, nrMaxTranzactii;
    int nrCrtPers, nrMaxPers;
    TPers *pers;
    TTranzactie *tranz;
    TTranzactie **tranzldx;
    TTranzactie **idxData[366];
} TColectie;

TColectie *alocaElem(int nrMaxTranzactii, int nrMaxPers) {
    TColectie *x = calloc(1, sizeof(TColectie));
    x->pers = calloc(nrMaxPers, sizeof(TPers));
    x->tranz = calloc(nrMaxTranzactii, sizeof(TTranzactie));
    x->tranzldx = calloc(nrMaxTranzactii, sizeof(TTranzactie*));
    for( int i = 0 ; i < 366 ; i++ )
        x->idxData[i] = calloc(1, sizeof(TTranzactie*));
    return x;
}

int cmp(const void* a, const void* b) {
    TTranzactie *x = *(TTranzactie**) a;
    TTranzactie *y = *(TTranzactie**) b;
    return x->timestamp - y->timestamp;
}

void subpunct_c(TColectie *x) {
    for ( int i = 0 ; i < x->nrCrtTranzactii ; i++ )
        x->tranzldx[i] = &x->tranz[i];
    qsort(x->tranzldx, x->nrCrtTranzactii, sizeof(TTranzactie*), cmp);
}

int timestampToDay(int x) {
    return 0;
}

void completeaza_idxData(TColectie *x) {
    for ( int i = 0 ; i < 366 ; i++ ) {
        int minim_index, minim = 3600 * 24;
        for ( int j = 0 ; j < x->nrCrtTranzactii ; j++ ) {
            if ( timestampToDay( x->tranz[j].timestamp ) == i + 1 && x->tranz[j].timestamp - timestampToDay( x->tranz[j].timestamp ) < minim ) {
                minim_index = j;
                minim = x->tranz[j].timestamp - ( x->tranz[j].timestamp );
            }
        }
        x->tranzldx[i] = &x->tranz[minim_index];
    }
}

int nr_Pers_cont_Banci_multe(TColectie *x) {
    int cnt = 0;
    for ( int i = 0 ; i < x->nrCrtPers ; i++ ) {
        int ok = 1;
        for ( int j = 0 ; j < x->pers[i].nrCrtConturi && ok; j++ ) {
            for ( int k = 0 ; k < x->pers[i].nrCrtConturi && ok ; k++ ) {
                if ( x->pers[i].conturi[j][3] != x->pers[i].conturi[k][3] || x->pers[i].conturi[j][4] != x->pers[i].conturi[k][4] || x->pers[i].conturi[j][5] != x->pers[i].conturi[k][5] || x->pers[i].conturi[j][6] != x->pers[i].conturi[k][6]) {
                    cnt++;
                    ok = 0;
                    break;
                }
            }
        }
    }
    return cnt;
}

int apartineCont(TPers *p, char *iban) {
    for ( int i = 0 ; i < p->nrCrtConturi ; i++ ) 
        if ( strcmp(p->conturi[i], iban) == 0 )
            return 1;
    return 0;
}

double calcSuma(TColectie *col, char *cnp, int zi) {
    int indice_om;
    for ( int i = 0 ; i < col->nrCrtPers ; i++ ) {
        if ( strcmp(col->pers[i].cnp, cnp) == 0 ) {
            indice_om = i;
            break;
        }
    }
    int indice_tranz_start = -1, indice_tranz_final = -1, indice_zi_start = zi - 1;
    while( col->idxData[zi] = NULL )
        zi++;
    for ( int i = 0 ; i < col->nrCrtTranzactii ; i++ ) {
        if ( &col->tranzldx[i] == col->idxData[indice_zi_start] )
            indice_tranz_start = i;
        if ( &col->tranzldx[i] == col->idxData[zi])
            indice_tranz_final = i;
    }
    if ( indice_tranz_start == -1 )
        return 0;

    double s = 0;
    for ( int i = indice_tranz_start ; i < indice_tranz_final ; i++ ) {
        for ( int j = 0 ; j < col->pers[indice_om].nrCrtConturi ; j++ )
            if( strcmp( col->tranzldx[i]->dest, col->pers[indice_om].conturi[j]) == 0 )
                s += col->tranzldx[i]->suma; 
    }
    return s;
}

void main(void) {
    TColectie *x = alocaElem(10, 10);
    x->nrCrtTranzactii = 3;
    x->tranz[0].timestamp = 69;
    x->tranz[1].timestamp = 1300;
    x->tranz[2].timestamp = -1;
    subpunct_c(x);
    for ( int i = 0 ; i < 3 ; i++ )
        printf("%d\n", x->tranzldx[i]->timestamp);
}