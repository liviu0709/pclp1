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

/*
Se da un fisier ce contine doua siruri de numere intregi, ambele sortate. 
Sa se creeze fisierul data.out ce contine valorile interclasate din cele doua siruri. 
Pe prima linie se afiseaza numarul de elemente ale sirului interclasat,
iar pe a doua linie se afiseaza sirul dupa interclasare.
*/

void ex1() {
    FILE *f = fopen("data.in", "r");
    int n, m;
    fscanf(f, "%d", &n);
    int *v1 = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        fscanf(f, "%d", &v1[i]);
    }
    fscanf(f, "%d", &m);
    int *v2 = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; ++i) {
        fscanf(f, "%d", &v2[i]);
    }
    fclose(f);
    FILE *g = fopen("data.out", "w");
    fprintf(g, "%d\n", n + m);
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (v1[i] < v2[j]) {
            fprintf(g, "%d ", v1[i]);
            i++;
        } else {
            fprintf(g, "%d ", v2[j]);
            j++;
        }
    }
    while (i < n) {
        fprintf(g, "%d ", v1[i]);
        i++;
    }
    while (j < m) {
        fprintf(g, "%d ", v2[j]);
        j++;
    }
    fprintf(g, "\n");
    fclose(g);
}

/*
Se da un fisier text si doua cuvinte cuv1 si cuv2.
Inlocuiti toate aparitiile cuvantului cuv1  cu cuvantul cuv2.
cuv1 si cuv2 pot contine doar caractere alfanumerice (fara spatii sau newline). 
Textul poate contine orice caracter valid si se poate extinde pe mai multe linii.
*/

void ex2() {
    FILE *f = fopen("data.in", "r");
    FILE *g = fopen("data.out", "w");
    char cuv1[100], cuv2[100];
    fscanf(f, "%s %s", cuv1, cuv2);
    char *line = malloc(1000 * sizeof(char));
    while ( fscanf(f, "%s", line) != EOF ) {
        if ( strcmp(line, cuv1) == 0 ) {
            fprintf(g, "%s ", cuv2);
        } else {
            if ( strcmp(line, cuv2) == 0 ) {
                fprintf(g, "%s ", cuv1);
            } else {
                fprintf(g, "%s ", line);
            }
        }
    }

}

/*
Sa se elimine dintr-un fisier toate spatiile, taburile, si liniile vide consecutive.
Rezultatul se va scrie intr-un nou fisier numit “data.out”.
Fisierul de intrare va ramane nemodificat.
*/

void ex3() {
    FILE *f = fopen("data.in", "r");
    FILE *g = fopen("data.out", "w");
    char *line = malloc(1000 * sizeof(char));
    while ( fgets(line, 1000, f) != NULL ) {
        for ( int i = 0 ; i < strlen(line) ; ++i ) {
            if ( line[i] == ' ' || line[i] == '\t' ) {
                for ( int j = i ; j < strlen(line) ; ++j ) {
                    line[j] = line[j + 1];
                }
                i--;
            }
        }
        line[strlen(line) - 1] = '\0';
        if ( strlen(line) > 0 ) {
            fprintf(g, "%s\n", line);
        }
    }
    fclose(f);
    fclose(g);
}

/*
Avem 2 fisiere text (data1.in si data2.in).
Se doreste adaugarea continutului celui de-al doilea fisier la sfarsitul primului (concatenarea fisierelor) si salvarea intr-un al treilea fisier (data.out).
Fisierele de intrare vor ramane nemodificate.
*/

void ex4() {
    FILE *f1 = fopen("data1.in", "r"), *f2 = fopen("data2.in", "r"), *g = fopen("data.out", "w");
    char *line = malloc(1000 * sizeof(char));
    while ( fgets(line, 1000, f1) != NULL ) {
        fprintf(g, "%s", line);
    }
    while ( fgets(line, 1000, f2) != NULL ) {
        fprintf(g, "%s", line);
    }
    fclose(f1);
    fclose(f2);
    fclose(g);
}

int main(void) {
    ex4();
}