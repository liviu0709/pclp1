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

typedef struct TBec{
    char intensitate, r, g, b;
};

typedef struct TCamera{
    char *nume;
    int nrCrtBecuri;
    struct TBec **becuri;
};

typedef struct TCasa{
    int nrCrtBecuri, nrCrtCamere;
    struct TBec *becuri;
    struct TCamera *camere;
    int nrMaxBecuri, nrMaxCamere;

};

struct TCasa *alocaCasa(int nrMaxBecuri, int nrMaxCamere) {
    struct TCasa *casa = calloc(1, sizeof(struct TCasa));
    casa->nrMaxBecuri = nrMaxBecuri;
    casa->nrMaxCamere = nrMaxCamere;
    casa->becuri = calloc(nrMaxBecuri, sizeof(struct TBec));
    casa->camere = calloc(nrMaxCamere, sizeof(struct TCamera));
    return casa;
}

struct TBec *adaugaBec(char *numeCamera, struct TCasa *casa, char intensitate, char r, char g, char b) {
    for ( int i = 0 ; i < casa->nrCrtCamere ; i++ ) {
        if ( strcmp(casa->camere[i].nume, numeCamera) == 0 ) {
            if ( casa->nrCrtBecuri < casa->nrMaxBecuri ) {
                casa->nrCrtBecuri++;
                casa->camere[i].nrCrtBecuri++;
                casa->becuri[casa->nrCrtBecuri].b = b;
                casa->becuri[casa->nrCrtBecuri].g = g;
                casa->becuri[casa->nrCrtBecuri].r = r;
                casa->becuri[casa->nrCrtBecuri].intensitate = intensitate;
                casa->camere[i].becuri[casa->camere[i].nrCrtBecuri] = &casa->becuri[casa->nrCrtBecuri];
                return &casa->becuri[casa->nrCrtBecuri];
            }
            
        }
    }
    return NULL;
}

struct TCasa *citesteCasa(FILE *in) {
    int nc;
    fscanf(in, "%d", &nc);
    struct TCamera *camere = calloc(nc, sizeof(struct TCamera));
    struct TBec *becuri = calloc(nc * 100, sizeof(struct TBec));
    int nrBecuriFinal = 0;
    for ( int i = 0 ; i < nc ; i++ ) {
        char nume[10];
        fscanf(in, "%s", nume);
        strcpy(camere[i].nume, nume);
        fscanf(in, "%d", &camere[i].nrCrtBecuri);
        int nrBecCamera = 0;
        for ( int j = 0 ; j < camere[i].nrCrtBecuri ; j++ ) {
            char intensitate, r, g ,b;
            fscanf(in, "%c %c %c %c", &intensitate, &r, &g, &b);
            becuri[nrBecuriFinal].b = b;
            becuri[nrBecuriFinal].r = r;
            becuri[nrBecuriFinal].g = g;
            becuri[nrBecuriFinal].intensitate = intensitate;
            camere[i].becuri[nrBecCamera] = &becuri[nrBecuriFinal];
            nrBecuriFinal++;
            nrBecCamera++;
        }
    }
    struct TCasa *casa = alocaCasa(nrBecuriFinal, nc);
    casa->becuri = becuri;
    casa->camere = camere;
    casa->nrCrtBecuri = nrBecuriFinal;
    casa->nrCrtCamere = nc;
    casa->nrMaxCamere = nc;
    casa->nrMaxBecuri = nc * 100;
    return casa;
}

int AvemBecuriAprinse(struct TCasa *casa) {
    for ( int i = 0 ; i < casa->nrCrtCamere ; i++ ) {
        int cnt = 0;
        for ( int j = 0 ; j < casa->camere[i].nrCrtBecuri ; j++ ) {
            if ( casa->camere[i].becuri[j]->intensitate > 0 )
                cnt++;
        }
        if ( cnt > 1 )
            return 0;
    }
    return 1;
}

// posibil sa trebuiasca *(**) 
int compar( const void* a, const void* b) {
    struct TBec *b1 = (struct TBec*) a;
    struct TBec *b2 = (struct TBec*) b;
    return b1->intensitate - b2->intensitate;
}

void sortamBecuri(struct TCasa *casa) {
    for ( int i = 0 ; i < casa->nrCrtCamere ; i++ ) {
        qsort(casa->camere[i].becuri, casa->camere[i].nrCrtBecuri,sizeof(struct TBec), compar);
    }
}

int main(void) {
    struct TCasa *casa = alocaCasa(10, 10);
    printf("%d", casa->becuri[5].intensitate);
    return 0;
}