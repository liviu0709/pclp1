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

typedef struct TDest {
    char nume[101];
    char cod[4];
    struct TDest *next;
} TDest;

typedef struct {
    unsigned int nr_T;
    unsigned int *lung;
    TDest **p;
} TItinerariu;

TDest *alocDest(char *oras, char *tara) {
    TDest *x = calloc(1, sizeof(TDest));
    strcpy(x->nume, oras);
    strcpy(x->cod, tara);
    x->next = NULL;
    return x;
}

TItinerariu *alocaIt(unsigned int nr_Trasee, unsigned int *lung_t, char **orase, char **trasee) {
    TItinerariu *x = calloc(1, sizeof(TItinerariu));
    x->lung = calloc(nr_Trasee, sizeof(unsigned int));
    for ( int i = 0 ; i < nr_Trasee ; i++ )
        x->lung[i] = lung_t[i];
    x->p = calloc(nr_Trasee, sizeof(TDest*));
    int cnt = 0;
    for ( int i = 0 ; i < nr_Trasee ; i++ ) {
        TDest *pointer = x->p[i];
        for ( int j = 0 ; j < lung_t[i] ; j++ ) {
            pointer = alocDest(orase[cnt], trasee[cnt]);
            cnt++;
            pointer = pointer->next;
        }
    }
    return x;
}

TItinerariu *read(FILE *in) {
    unsigned int nr_Trasee;
    fscanf(in, "%d", &nr_Trasee);
    unsigned int *lung_t = calloc(nr_Trasee, sizeof(unsigned int));
    int cnt = 0;
    for ( int i = 0 ; i < nr_Trasee ; i++ ) {
        fscanf(in, "%u", &lung_t[i]);
        cnt += lung_t[i];
    }
    char **orase = calloc(cnt, sizeof(char*));
    char **trasee = calloc(cnt, sizeof(char*));
    for ( int i = 0 ; i < cnt ; i++ ) {
        orase[i] = calloc(101, sizeof(char));
        trasee[i] = calloc(4, sizeof(char));
    }
    for ( int i = 0 ; i < cnt ; i++ ) {
        fscanf(in, "%s %s", orase[i], trasee[i]);
    }
    TItinerariu *x = alocaIt(nr_Trasee, lung_t, orase, trasee);
    return x;
}

typedef struct {
    char oras[101];
    char tara[4];
    int nr_Ap;
} Oras;

void adaug_oras(char *oras, char *tara, Oras *x, int *crt) {
    for ( int i = 0 ; i < *crt ; i++ ) {
        if ( strcmp(x->oras, oras) == 0 && strcmp(x->tara, tara))
            return;
    }
    strcpy(x[*crt].oras, oras);
    strcpy(x[*crt].tara, tara);
    x[*crt].nr_Ap++;
    *crt++;
}

Oras *caut_oras(char *oras, char *tara, Oras *x, int *crt) {
    for ( int i = 0 ; i < *crt ; i++ )
        if ( strcmp(x->oras, oras) == 0 && strcmp(x->tara, tara)) {
            x[i].nr_Ap++;
            return &x[i];
        }
    adaug_oras(oras, tara, x, crt);
    return &x[*crt - 1];
}

int nrAparitii(TItinerariu *x, char *oras) {
    int cnt = 0, *crt = 0;
    for ( int i = 0 ; i < x->nr_T ; i++ ) {
        cnt += x->lung[i];
    }
    Oras *frec = calloc(cnt, sizeof(Oras));
    for ( int i = 0 ; i < x->nr_T ; i++ ) {
        TDest *p = x->p[i];
        for ( int j = 0 ; j < x->lung[i]; j++ ) {
            caut_oras(p->nume, p->cod, frec, crt);
            p = p->next;
        }
    }
    int max = 0;
    for ( int i = 0 ; i < *crt ; i++ ) {
        if ( frec[i].nr_Ap > max )
            max = frec[i].nr_Ap;
    }
    for ( int i = 0 ; i < *crt ; i++ ) {
        if ( frec[i].nr_Ap == max ) {
            strcpy(oras, frec[i].oras);
            return max;
        }
    }
    return -1;
}

void cmp(void const* a, void const* b) {
    char *x = *(char**)a;
    char *y = *(char**)b;
    return strcmp(x, y);
}

char** sorteazaOraseDinTara(TItinerariu *x, char *tara) {
    int cnt = 0, crt = 0;
    for ( int i = 0 ; x->nr_T ; i++ ) {
        TDest *p = x->p[i];
        for ( int j = 0 ; j < x->lung[i] ; j++ ) {
            if ( strcmp(p->cod, tara) )
                cnt++;
        }
    }
    char **sate = calloc(cnt, sizeof(char*));
    for ( int i = 0 ; i < cnt ; i++ )
        sate[i] = calloc(101, sizeof(char));
    for ( int i = 0 ; x->nr_T ; i++ ) {
        TDest *p = x->p[i];
        for ( int j = 0 ; j < x->lung[i] ; j++ ) {
            if ( strcmp(p->cod, tara) )
                strcpy(sate[crt], p->nume), crt++;
        }
    }
    qsort(sate, crt, sizeof(char*), cmp);
    for ( int i = 0 ; i < crt - 1; i++ ) {
        if ( strcmp(sate[i], sate[i + 1] == 0 ) ) {
            for ( int j = i ; j < crt - 1; j++ )
                sate[j] = sate[j + 1];
            i--;
        }
    }
    return sate;
}

void dezalocIt(TItinerariu *x) {
    free(x->lung);
    free(x->p);
    free(x);
}

