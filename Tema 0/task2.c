#include <stdio.h>
#include <stdlib.h>

#define trick 7
#define treat 11

int main(void) {
    int num_elems = 0;

    scanf("%d", &num_elems);  //  Citirea lui N de la tastatura

    //  Se parcurg toate numerele de la 1 la N
    for ( int i = 1 ; i <= num_elems ; i++ ) {
        //  Se verifica daca numarul este divizibil cu 7 si 11
        if ( i % trick == 0 && i % treat == 0 ) {
            printf("TrickOrTreat ");
        } else {
            //  Se verifica daca numarul este divizibil cu 7
            if ( i % trick == 0 ) {
                printf("Trick ");
            } else {
                //  Se verifica daca numarul este divizibil cu 11
                if ( i % treat == 0 ) {
                    printf("Treat ");
                //  Daca niciunul din cazuri nu convine, se afiseaza valoarea sa
                } else {
                    printf("%d ", i);
                }
            }
        }
    }
}
