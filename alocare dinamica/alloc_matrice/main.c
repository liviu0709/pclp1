#include <stdio.h>
#include <stdlib.h>

int** aloca_matrice(int N, int M) {
    int **m = (int**)malloc(N*sizeof(int*));
    if (m == NULL) {
        printf("Eroare la alocarea m\n");
        return NULL;
    }

    for (int i=0; i<N; i++) {
        m[i] = (int*)malloc(M*sizeof(int));
        if (m[i] == NULL) {
            printf("Eroare la alocarea randului %d\n", i);
            for (int j=0; j<i; j++) {
                free(m[j]);
            }
            free(m);
            m = NULL;
            return NULL;
        }
    }
    return m;
}


int main()
{
    //int m[N][M];

    /*
    int *v = malloc(600 * sizeof(int));

    // linia i, coloana j i=2, j=4
    int i=2;
    int j=4;
    v[i*M+j];

    v[i][j];
    */

    int N, M;
    scanf("%d%d", &N, &M);

    /*
    int **m = (int**)malloc(N*sizeof(int*));
    if (m == NULL) {
        printf("Eroare la alocarea m\n");
        return 1;
    }

    for (int i=0; i<N; i++) {
        m[i] = (int*)malloc(M*sizeof(int));
        if (m[i] == NULL) {
            printf("Eroare la alocarea randului %d\n", i);
            for (int j=0; j<i; j++) {
                free(m[j]);
            }
            free(m);
            m = NULL;
            break;
        }
    }

    if (m == NULL) {
        return 1;
    }*/

    int **m = aloca_matrice(N,M);
    if (m == NULL) {
        printf("Eroare\n");
        return 1;
    }

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            scanf("%d", &m[i][j]);
            //printf("AM CITIT: %d ", m[i][j]);
            
        }
        //printf("\n");
    }

    int k ,p;
    scanf("%d%d", &k, &p);

    m = realloc(m, (N+k)*sizeof(int*));
    if (m == NULL) {
        printf("Eroare la realocare\n");
        return 1;
    }
    for( int  i = 0 ; i < M + p ; i++ ) {
        m[i] = realloc(m[i], (M+p)*sizeof(int));
        if (m[i] == NULL) {
            printf("Eroare la realocare\n");
            return 1;
        }

    }

    for( int i = 0 ; i < N + k ; i++ ) {
        for( int j = 0 ; j < M + p ; j++) {
            if( i >= N || j >= M ) {
                scanf( "%d", &m[i][j]);
            }
        }
    }


    N = N+k;
    M = M+p;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    //*m = NULL; // -------

    for (int i=0; i<N; i++) {
        free(m[i]);
    }
    free(m);
    m = NULL;

    //*m = NULL; // -------

    return 0;
}
