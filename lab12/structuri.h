#pragma once

#define MAX_IBAN 25
#define MAX_CNP 14

typedef struct {
    char *nume;
    char CNP[14];
    char conturi[50][25];
    int nrCrtConturi;
} TPers;

typedef struct {
    char src[25];
    char dst[25];
    int timestamp;
    double suma;
} TTranzactie;

typedef struct {
    int nrCrtTranzactii, nrMaximTranzactii;
    int nrCrtPersoane, nrMaximPersoane;
    TPers *pers;
    TTranzactie *tranz;
    TTranzactie **tranzidx;
    TTranzactie **idxData[366];
} TColectie;

TColectie* aloca_colectie(int nrMaximPersoane, int nrMaximTranzactii);

