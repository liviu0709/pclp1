#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

#define MAX 255
#define MIN 0

// Interschimbare pixeli
void interschimbare(int ***image, int i, int j, int k, int l) {
    int aux1 = image[i][j][0], aux2 = image[i][j][1], aux3 = image[i][j][2];
    image[i][j][0] = image[k][l][0];
    image[i][j][1] = image[k][l][1];
    image[i][j][2] = image[k][l][2];
    image[k][l][0] = aux1;
    image[k][l][1] = aux2;
    image[k][l][2] = aux3;
}

int*** alocare(int N, int M) {  // Alocare memorie pentru o noua imagine
    // Alocam o matrice
    int ***image = (int***) malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        image[i] = (int**) malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            image[i][j] = (int*) malloc(3 * sizeof(int));
        }
    }
    // Returnam imaginea alocata
    return image;
}

// Dezalocare memorie pentru o imagine
void dezalocare(int ***image, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {  // Dezalocam fiecare pixel
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
}

// Verificare daca un numar este in intervalul [0, 255]
int convert_to_rgb_num(int x) {
    if ( x < MIN )
        x = MIN;
    if ( x > MAX )
        x = MAX;
    return x;
}

// Functie ajutatoare pentru modificarea unui pixel
void modificare_pixel(int *pixel_dst, int *pixel_src) {
    // Modificam pixelul destinatie cu valorile din pixelul sursa
    pixel_dst[0] = pixel_src[0];
    pixel_dst[1] = pixel_src[1];
    pixel_dst[2] = pixel_src[2];
}

// Task 1
int ***flip_horizontal(int ***image, int N, int M) {
    for ( int i = 0 ; i < N ; i++ ) {  // Parcurgem liniile
        for ( int j = 0 ; j < M / 2 ; j++ ) {  // Inversam pixelii
            interschimbare(image, i, j, i, M - j - 1);
        }
    }
    // Returnam imaginea inversata
    return image;
}

// Task 2
int ***rotate_left(int ***image, int N, int M) {
    // Rotim imaginea la stanga, deci dimensiunile se schimba
    int ***image2 = alocare(M, N);

    for ( int i = 0 ; i < N ; i++ ) {
        for ( int j = 0 ; j < M  ; j++ ) {
            // Punem pixelii din imaginea primita
            // in cea rotita cu dimensiunile schimbate
            modificare_pixel(image2[j][N - i - 1], image[i][M - j - 1]);
        }
    }

    image2 = flip_horizontal(image2, M, N);
    // Dezalocam memoria pentru imaginea primita
    dezalocare(image, N, M);
    // Returnam imaginea rotita
    return image2;
}

// Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    // Alocam memorie pentru noua imagine
    int ***image2 = alocare(h, w);
    // Verificam daca putem procesa imaginea fara seg fault
    if ( x + w > M || y + h > N ) {
        printf("Nu se poate cropa imaginea\n");
        return NULL;
    }
    // Copiem pixelii ceruti din imaginea primita in cea noua
    for ( int i = y ; i < h + y ; i++ ) {
        for ( int j = x ; j < w + x ; j++ ) {
            modificare_pixel(image2[i - y][j - x], image[i][j]);
        }
    }
    // Dezalocam memoria pentru imaginea primita
    dezalocare(image, N, M);
    // Returnam imaginea ceruta
    return image2;
}

// Task 4
int ***extend(int ***image, int N, int M, int rows,
int cols, int new_R, int new_G, int new_B) {
    int ***image2 = alocare(N + 2 * rows, M + 2 * cols);
    // Copiem pixelii din imaginea primita in cea noua
    for ( int i = 0 ; i < N ; i++ ) {
        for ( int j = 0 ; j < M ; j++ ) {
            modificare_pixel(image2[i + rows][j + cols], image[i][j]);
        }
    }
    // Umplem marginile cu acelasi pixel
    for ( int i = 0 ; i < N + 2 * rows ; i++ ) {
        for ( int j = 0 ; j < M + 2 * cols ; j++ ) {
            if ( i < rows || i >= N + rows || j < cols || j >= M + cols ) {
                image2[i][j][0] = new_R;
                image2[i][j][1] = new_G;
                image2[i][j][2] = new_B;
            }
        }
    }

    // Dezalocam memoria pentru imaginea primita
    dezalocare(image, N, M);
    // Returnam imaginea ceruta
    return image2;
}

// Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst,
int *** image_src, int N_src, int M_src, int x, int y) {
    // Modificam pe rand fiecare pixel din imaginea dest
    // care trb sa fie suprascris si incarcam imaginea
    // sursa pana nu mai este loc
    for ( int i = 0 ; i + y < N_dst ; i++ ) {
        for ( int j = 0 ; j + x < M_dst ; j++ ) {
            // Daca am parcurs imaginea sursa
            // ne oprim
            if ( i >= N_src || j >= M_src ) {
                break;
            }
            modificare_pixel(image_dst[i + y][j + x], image_src[i][j]);
        }
    }
    // Returnam imaginea modificata
    return image_dst;
}

// Task 6
int ***apply_filter(int ***image, int N, int M,
float **filter, int filter_size) {
    int ***image2 = alocare(N, M);
    // Procesam toti pixelii imaginii
    for ( int i = 0 ; i < N ; i++ ) {
        for ( int j = 0 ; j < M ; j++ ) {
            // Aplicam filtrul pixelului de la pozitia i, j
            float R = 0, G = 0, B = 0;
            for ( int k = i - filter_size / 2, indice_filtru = 0 ; k <= i + filter_size / 2 ; k++, indice_filtru++ ) {
                for ( int l = j - filter_size / 2, indice_filtru2 = 0 ;
                 l <= j + filter_size / 2 ; l++, indice_filtru2++ ) {
                    // Daca suntem in afara imaginii
                    // nu facem nimic
                    if ( k >= 0 && k < N && l >= 0 && l < M ) {
                        R += (float) image[k][l][0] * filter[indice_filtru][indice_filtru2];
                        G += (float) image[k][l][1] * filter[indice_filtru][indice_filtru2];
                        B += (float) image[k][l][2] * filter[indice_filtru][indice_filtru2];
                    }
                }
            }
            // Salvam rezultatul in imaginea procesata
            image2[i][j][0] = convert_to_rgb_num((int) R);
            image2[i][j][1] = convert_to_rgb_num((int) G);
            image2[i][j][2] = convert_to_rgb_num((int) B);
        }
    }
    // Dezalocam memoria pentru imaginea primita
    dezalocare(image, N, M);
    // Returnam imaginea procesata
    return image2;
}
