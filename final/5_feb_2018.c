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

typedef struct {
    char *nume;
    int *stoc;
} TFloare;

typedef struct {
    char *nume;
    TFloare *pref;
} TFriend;

typedef struct {
    int nrCrtFlori, nrMaxFlori;
    int nrCrtFriends, nrMaxFriends;
    TFloare *flori;
    int *stocuri;
    TFriend *friends;
} TColectie;

TColectie* alocaCol(int nrMaxFlori, int nrMaxFriends) {
    TColectie *col = calloc(1, sizeof(TColectie));
    col->flori = calloc(nrMaxFlori, sizeof(TFloare));
    col->friends = calloc(nrMaxFriends, sizeof(TFriend));
    col->nrMaxFlori = nrMaxFlori;
    col->nrCrtFriends = nrMaxFriends;
    col->stocuri = calloc(nrMaxFlori, sizeof(int));
    return col;
}

TFloare *adaugaFloare(TColectie *c, char *nume, int stoc) {
    if ( c->nrCrtFlori + 1 > c->nrMaxFlori ) {
        TFloare *aux = c->flori;
        aux = realloc(c->flori, sizeof(TFloare) * (c->nrMaxFlori + 1));
        if ( aux == NULL )
            return NULL;
        c->flori = aux;
        c->nrMaxFlori++;
    }
    c->nrCrtFlori++;
    strcpy(c->flori[c->nrCrtFlori].nume, nume);
    c->stocuri[c->nrCrtFlori] = stoc;
    c->flori[c->nrCrtFlori].stoc = &c->stocuri[c->nrCrtFlori];
    return &c->flori[c->nrCrtFlori]; 
}

int eliminaFriend(TColectie *c, char *nume) {
    for ( int i = 0 ; i < c->nrCrtFriends ; i++ ) {
        if ( strcmp(nume, c->friends[i].nume) == 0 ) {
            for ( int j = i ; j < c->nrCrtFriends ; j++ ) {
                c->friends[j] = c->friends[j + 1];
            }
            return 1;
        }

    }
    return 0;
}

typedef struct {
    TFloare *flori;
    int *count;
    int total;
} TBuchet;

TBuchet *creeazaBuchet(TColectie *c, TFriend *f, int nrFlori) {
    TBuchet *b = calloc(1, sizeof(TBuchet));
    if ( f->pref->stoc == 0 )
        return NULL;
    int cnt = 0;
    for ( int i = 0 ; i < c->nrCrtFlori ; i++ ) {
        cnt += c->stocuri[i];
    }
    if ( cnt < nrFlori )
        return NULL;
    b->flori = c->flori;
    b->count = calloc(c->nrCrtFlori, sizeof(int));
    int index_pref = 0;
    for ( int i = 0 ; i < c->nrCrtFlori ; i++ ) {
        if ( &c->flori[i] == f->pref )
            index_pref = i;
    }
    while ( b->total < nrFlori ) {
        if ( f->pref->stoc ) {
            b->total++;
            b->count[index_pref]++;
            f->pref->stoc--;
        }
    }
    for ( int i = 0 ; i < c->nrCrtFlori && b->total < nrFlori ; i++ ) {
        if ( c->stocuri[i] && b->total < nrFlori ) {
            c->stocuri[i]--;
            b->total++;
            b->count[i]++;
        }
    }
    return b;
} 