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
    int an;
    struct TActor *distributie[100];
    int nrCrtD;
} TFilm;

typedef struct TActor{
    char *nume;
    int nrCrtFilme;
    TFilm *filme[100];
} TActor;

typedef struct {
    int nrCrtFilme, nrMaxFilme;
    int nrCrtActori, nrMaxActori;
    TActor *actori;
    TFilm *filme;
    TActor **idxActori;
    TFilm **idxFilme;
} TIMDB;

TIMDB *alocaElement(int nrMaxActori, int nrMaxFilme) {
    TIMDB *x = calloc(1, sizeof(TIMDB));
    x->nrMaxActori = nrMaxActori;
    x->nrMaxFilme = nrMaxFilme;
    x->filme = calloc(nrMaxFilme, sizeof(TFilm));
    x->actori = calloc(nrMaxActori, sizeof(TActor));
    x->idxActori = calloc(nrMaxActori, sizeof(TActor*));
    x->idxFilme = calloc(nrMaxFilme, sizeof(TFilm*));
    return x;
}

TFilm *cauta_film(TIMDB *c, char *nume) {
    for ( int i = 0 ; i < c->nrCrtFilme ; i++ )
        if( strcmp(c->filme[i].nume, nume) == 0 )
            return &c->filme[i];
    return NULL;
}

TActor *cauta_actor(TIMDB *c, char *nume) {
    return NULL;
}

TActor *adaugaActorFilm(TIMDB *c, char *numea, char *numef) {
    TFilm *x = cauta_film(c, numef);
    TActor *y = cauta_actor(c, numea);
    if ( x->nrCrtD == 100 || y->nrCrtFilme == 100 )
        return NULL;
    x->distributie[x->nrCrtD] = y;
    x->nrCrtD++;
    y->filme[y->nrCrtFilme] = x;
    y->nrCrtFilme++;
    return y;
}

int cmp(const void* a, const void* b) {
    TFilm *x = *(TFilm**) a;
    TFilm *y = *(TFilm**) b;
    return strcmp(x->nume, y->nume);
}

TFilm *adaugaFilm(TIMDB *c, char *nume) {
    if ( c->nrCrtFilme == 100 )
        return NULL;
    c->filme[c->nrCrtFilme].nume = nume;
    c->nrCrtFilme++;
    c->idxFilme[c->nrCrtFilme - 1] = &c->filme[c->nrCrtFilme - 1];
    qsort(c->idxFilme, c->nrCrtFilme, sizeof(TFilm*), cmp);
    return &c->filme[c->nrCrtFilme - 1];
}

TIMDB **dezaloc(TIMDB **x) {
    free((*x)->idxActori);
    free((*x)->idxFilme);
    free((*x)->filme);
    free((*x)->actori);
    free(*x);
    return NULL;
}