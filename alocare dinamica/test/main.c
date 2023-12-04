#include <stdio.h>
#include <stdlib.h>

int* f() {
    int x = 10;

    //for (int x=0; x<5; x++)
    //    printf("%d\n", x);

    int *p = &x;
    printf("Adresa este %p\n", p);

    return p;
}

int main()
{
    int x = 5;
    int v[100];
    int *p = v;
    const int *p2 = v;

    p = &x;
    p2 = &x;

    //*p = 6;
    //*p2 = 7;

    p = f();
    printf("Adresa este %p\n", p);
    printf("%d\n", *p);

    //printf("%p %p\n", p, p2);
    return 0;
}
