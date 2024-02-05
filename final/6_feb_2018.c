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
    char id;
    short val;
} TBec;

typedef struct {
    TBec **becuriCamera;
    int nrCrt;
} TCamera;

typedef struct {
    TCamera *camere;
    TBec *becuri;
    int nrMaxBec, nrMaxCam;
    int nrCrtCam, nrCrtBec;
    int nrMaxBecPerCamera;
} TComanda;

TComanda *alocaComanda(int nrMaxCam, int nrMaxBec, int nrMaxBecPerCamera) {
    TComanda *c = calloc(1, sizeof(TComanda));
    c->nrMaxCam = nrMaxCam;
    c->nrMaxBec = nrMaxBec;
    c->nrMaxBecPerCamera = nrMaxBecPerCamera;
    c->camere = calloc(nrMaxCam, sizeof(TCamera));
    c->becuri = calloc(nrMaxBec, sizeof(TBec));
    for ( int i = 0 ; i < nrMaxCam ; i++ ) {
        c->camere[i].becuriCamera = calloc(nrMaxBecPerCamera, sizeof(TBec*));
        for ( int j = 0 ; j < nrMaxBecPerCamera ; j++ )
            c->camere[i].becuriCamera[j] = &c->becuri[i * nrMaxBecPerCamera + j];
    }
    return c;
}

void adaugaBec(TComanda *c, char r, char g, char b, char i, TCamera *cam) {
    c->becuri[c->nrCrtBec].id = c->nrCrtBec;
    c->becuri[c->nrCrtBec].val = r + (g << 4) + (b << 8) + (i << 12);
    cam->nrCrt++;
    cam->becuriCamera[cam->nrCrt] = &c->becuri[c->nrCrtBec];
}

void eliminaBec(TComanda *c, int id) {
    for ( int i = 0 ; i < c->nrCrtBec ; i++ ) {
        if ( c->becuri[i].id == id ) {
            for ( int j = 0 ; j < c->nrCrtCam ; j++ ) {
                for ( int k = 0 ; k < c->camere[j].nrCrt ; k++ ) {
                    if ( c->camere[j].becuriCamera[k] == &c->becuri[i] ) {
                        for ( int p = k ; p < c->camere[j].nrCrt ; p++ )
                            c->camere[j].becuriCamera[p] = c->camere[j].becuriCamera[p + 1];
                        c->camere[j].nrCrt--;
                    }
                }
            }
            for ( int j = i ; j < c->nrCrtBec ; j++ ) {
                c->becuri[j] = c->becuri[j + 1];
            }
            c->nrCrtBec--;
        }
    }
}

int cmp(TBec *b1, TBec *b2) {
    int a = b1->val;
    int b = b2->val;
    a >= 12;
    b >= 12;
    if ( a > b )
        return -1;
    else {
        if ( a == b )
            return 0;
        else
            return 1;
    }
}

void updateCamera(TCamera *cam, TBec *etalon, int (*cmp)(TBec*, TBec*)) {
    for ( int i = 0 ; i < cam->nrCrt ; i++ ) {
        if ( cmp(cam->becuriCamera[i], etalon) == 0 ) {
            int cul = etalon->val;
            cam->becuriCamera[i]->val = cul; 
        }
    }
}

void eliberareComanda( TComanda **c ) {
    free((*c)->becuri);
    for ( int i = 0 ; i < (*c)->nrMaxCam ; i++ ) {
        free((*c)->camere[i].becuriCamera);
    }
    free((*c)->camere);
    free(c);
}