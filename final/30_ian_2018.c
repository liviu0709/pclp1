#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TTranzactie{
    char nume[25];
    double suma;
    struct TTranzactie* urmTranzactie;
} TTranzactie;


typedef struct {
    unsigned int id;
    char timestamp[11];
    unsigned int lung;
    TTranzactie* lantTranzactie;
} TSursa;

TSursa *alocaSursa(unsigned int lungT) {
    TSursa *x = calloc(1, sizeof(TSursa));
    x->lantTranzactie = calloc(lungT, sizeof(TTranzactie));
    x->lung = lungT;
    for ( int i = 0 ; i < lungT ; i++ ) {
        if ( i + 1 < lungT )
            x->lantTranzactie->urmTranzactie = &x->lantTranzactie[i + 1];
        else
            x->lantTranzactie->urmTranzactie = NULL;
    }
    return x;
}

TSursa **alocaSurse(unsigned int nrSurse, unsigned int *lungT) {
    TSursa **x = calloc(nrSurse, sizeof(TSursa*));
    for ( int i = 0 ; i < nrSurse ; i++ ) {
        x[i] = calloc(1, sizeof(TSursa));
        x[i]->lung = lungT[i];
        x[i]->lantTranzactie = calloc(lungT[i], sizeof(TTranzactie));
        for ( int j = 0 ; j < lungT[j] ; j++ ) {
            if ( j + 1 < lungT[i] )
                x[i]->lantTranzactie->urmTranzactie = &x[i]->lantTranzactie[j + 1];
            else
                x[i]->lantTranzactie->urmTranzactie = NULL;
        }
    }
    return x;
}

TSursa **read(FILE *in) {
    unsigned int nrS;
    fscanf(in, "%d", &nrS);
    TSursa **x = calloc(nrS, sizeof(TSursa*));
    unsigned int *lung = calloc(nrS, sizeof(unsigned int));
    for ( int i = 0 ; i < nrS ; i++ ) {
        fscanf(in, "%u", &lung[i]);
        x[i] = alocaSursa(lung[i]);
        fscanf(in, "%u %s", &x[i]->id, x[i]->timestamp);
        for ( int j = 0 ; j < lung[i] ; j++ ) {
            fscanf(in, "%s %lf", x[i]->lantTranzactie[j].nume, &x[i]->lantTranzactie[j].suma);
        }
    }
    return x;
}

void detecteazaSiEliminaCiclu(TSursa *sursa) {
    for ( int i = 0 ; i < sursa->lung - 1 ; i++ ) {
        if ( strcmp(sursa->lantTranzactie[i].nume, sursa->lantTranzactie[i + 1].nume) == 0 && sursa->lantTranzactie[i].suma == sursa->lantTranzactie[i + 1].suma ) {
            if ( i + 2 < sursa->lung )
                sursa->lantTranzactie[i].urmTranzactie = &sursa->lantTranzactie[i + 2];
            else
                sursa->lantTranzactie[i].urmTranzactie = NULL;
        }

    }
}

void adaugaPers(char **f, int *cnt, char *x) {
    for ( int i = 0 ; i < 100 ; i++ ) {
        if ( strcmp(f[i], x) == 0 )
            cnt[i]++;
    }
}

char* persoanaTranzactiiMax(TSursa **surse, unsigned int nrSurse) {
    char **frec = calloc(100, sizeof(char*));
    int *cnt = calloc(100, sizeof(int));
    for ( int i = 0 ; i < 100 ; i++ ) 
        frec[i] = calloc(25, sizeof(char));
    for ( int i = 0 ; i < nrSurse ; i++ ) {
        for ( int j = 0 ; j < surse[i]->lung ; j++ ) {
            adaugaPers(frec, cnt, surse[i]->lantTranzactie[j].nume);
        }
    }
    int maxim = 0;
    for ( int i = 0 ; i < 100 ; i++ )
        if ( cnt[i] > maxim )
            maxim = cnt[i];
    for ( int i = 0 ; i < 100 ; i++ )
        if ( cnt[i] == maxim )
            return frec[i];
    return NULL;
}

void dezalocaSurse(TSursa **surse, unsigned int nrSurse) {
    for ( int i = 0 ; i < nrSurse ; i++ ) {
        free(surse[i]->lantTranzactie);
        free(surse[i]);
    }
    free(surse);
}