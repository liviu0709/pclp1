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

enum { a,b,c,d,e,f };

struct foo {
unsigned char ch : 3;
unsigned int myint :4;
};
int main(void) {
    printf("A: %d\nB: %d\n", a, b);
    struct foo f;
    f.ch = b ^ c ;
    printf("%d\n", f.ch);
    f.ch = (1<<f.ch) - f.ch;
    f.myint = ~f.ch;
    printf("%d\n", f.ch);
    printf("%d\n", f.myint);
    return 0;
}