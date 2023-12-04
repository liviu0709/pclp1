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

//Sa se inverseze elementele unui vector utilizand o parcurgere cu 2 pointeri (unul de la inceput si unul de la final).
//void reverse(int *v1, int n); Ex: [1, 2, 3, 4, 5], n = 5 -> [5, 4, 3, 2, 1] 
void reverse(int *v1, int n) {
    int *p1 = v1, *p2 = v1 + n - 1;
    while (p1 < p2) {
        int aux = *p1;
        *p1 = *p2;
        *p2 = aux;
        p1++;
        p2--;
    }
}

void reverseChar(char *v1, int n) {
    char *p1 = v1, *p2 = v1 + n - 1;
    while (p1 < p2) {
        char aux = *p1;
        *p1 = *p2;
        *p2 = aux;
        p1++;
        p2--;
    }
}

/*
Remember binary search? Hai cu el din nou, dar de data asta cu pointeri.

Se da un vector sortat crescator cu N elemente (N citit de la tastatura) si un numar x. Sa se determine daca x se afla in vector.

int binary_search(int *v, int n, int x); Ex: [1, 2, 3, 4, 5], n = 5, x = 3 -> 1 (true) Ex: [1, 2, 3, 4, 5], n = 5, x = 6 -> 0 (false)

Nu se va permite accesul elementelor folosind operatorul [].
*/
int binary_search(int *v, int n, int x) {
    int *p1 = v, *p2 = v + n - 1;
    while (p1 <= p2) {
        int *mid = p1 + (p2 - p1) / 2;
        if (*mid == x) {
            return 1;
        }
        if (*mid < x) {
            p1 = mid + 1;
        } else {
            p2 = mid - 1;
        }
    }
    return 0;
}



/*
Se cunoaste faptul ca o adresa IP este pe 32 de biti. Dandu-se un intreg (pe 4 octeti) sa se afiseze ce adresa ip reprezinta si sa se afiseze adresa.

Ex: IP = 3229305093 192.123.73.5 (192 -> 1 << 24, 123 -> 1 << 16, 73 -> 1 << 8, 5 -> 1 << 0)
*/

char* nrToIp( unsigned int x ) {
    unsigned char *p = &x;
    char **c = malloc( 4 * sizeof(char*));
    for( int i = 0 ; i < 4 ; i++ ) {
        c[i] = malloc( 4 * sizeof(char));
    }
    char *sol = malloc( 20 * sizeof(char));
    for( int i = 0 ; i < 4 ; i++ ) {
        int x = *p;
        sprintf(c[i], "%d", x);
        strcat(sol, c[i]);
        //printf("%s", c[i]);
        if( i != 3 ) {
            strcat(sol, ".");
            //printf(".");
        }
        p++;
    }
    /*
    char numesmek[20], numesmek2[14], numesmek3[9], numesmek4[4];
    strcat(numesmek, c[3]);
    strcat(numesmek2, c[2]);
    strcat(numesmek3, c[1]);
    strcat(numesmek4, c[0]);
    return strcat(numesmek, strcat(".", strcat(numesmek2, strcat(".", strcat(numesmek3, strcat(".", numesmek4))))));
    */
    /*for( int i = 0 ; i < 4 ; i++ ) 
       printf("%s\n", c[i]);
    static char SOLUTIE[69];
    SOLUTIE[0] = c[3][0];
    SOLUTIE[1] = c[3][1];
    SOLUTIE[2] = c[3][2];*/
    //strcat(SOLUTIE, c[4]);
    /*strcat(SOLUTIE, ".");
    strcat(SOLUTIE, c[3]);
    strcat(SOLUTIE, ".");
    strcat(SOLUTIE, c[2]);
    strcat(SOLUTIE, ".");
    strcat(SOLUTIE, c[1]);*/
    //SOLUTIE[50] = '\0'; 
    //return SOLUTIE;
    
        
    
    int trei_zero = 3, cnt = 0 ;
    char *final_solutie = malloc( 20 * sizeof(char));
    for( int i = 0 ; i < strlen(c[1]) + strlen(c[2]) + strlen(c[3]) + strlen(c[0]) + 3; i++ ) {
        final_solutie[i] = c[trei_zero][cnt];
        cnt++;
        if( c[trei_zero][cnt] == '\0' ) {
            trei_zero--;
            cnt = 0;
            final_solutie[++i] = '.';
        }
    }
    final_solutie[strlen(final_solutie) - 1] = '\0';
    return final_solutie;
    return sol;
}

int sum(int a, int b) {
    return a + b;
}

/*'
Sa se implementeze functionala reduce: 
se primesc un vector de numere v si un numar de numere N, precum si o functie f de tipul int f(int, int). 
Sa se reduca vectorul la un singur numar, aplicand functia f pe cate N elemente consecutive.

Ex: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], N = 2, f = suma -> 55 (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10) Ex: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], N = 3, f = produs -> 3628800 (1 x 2 x 3 x 4 x 5 x 6 x 7 x 8 x 9 x 10)

Functia f poate fi scrisa de voi sau puteti folosi una din functiile din math.h (grija cu tipurile argumentelor in acest caz)
*/
int reduce(int *v, int n, int (*f)(int, int), int N ) {
    for( int i = 0; i < n - 1 ; i++ ) {
        
            v[i + 1] = f(v[i], v[i + 1]);
    }
    return v[n - 1];
}

/*
gigel alcoolistu m,n,dist m*n mat cu bautura != 0
*/
int gigel(int m, int n, int **p, int dist, int x, int y, int **visited) {
    if( dist < 0 )
        return 0;
    if( x < 0 || y < 0 )
        return 0;
    if( x >= m || y >= n )
        return 0;
    if(  visited[x][y] == 1 )
        return 0;
    int sol = 0;
    if( p[x][y] != 0) {
        //printf("%d %d\n", x, y);
        sol++;
    }
    visited[x][y] = 1;
    return sol + gigel(m, n, p, dist - 1, x + 1, y, visited) + gigel(m, n, p, dist - 1, x - 1, y, visited) + gigel(m, n, p, dist - 1, x, y + 1, visited) + gigel(m, n, p, dist - 1, x, y - 1, visited); 
}

int** alocMatrice( int n, int m ) {
    int **v = malloc( n * sizeof(int*));
    for( int i = 0 ; i < n ; i++ ) {
        v[i] = malloc( m * sizeof(int));
    }
    return v;
}

void free_v( int **v, int n ) {
    for( int i = 0 ; i < n ; i++ ) {
        free(v[i]);
    }
    free(v);
}

int main(void) {
    int n, m, dist;
    scanf("%d%d%d", &n, &m, &dist);
    int **v = alocMatrice(n, m), **gol = alocMatrice(n, m);
    for( int i = 0 ; i < n ; i++ ) {
        for( int j = 0 ; j < m ; j++ ) {
            scanf("%d", &v[i][j]);
        }
    }
    if( gigel(n, m, v, dist, 0, 0, gol) >= 3 )
        printf("DA");
    else
        printf("NU");
    if( 0 ) { //daca vreau sa vad matricea
        for( int i = 0 ; i < n ; i++, printf("\n") ) {
            for( int j = 0 ; j < m ; j++ ) {
                printf("%d ", v[i][j]);
            }
        }
    }
    int maxim = m;
    if( n > maxim )
        maxim = n;
    for( int i = 0 ; i < maxim ; i++) {
        free_v(gol, n);
        gol = alocMatrice(n, m);
        if( gigel(n, m, v, i, 0, 0, gol) > 0 ) {
            printf("\nDist minima: %d ", i);
            break;
        }
    }
    printf("\n");
    for( int i = 0 ; i < n ; i++ ) {
        free(v[i]);
        free(gol[i]);
    }
    free(v);
    free(gol);
    
}
 