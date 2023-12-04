#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    int *v = NULL;

    while (1) {
        int x;
        scanf("%d", &x);

        if (x==0) {
            break;
        }

        // cu malloc + free
        /*
        int *v_aux = (int*) malloc((n+1) * sizeof(int));
        for (int i=0; i<n; i++) {
            v_aux[i] = v[i];
        }
        if (v != NULL) {
            free(v);
        }
        v = v_aux;
        */

        // realloc
        // 0x000006FC80
        int *v_aux = (int*) realloc(v, (n+1) * sizeof(int));
        if (v_aux == NULL) {
            printf("Problema\n");
            break;
        }
        // v_aux = 0x00000089ABC;
        // v = 0x00006FC80
        v = v_aux;

        v[n] = x;
        n++;
    }

    for (int i=0; i<n; i++) {
        printf("%d ", v[i]);
    }

    return 0;
}
