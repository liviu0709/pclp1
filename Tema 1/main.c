#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#include "bmp.h"

// Aceasta e un fisier exemplu pentru a vedea
// cum folositi functiile read_from_bmp si write_to_bmp

// puteti folosi acest fisier si pentru testarea manuala
// a functiilor pe care le implementati in imageprocessing.c

int main()
{
	// alocam o matrice
	int N = 789, M=1024;
	int ***m = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        m[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            m[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

    read_from_bmp(m, N, M, "./4964064451_25410b9741_b.bmp");

	// mica procesare pe imagine ca exemplu
	
	// adaugam o banda orizontala rosie
    for (int i=20; i<40; i++) {
        for (int j=0; j<M; j++) {
            m[i][j][0] = 255;
        }
    }

	// adaugam o banda verticala verde
    for (int j=100; j<200; j++) {
        for (int i=0; i<N; i++) {
            m[i][j][1] = 255;
        }
    }

    //test flip
    //m = flip_horizontal(m, N, M);

    //test rotate
    /*m = rotate_left(m, N, M);
    int aux = N;
    N = M;
    M = aux;*/

    //test crop
    /*m = crop(m, N, M, 100, 100, 600, 900);
    N = 600;
    M = 900;*/

    //test extend
    /*m = extend(m, N, M, 100, 100, 255, 255, 255);
    N = 100 + N + 100;
    M = 100 + M + 100;*/

    //test paste
    /*int ***m2 = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        m2[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            m2[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    read_from_bmp(m2, N, M, "./4964064451_25410b9741_b.bmp");
    m = paste(m, N, M, m2, N, M, 300, 300);
    //free m2
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) { // Dezalocam fiecare pixel
            free(m2[i][j]);
        }
        free(m2[i]);
    }
    free(m2);*/

    //test filter
    float **filter = (float **)malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++) {
        filter[i] = (float *)malloc(3 * sizeof(float));
    }
    for (int i = 0; i < 3; i++) {
        for (int j=0; j<3; j++) {
            filter[i][j] = 0.5 / 9.0;
        }
    }
    //m = apply_filter(m, N, M, filter, 3);

	// salvam imaginea sub numele output.bmp
    write_to_bmp(m, N, M, "./output.bmp");

	// free matrice
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(m[i][j]);
        }
		free(m[i]);
    }
	free(m);

    printf("Done\n");
    return 0;
}
