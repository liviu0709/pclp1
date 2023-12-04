#include <stdio.h>
#include <stdlib.h>

int main()
{
    int capacitate, n;
    scanf("%d", &capacitate);
    scanf("%d", &n);

    int *v = (int*)malloc(capacitate * sizeof(int));
    // int *v = (int*)calloc(capacitate, sizeof(int));
    // calloc => initializeaza zona de memore alocata cu 0
    if (v == NULL) {
        printf("Memorie insuficienta!!\n");
        return 0;
    }

    // alocare reusita

    printf("%p\n", v);
    for (int i=0; i<n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i=0; i<n; i++) {
        printf("%d ", v[i]);
    }

    // alt cod
    free(v);
    v = &n;

    //printf("%p\n", p);

    return 0;
}
