#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *v = malloc(100000*sizeof(int));
    printf("%p\n", v);
    int *v2 = realloc(v, 800000*sizeof(int));
    printf("%p\n", v2);
    return 0;
}
