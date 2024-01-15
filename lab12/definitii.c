#include "structuri.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
TColectie *aloca_colectie(int nrMaxPers, int nrMaximTranzactii) {
    TColectie *c = (TColectie *) malloc(sizeof(TColectie));
    c->nrMaximPersoane = nrMaxPers;
    c->nrMaximTranzactii = nrMaximTranzactii;
    c->pers = malloc(nrMaxPers * sizeof(TPers));
    c->tranz = malloc(nrMaximTranzactii * sizeof(TTranzactie));
    c->tranzidx = calloc(nrMaximTranzactii, sizeof(TTranzactie *));
    for (int i = 0; i < 366; i++) {
        c->idxData[i] = calloc(nrMaximTranzactii, sizeof(TTranzactie *));
    }

    if (c->pers == NULL || c->tranz == NULL || c->tranzidx == NULL) {
        printf("Eroare alocare memorie\n");
        exit(1);
    }
    return c;
}

void completeaza_tridx(TColectie *c) {
    for (int i = 0; i < c->nrCrtTranzactii; i++) {
        c->tranzidx[i] = &c->tranz[i];
    }
}

static int cmp(const void *a, const void *b) {
    return (*((TTranzactie **) a))->timestamp - (*((TTranzactie **) b))->timestamp;
}

void sortareTranzactii(TColectie *c) {
    qsort(c->tranzidx, c->nrCrtTranzactii, sizeof(TTranzactie*), cmp);
}

void sortareTranzactii2(TColectie *c) {
    for (int i = 0; i < c->nrCrtTranzactii; i++) {
        for (int j = i + 1; j < c->nrCrtTranzactii; j++) {
            if (c->tranzidx[i]->timestamp > c->tranzidx[j]->timestamp) {
                TTranzactie *aux = c->tranzidx[i];
                c->tranzidx[i] = c->tranzidx[j];
                c->tranzidx[j] = aux;
            }
        }
    }
}

void completare_idxData(TColectie *c) {
    TTranzactie **iterator_tranzactie = c->tranzidx;
    for (int zi = 1; zi < 366; zi++) {
        while (iterator_tranzactie < c->tranzidx + c->nrCrtTranzactii && (*iterator_tranzactie)->timestamp < zi) {
            iterator_tranzactie++;
        }
        if (iterator_tranzactie < c->tranzidx + c->nrCrtTranzactii)
            c->idxData[zi] = iterator_tranzactie;
    }
}

int difera_iban(const char *iban1, const char *iban2) {
    return strncmp(iban1 + 4, iban2 + 4, 4) != 0;
    // return iban1[4] != iban2[4] || iban1[5] != iban2[5] || iban1[6] != iban2[6] || iban1[7] != iban2[7];
}

int macar_2_conturi(TPers *p) {
    // for (int i = 0; i < p->nrCrtConturi; i++) {
    //     for (int j = i + 1; j < p->nrCrtConturi; j++)
    //         if (difera_iban(p->conturi[i], p->conturi[j]))
    //             return 1;
    // }
    // return 0;

    char *iban1 = p->conturi[0];
    for (int i = 1; i < p->nrCrtConturi; i++) {
        if (difera_iban(iban1, p->conturi[i]))
            return 1;
    }
    return 0;
}

int apartine_iban(TPers *p, const char *iban) {
    // for (int i = 0; i < p->nrCrtConturi; i++) {
    //     if (strncmp(p->conturi[i], iban, MAX_IBAN) == 0)
    //         return 1;
    // }
    
    for (char **iterator_iban = p->conturi; iterator_iban < p->conturi + p->nrCrtConturi; iterator_iban++) {
        if (strncmp(*iterator_iban, iban, MAX_IBAN) == 0)
            return 1;
    }

    return 0;
}

double calc_suma(TColectie *c, const char *cnp, int zi) {
    TPers *p = c->pers;
    for (; p < c->pers + c->nrCrtPersoane; p++) {
        if (strncmp(p->CNP, cnp, MAX_CNP) == 0)
            break;
    }
    if (p == c->pers + c->nrCrtPersoane) {
        printf("Nu exista persoana cu CNP-ul %s\n", cnp);
        exit(1);
    }

    TTranzactie **inceput_zi = c->idxData[zi], **sfarsit_zi = NULL;
    if (zi == 365)
        sfarsit_zi = c->tranzidx + c->nrCrtTranzactii;
    else
        sfarsit_zi = c->idxData[zi + 1];

    double total = 0.0;
    for (TTranzactie **iterator_tranzactii = inceput_zi; iterator_tranzactii < sfarsit_zi && *iterator_tranzactii != NULL; iterator_tranzactii++) {
        char *dest = (*iterator_tranzactii)->dst;
        if (apartine_iban(p, dest)) {
            total += (*iterator_tranzactii)->suma;
        }
    }

    return total;
}

