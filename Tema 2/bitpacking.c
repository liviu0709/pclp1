#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"

// Definim o functie de sortare pt qsort
int compara(const void *a, const void *b) {
    TDate *x = (TDate *)a;
    TDate *y = (TDate *)b;
    if ( x->year != y->year )
        return x->year - y->year;
    if ( x->month != y->month )
        return x->month - y->month;
    return x->day - y->day;
}

void task7() {
    int n;
    scanf("%d", &n);
    TDate *dt = (TDate *)malloc(n * sizeof(TDate));
    for (int i = 0; i < n; i++)
    {
        // Citim datele pe rand
        unsigned int v;
        scanf("%u", &v);
        // Dupa shiftarea bitilor,
        // Punem data in vectorul de tip TDate
        int ziua = 0;
        // Ziua ocupa primii 5 biti, deci shiftam de 5 ori
        for( int j = 0 ; j < 5 ; j++ ) {
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
        for( int j = 0 ; j < 4 ; j++ ) {
            if ( v & 1 ) {
                luna += (1 << j);
            }
            v >>= 1;
        }
        dt[i].month = luna;
        int an = 0;
        // Se procedeaza la fel ca mai sus
        for( int j = 0 ; j < 6 ; j++ ) {
            if ( v & 1 ) {
                an += (1 << j);
            }
            v >>= 1;
        }
        dt[i].year = 1970 + an;
        printf("%02d.%02d.%04d\n", dt[i].day, dt[i].month, dt[i].year);
    }
    // Acum, vectorul trebuie sortat
    qsort(dt, n, sizeof(TDate), compara);
    // Pentru afisare avem nevoie de luni
    char *luni[12] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie",
		"iulie", "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    // Afisam datele sortate
    for ( int i = 0 ; i < n ; i++ ) {
        printf("%d %s %d\n", dt[i].day, luni[dt[i].month - 1], dt[i].year);
    }
}

void task8() {
    // TODO Task 8
}

int main()
{
    // TODO Task 7 & 8
	int nr_Task;
    scanf("%d", &nr_Task);
    switch (nr_Task)
    {
    case 7:
        task7();
        break;
    case 8:
        task8();
        break;
    }
    return 0;
}
