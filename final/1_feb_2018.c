#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int id;
    double x, y;
} TPunct2D;

typedef struct {
    char nume[101];
    unsigned int nrPuncte;
    TPunct2D *puncte;
    double (*functieArie)(TPunct2D*, int);
} TFigura2D;

TFigura2D *alocaFigura(unsigned int nrPuncte) {
    TFigura2D *x = calloc(1, sizeof(TFigura2D));
    x->puncte = calloc(nrPuncte, sizeof(TPunct2D));
    x->nrPuncte = nrPuncte;
    return x;
}

TFigura2D **alocaPlansa(unsigned int nrFiguri, unsigned int *nrPuncte) {
    TFigura2D **x = calloc(nrFiguri, sizeof(TFigura2D*));
    for ( int i = 0 ; i < nrFiguri ; i++ ) {
        x[i] = calloc(1, sizeof(TFigura2D));
        x[i]->nrPuncte = nrPuncte[i];
        x[i]->puncte = calloc(nrPuncte[i], sizeof(TPunct2D));
    }
    return x;
}

TFigura2D **read(FILE *in) {
    int nrfig;
    fscanf(in, "%d", &nrfig);
    unsigned int *nrpuncte = calloc(nrfig, sizeof(unsigned int));
    for ( int i = 0 ; i < nrfig ; i++ )
        fscanf(in, "%d", &nrpuncte[i]);
    TFigura2D **x = alocaPlansa(nrfig, nrpuncte);
    for ( int i = 0 ; i < nrfig ; i++ ) {
        fscanf(in, "%s", x[i]->nume);
        for ( int j = 0 ; j < x[i]->nrPuncte ; j++ ) {
            fscanf(in, "%d %lf %lf", &x[i]->puncte[j].id, &x[i]->puncte[j].x, &x[i]->puncte[j].y);
        }
    }
}

double funArieTriEchi(TPunct2D *puncte, int nrPuncte) {
    return 0;
}
double funAriePatrat(TPunct2D *puncte, int nrPuncte) {
    return 0;
}
double funArieFiguraComplexa(TPunct2D *puncte, int nrPuncte) {
    return 0;
}

void asociazaFunctieArie(TFigura2D **plansa, unsigned int nrFiguri) {
    for ( int i = 0 ; i < nrFiguri ; i++ ) {
        if ( plansa[i]->nrPuncte == 3 )
            plansa[i]->functieArie = funArieTriEchi;
        else {
            if( plansa[i]->nrPuncte == 4 )
                plansa[i]->functieArie = funAriePatrat;
            else
                plansa[i]->functieArie = funArieFiguraComplexa;
        }
    }
}

int comp(const void* a, const void* b) {
    TFigura2D *x = (TFigura2D*) a;
    TFigura2D *y = (TFigura2D*) b;
    double a1 = x->functieArie(x->puncte, x->nrPuncte);
    double a2 = y->functieArie(y->puncte, y->nrPuncte);
    return a1 - a2;
}

char *sorteazaFiguriArie(TFigura2D **plansa, unsigned int nrFiguri) {
    qsort(plansa, nrFiguri, sizeof(TFigura2D), comp);
    return 0;
}

void dezalocaPlansa(TFigura2D **plansa, unsigned int nrFiguri) {
    for ( int i = 0 ; i < nrFiguri ; i++ )
        free(plansa[i]->puncte);
    free(plansa);
}