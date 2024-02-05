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

char str1[50];

char* foo(char str[]) {
    static int i = 0;
    if (*str) {
        foo(str + 1);
        str1[i] = *str;
        i++;
    }
    return str1;
}

int main(){
    char str[] = "Examen Programare 2018";
    printf("%s\n", foo(str));
    return 0;
}