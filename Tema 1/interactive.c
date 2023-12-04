#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

enum comenzi {
    iesire = 1, load = 2, save = 3, flip = 4, rotate = 5, crop_image = 6,
    extend_image = 7, paste_image = 8, create_filter = 9,
    apply_filter_image = 10, delete_filter = 11, delete_image = 12,
    nr_max_imag_loaded = 25,
    max_nr_chars = 100
};

struct imag_data {
    int N, M;
    int ***image;
};

struct filter {
    int size;
    float **value;
};

// Functie care returneaza indicele comenzii
int comanda_to_int(char *cmd) {
    if ( strcmp(cmd, "e" ) == 0 )
        return iesire;
    else if ( strcmp(cmd, "l" ) == 0 )
        return load;
    else if ( strcmp(cmd, "s" ) == 0 )
        return save;
    else if ( strcmp(cmd, "ah" ) == 0 )
        return flip;
    else if ( strcmp(cmd, "ar" ) == 0 )
        return rotate;
    else if ( strcmp(cmd, "ac" ) == 0 )
        return crop_image;
    else if ( strcmp(cmd, "ae" ) == 0 )
        return extend_image;
    else if ( strcmp(cmd, "ap" ) == 0 )
        return paste_image;
    else if ( strcmp(cmd, "cf" ) == 0 )
        return create_filter;
    else if ( strcmp(cmd, "af" ) == 0 )
        return apply_filter_image;
    else if ( strcmp(cmd, "df" ) == 0 )
        return delete_filter;
    else if ( strcmp(cmd, "di" ) == 0 )
        return delete_image;
    else
        return -1;
}

int main() {
    // Task 7
    static int exit, nr_imagini, index, x, y, w, h;
    static int nr_filtre, index_filtre, size, n, m;
    static int R, G, B, rows, cols, src;
    struct filter *filtre = calloc( nr_max_imag_loaded, sizeof(struct filter) );
    struct imag_data *imagini = calloc( nr_max_imag_loaded, sizeof(struct imag_data) );
    char cmd[max_nr_chars], path[max_nr_chars];
    while ( !exit ) {
        scanf("%s", cmd);
        int indice_comanda = 0;
        indice_comanda = comanda_to_int(cmd);

        switch ( indice_comanda ) {
            // Exit
            case iesire:
                exit = 1;
                break;
            // Load
            case load:
                scanf("%d %d", &n, &m);
                scanf("%s", path);
                imagini[nr_imagini].N = n;
                imagini[nr_imagini].M = m;
                imagini[nr_imagini].image = alocare(n, m);
                read_from_bmp(imagini[nr_imagini].image, imagini[nr_imagini].N, imagini[nr_imagini].M, path);
                nr_imagini++;
                break;
            // Save
            case save:
                scanf("%d", &index);
                scanf("%s", path);
                write_to_bmp(imagini[index].image, imagini[index].N, imagini[index].M, path);
                break;
            // Apply horizontal flip
            case flip:
                scanf("%d", &index);
                imagini[index].image = flip_horizontal(imagini[index].image, imagini[index].N, imagini[index].M);
                break;
            // Apply rotate
            case rotate:
                scanf("%d", &index);
                imagini[index].image = rotate_left(imagini[index].image, imagini[index].N, imagini[index].M);
                int aux = imagini[index].N;
                imagini[index].N = imagini[index].M;
                imagini[index].M = aux;
                break;
            // Apply crop
            case crop_image:
                scanf("%d", &index);
                scanf("%d %d %d %d", &x, &y, &w, &h);
                imagini[index].image = crop(imagini[index].image, imagini[index].N, imagini[index].M, x, y, h, w);
                imagini[index].N = h;
                imagini[index].M = w;
                break;
            // Apply extend
            case extend_image:
                scanf("%d", &index);
                scanf("%d %d %d %d %d", &rows, &cols, &R, &G, &B);
                imagini[index].image = extend(imagini[index].image, imagini[index].N,
                imagini[index].M, rows, cols, R, G, B);
                imagini[index].N = imagini[index].N + 2 * rows;
                imagini[index].M = imagini[index].M + 2 * cols;
                break;
            // Apply paste
            case paste_image:
                scanf("%d %d %d %d", &index, &src, &x, &y);
                imagini[index].image = paste(imagini[index].image, imagini[index].N,
                imagini[index].M, imagini[src].image, imagini[src].N, imagini[src].M, x, y);
                break;
            // Create filter
            case create_filter:
                scanf("%d", &size);
                filtre[nr_filtre].size = size;
                filtre[nr_filtre].value = (float**) malloc(size * sizeof(float*));
                for ( int  i = 0 ; i < size ; i++ ) {
                    filtre[nr_filtre].value[i] = (float*) malloc(size * sizeof(float));
                }
                for ( int i = 0 ; i < size ; i++ ) {
                    for ( int j = 0 ; j < size ; j++ ) {
                        scanf("%f", &filtre[nr_filtre].value[i][j]);
                    }
                }
                nr_filtre++;
                break;
            // Apply filter
            case apply_filter_image:
                scanf("%d %d", &index, &index_filtre);
                imagini[index].image = apply_filter(imagini[index].image,
                imagini[index].N, imagini[index].M, filtre[index_filtre].value, filtre[index_filtre].size);
                break;
            // Delete filter
            case delete_filter:
                scanf("%d", &index_filtre);
                for ( int i = 0 ; i < filtre[index_filtre].size ; i++ ) {
                    free(filtre[index_filtre].value[i]);
                }
                free(filtre[index_filtre].value);
                for ( int i = index_filtre ; i < nr_max_imag_loaded - 1 ; i++ )
                    filtre[i] = filtre[i + 1];
                nr_filtre--;
                break;
            // Delete image
            case delete_image:
                scanf("%d", &index);
                dezalocare(imagini[index].image, imagini[index].N, imagini[index].M);
                for ( int i = index ; i < nr_max_imag_loaded - 1 ; i++ )
                    imagini[i] = imagini[i + 1];
                nr_imagini--;
                break;
        }
    }
    // Dezalocam memoria pentru filtre
    for ( int i = 0 ; i < nr_max_imag_loaded ; i++ ) {
            for ( int j = 0 ; j < filtre[i].size ; j++ ) {
                free(filtre[i].value[j]);
            }
            free(filtre[i].value);
    }
    free(filtre);
    // Dezalocam memoria pentru imagini
    for ( int i = 0 ; i < nr_max_imag_loaded ; i++ ) {
            dezalocare(imagini[i].image, imagini[i].N, imagini[i].M);
    }
    free(imagini);
    return 0;
}
