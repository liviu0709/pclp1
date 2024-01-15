#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"

enum { an_inceput = 1970, cinci = 5, sase = 6, doisprezece = 12, treizeci_doi = 32, cinspe = 15 };

// Definim o functie de sortare pt qsort
int compara(const void *a, const void *b) {
    TDate *x = (TDate *)a;
    TDate *y = (TDate *)b;
    if ( x->year != y->year )
        return (int) x->year - (int) y->year;
    if ( x->month != y->month )
        return (int) x->month - (int) y->month;
    return (int) x->day - (int) y->day;
}

void task7() {
    static int n;
    scanf("%d", &n);
    TDate *dt = (TDate *)malloc(n * sizeof(TDate));
    for (int i = 0; i < n; i++) {
        // Citim datele pe rand
        static unsigned int v;
        scanf("%u", &v);
        // Dupa shiftarea bitilor,
        // Punem data in vectorul de tip TDate
        unsigned int ziua = 0;
        // Ziua ocupa primii 5 biti, deci shiftam de 5 ori
        for ( int j = 0 ; j < cinci ; j++ ) {
            // Daca bitul curent este 1, adaugam 2^j la ziua curenta
            if ( v & 1 ) {
                ziua += (1 << j);
            }
            // Shiftam bitii la dreapta cu o pozitie
            v >>= 1;
        }
        // Punem ziua in vectorul de tip TDate
        dt[i].day = ziua;
        int luna = 0;
        // Luna ocupa urmatorii 4 biti, deci shiftam de 4 ori
        // si procedam la fel ca mai sus
        for ( int j = 0 ; j < 4 ; j++ ) {
            if ( v & 1 ) {
                luna += (1 << j);
            }
            v >>= 1;
        }
        dt[i].month = luna;
        int an = 0;
        // Se procedeaza la fel ca mai sus
        for ( int j = 0 ; j < sase ; j++ ) {
            if ( v & 1 ) {
                an += (1 << j);
            }
            v >>= 1;
        }
        dt[i].year = an_inceput + an;
        // printf("%02d.%02d.%04d\n", dt[i].day, dt[i].month, dt[i].year);
    }
    // Acum, vectorul trebuie sortat
    qsort(dt, n, sizeof(TDate), compara);
    // Pentru afisare avem nevoie de luni
    char *luni[doisprezece] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
        "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    // Afisam datele sortate
    for ( int i = 0 ; i < n ; i++ ) {
        printf("%d %s %d\n", dt[i].day, luni[dt[i].month - 1], dt[i].year);
    }
    // Eliberam memoria
    free(dt);
}

int get_bit(unsigned int *v, int bit) {
    // Calculam pozitia bitului in vectorul de int-uri
    int poz = bit / treizeci_doi;
    // Calculam pozitia bitului in interiorul int-ului
    int poz_bit = bit % treizeci_doi;
    // Shiftam bitii la dreapta cu poz_bit pozitii
    unsigned int aux = v[poz] >> poz_bit;
    // Returnam bitul
    return (int) aux & 1;
}

void task8() {
    static int nr_date, nr_int, nr_int_control, nr_biti_date;
    scanf("%d", &nr_date);
    // Calculam numarul de int-uri necesare pentru date
    if ( nr_date % treizeci_doi == 0 ) {
        nr_int = nr_date * cinspe / treizeci_doi;
    } else {
        nr_int = nr_date * cinspe / treizeci_doi + 1;
    }
    // Calculam numarul de int-uri necesare pentru bitii de control
    if ( nr_int % treizeci_doi == 0 ) {
        nr_int_control = nr_int / treizeci_doi;
    } else {
        nr_int_control = nr_int / treizeci_doi + 1;
    }
    // Calculam nr de biti total de date
    nr_biti_date = nr_date * cinspe;
    unsigned int *v = (unsigned int *)malloc(nr_int * sizeof(unsigned int));
    // Citim int urile cu date
    for ( int i = 0 ; i < nr_int ; i++ ) {
        scanf("%u", &v[i]);
    }
    unsigned int *v_control = (unsigned int *)malloc(nr_int_control * sizeof(unsigned int));
    // Citim int urile de control
    for ( int i = 0 ; i < nr_int_control ; i++ )
        scanf("%u", &v_control[i]);
    int *corupt_date = calloc(nr_date, sizeof(int));
    int *corupt_int = calloc(nr_int, sizeof(int));
    // Verificam fiecare bit de control
    for ( int i = 0 ; i < nr_int ; i++ ) {
        int nr_biti_1 = 0;
        for ( int j = 0 ; j < treizeci_doi ; j++ ) {
            if ( get_bit(v, i * treizeci_doi + j) == 1 )
                nr_biti_1++;
        }
        if ( nr_biti_1 % 2 != get_bit(v_control, i) )
            corupt_int[i] = 1;
    }
    // Stiind care sunt int-urile corupte, aflam datele corupte
    for ( int i = 0 ; i < nr_biti_date ; i++ ) {
        if ( corupt_int[i / treizeci_doi] == 1 ) {
            corupt_date[i / cinspe] = 1;
        }
    }
    // Extragem toate datele
    TDate *dt = (TDate *)malloc(nr_date * sizeof(TDate));
    for ( int i = 0 ; i < nr_date ; i++ ) {
        int ziua = 0;
        for ( int j = 0 ; j < cinci ; j++ ) {
            if ( get_bit(v, i * cinspe + j) == 1 )
                ziua += (1 << j);
        }
        dt[i].day = ziua;
        int luna = 0;
        for ( int j = 0 ; j < 4 ; j++ ) {
            if ( get_bit(v, i * cinspe + cinci + j) == 1 )
                luna += (1 << j);
        }
        dt[i].month = luna;
        int an = 0;
        for ( int j = 0 ; j < sase ; j++ ) {
            if ( get_bit(v, i * cinspe + 4 + 4 + 1 + j) == 1 )
                an += (1 << j);
        }
        dt[i].year = an_inceput + an;
    }
    // Stergem datele corupte din dt
    int nr_date_corecte = 0;
    for ( int i = 0 ; i < nr_date ; i++ ) {
        if ( corupt_date[i] == 0 ) {
            dt[nr_date_corecte] = dt[i];
            nr_date_corecte++;
        }
    }
    // Sortam datele
    qsort(dt, nr_date_corecte, sizeof(TDate), compara);
    // Pentru afisare avem nevoie de luni
    char *luni[doisprezece] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
    "iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    // Afisam datele
    for ( int i = 0 ; i < nr_date_corecte ; i++ ) {
        printf("%d %s %d\n", dt[i].day, luni[dt[i].month - 1], dt[i].year);
    }
    // Eliberam memoria
    free(v);
    free(v_control);
    free(corupt_date);
    free(corupt_int);
    free(dt);
}

int main() {
    // Task 7 & 8
    static int nr_Task;
    scanf("%d", &nr_Task);
    switch (nr_Task) {
    case sase + 1:
        task7();
        break;
    case sase + 2:
        task8();
        break;
    }
    return 0;
}
