#include <stdio.h> //LAB 05
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "functiile_mele.h"
/*
Citiți un vector de întregi strict mai mari ca 0 de la tastatură. 
Vă veți opri din citit elemente ale vectorului într-una din situațiile următoare:

Ați citit deja N = 20 de elemente

Ați citit de la tastatură valoarea 0 sau o valoare negative (aceasta NU trebuie adăugată în vector)

Afișați la consolă, pe câte o linie nouă, indicele fiecărei valori impare din vector împreună cu valoarea propriu-zisă.
*/

void citire(int *n, int *v) {
    for ( int i = 0 ; i < *n ; i++ ) {
        scanf("%d", &v[i]);
        if( v[i] <= 0 ) {
            *n = i ; 
            break;
            }
    }
}

void afis( int n, int v[] ) {
    for( int i = 0 ; i < n ; i++ )
        printf("%d ", v[i]);
    printf("\n");
}

void ex1() {
    int v[21], n = 21;
    citire(&n , v);
    for( int i = 0 ; i < n ; i ++ ) {
        if( v[i] % 2 == 1 ) {
            printf("%d %d\n", i, v[i]);
        }
    }
}
/*
Pentru un vector citit similar cu citirea de la Execițiul 1, 
afișați doar acele elemente din vector pentru care elementul este mai mare decât indicele său 
(păstrați ordinea din vectorul inițial).
 Considerați că primul element din vector se află la indicele 0.
*/

void ex2() {
    int v[21], n = 21;
    citire(&n, v);
    for( int i = 0 ; i < n ; i++ )
        if( v[i] > i )
            printf("indice: %d valoare: %d\n", i, v[i]);
}

/*
Se dau n numere naturale. Stergeti elementul de la pozitia k in vectorul dat. Se va afisa vectorul rezultat.
*/
void ex3() {
    int n, k;
    scanf( "%d%d", &n, &k);
    int *v = malloc( n * sizeof(int));
    for( int i = 0 ; i < n ; i++ ) {
        scanf( "%d", &v[i]);
    }
    for( int i = 0 ; i < n ; i++ ) {
        if( i >= k )
            v[i] = v[i + 1];
    }
    n--;
    afis( n, v);

}

/*
Aplicati o functie pe fiecare element al unui vector dat. (elementele sunt numere intregi, la fel si rezultatele).

Functia va fi data ca si un numar de la 0 la 4:

0 - incrementare

1 - inmultire cu 2

2 - impartire la 2

3 - ridicare la patrat

4 - radical

Ex: n = 5, v = [1, 2, 3, 4, 5] si k=2 se va afisa [2, 4, 6, 8, 10].
*/

void ex4() {
    int n, k;
    scanf("%d%d", &n, &k);
    int *v = malloc( n * sizeof(int) );
    for( int i = 0 ; i < n ; i++ ) {
        scanf( "%d", &v[i] );
    }
    for( int i = 0 ; i < n ; i++ ) {
        switch( k ) {
            case 0:
                v[i]++;
                break;
            
            case 1:
                v[i] *= 2;
                break;

            case 2:
                v[i] /= 2;
                break;
            case 3:
                v[i] *= v[i];
                break;
            case 4:
                v[i] = sqrt( v[i] );
                break;
        }
    }
    afis( n , v);
}

void citireMatrice(int *n, int *m, int v[][100]) {
    scanf( "%d%d", n, m);
    for( int i = 0 ; i < *n ; i++ ) {
        for( int j = 0 ; j < *m ; j++ ) {
            scanf( "%d", &v[i][j] );
        }
    }
}

void afisMatrice(int n, int m, int v[][100]) {
    for( int i = 0 ; i < n ; i++ ) { 
        for( int j = 0 ; j < m ; j++ )
            printf("%d ", v[i][j]);
        printf("\n");}
}

/*'
Se citeste o matrice cu N linii si M coloane. 
Pentru liniile pare sa se afize minimul, iar pentru cele impare sa se afiseze maximul. 
Fiecare minim/maxim va fi printat pe o linie separata in formatul 
“nr_linie: min = x” pentru linii pare, “nr_linie: max = y” pentru linii impare, 
iar index-ul nr_linie va incepe de la 1, reprezentarea tabloului incepand de la 0.
*/

void MatriceEx1() {
    int n, m, v[100][100];
    citireMatrice( &n, &m, v);
    for( int i = 0 ; i < n ; i++ ) {
        int min = v[i][0], max = v[i][0];
        for( int j = 0 ; j < m ; j++ ) {
            if( min > v[i][j] )
                min = v[i][j];
            if( max < v[i][j] )
                max = v[i][j];
        }
        if( i % 2 == 0 )
            printf("%d: min = %d\n", i + 1, min);
        else
            printf("%d: max = %d\n", i + 1, max);
    }
}

/*
Se citeste o matrice cu N linii si M coloane. Urmeaza Q query-uri de forma: x1 y1 x2 y2. 
Sa se afiseze suma elementelor dintre cele 2 pozitii.
*/

void MatriceEx2() {
    int n, m, v[100][100], q, x1, x2, y2, y1;
    citireMatrice(&n, &m, v);
    scanf("%d", &q);
    for( int i = 0 ; i < q ; i++ ) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int s = 0;
        for( int k = x1 ; k <= x2 ; k++ ) {
            for( int l = y1 ; l <= y2 ; l++ )
                s += v[k][l];
        }
        printf("%d\n", s);
    }
}

/*
Inmultirea a doua matrice: 
se dau doua matrice de dimensiuni A, B respectiv B, C, sa se afiseze rezultatul inmultirii lor, 
o matrice de dimensiuni A, C.
1 2 3    1 2 3 4    a11*b11+a12*b21+a13*b31
4 5 6    5 6 7 8
         9 8 7 6
*/

void MatriceEx3() {
    int a, b, c;
    int A[100][100], B[100][100], C[100][100];
    citireMatrice(&a, &b, A);
    citireMatrice(&b, &c, B);
    for( int i = 0 ; i < a ; i++ ) {
        for( int j = 0 ; j < c ; j++ ) {
            for( int k = 0 ; k < max(2, a, c) ; k++ )
                C[i][j] += A[i][k] * B[k][j];
        }
    }
    afisMatrice(a, c, C);
}



int main(void) {
    MatriceEx3();
}
