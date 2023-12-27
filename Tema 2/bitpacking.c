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
    // Eliberam memoria
    free(dt);
}

int get_bit(unsigned int *v, int bit) {
    // Calculam pozitia bitului in vectorul de int-uri
    int poz = bit / 32;
    // Calculam pozitia bitului in interiorul int-ului
    int poz_bit = bit % 32;
    // Shiftam bitii la dreapta cu poz_bit pozitii
    unsigned int aux = v[poz] >> poz_bit;
    // Returnam bitul
    return aux & 1;
}

void task8() {
    int nr_date, nr_int, nr_int_control, nr_biti_date;
    scanf("%d", &nr_date);
    // Calculam numarul de int-uri necesare pentru date
    if ( nr_date % 32 == 0 ) {
        nr_int = nr_date * 15 / 32;
    } else {
        nr_int = nr_date * 15 / 32 + 1;
    }
    // Calculam numarul de int-uri necesare pentru bitii de control
    if ( nr_int % 32 == 0 ) {
        nr_int_control = nr_int / 32;
    } else {
        nr_int_control = nr_int / 32 + 1;
    }
    // Calculam nr de biti total de date
    nr_biti_date = nr_date * 15;
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
        for ( int j = 0 ; j < 32 ; j++ ) {
            if ( get_bit(v, i * 32 + j) == 1 )
                nr_biti_1++;
        }
        if ( nr_biti_1 % get_bit(v_control, i) == 1 )
            corupt_int[i] = 1;
    }
    // Stiind care sunt int-urile corupte, aflam datele corupte
    for ( int i = 0 ; i < nr_biti_date ; i++ ) {
        if ( corupt_int[i / 32] == 1 ) {
            corupt_date[i / 15] = 1;
        }
    }
    // Extragem toate datele
    TDate *dt = (TDate *)malloc(nr_date * sizeof(TDate));
    for ( int i = 0 ; i < nr_date ; i++ ) {
        int ziua = 0;
        for ( int j = 0 ; j < 5 ; j++ ) {
            if ( get_bit(v, i * 15 + j) == 1 )
                ziua += (1 << j);
        }
        dt[i].day = ziua;
        int luna = 0;
        for ( int j = 0 ; j < 4 ; j++ ) {
            if ( get_bit(v, i * 15 + 5 + j) == 1 )
                luna += (1 << j);
        }
        dt[i].month = luna;
        int an = 0;
        for ( int j = 0 ; j < 6 ; j++ ) {
            if ( get_bit(v, i * 15 + 9 + j) == 1 )
                an += (1 << j);
        }
        dt[i].year = 1970 + an;
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
    // Afisam datele
    for ( int i = 0 ; i < nr_date_corecte ; i++ ) {
        printf("%d.%d.%d\n", dt[i].day, dt[i].month, dt[i].year);
    }
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
