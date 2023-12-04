#include "utils.h"

#include <stdio.h>

// & - and 0011 & 0100 = 0000
// | - or 0100 | 0011 = 0111, 0100 | 1100 = 1100
// ^ - xor 0100 ^ 0011 = 0111, 0100 ^ 1100 = 1000, a ^ a = 0
// ~ - negare ~0100 = 1011 
// << - shift left 00010010 << 1 -> 00100100, 00010010 << 3 -> 10010000
// >> - shift right 00010010 >> 1 -> 00001001


void demo_bitwise() {
    int n = 0x00a00255;
    int m = n & 0x00000fa0;
    // printf("%d\n", 5 & 11); // 0101 & 1011
    // printf("%x\n", m);

    // m = n | 0x00000022;
    // printf("%x\n", m);

    // m = n ^ 0x00000011; // 55 = 01010101 ^ 11 = 00010001 = 01000100 == 44
    //                     // 01010101 ^ 00100010 = 01110111 = 77
    // printf("%x\n", m);

    // m = ~n;
    // printf("%x\n", m);
    char *s = binary_representation(&n, 4);
    // printf("%s\n", s);
    // s = binary_representation(&m, 4);
    // printf("%s\n", s);

    m = 0x00000007;
    s = binary_representation(&m, 4);
    print_binary_rep(s, 4);
    m = m << 1;
    s = binary_representation(&m, 4);
    print_binary_rep(s, 4);

    m = m >> 3;
    s = binary_representation(&m, 4);
    print_binary_rep(s, 4);
    // m = n ^ 0x00000066;
    // printf("%x\n", m);

    // printf("%d\n", 7 ^ 25);
}
char* binary_representation(void *p, int n) {
    char *s = calloc(n * 8 + 1, sizeof(uint8_t));
    s[n * 8] = '\0';
    for (int i = 0; i < n; i++) {
        char b = *((char*)p + i);
        for (int j = 0; j < 8; j++) {
            s[i * 8 + j] = (b & 0x80) ? '1' : '0';
            b <<= 1;
        }
    }
    return s;
}

void print_binary_rep(void *p, int n) {
    int i = 0; char *ps = p;
    while (*ps != 0) {
        if (i++ % 8 == 0)
            printf(BLUE_SPEC, *ps);
        else
            printf("%c", *ps);
        ps++;
    }
    printf("\n");
}

void pointers_demo() {
    // int *n = malloc(sizeof(int));
    // *n = 5;
    // int **mn = &n;
    // printf("%p\n", &n);
    // printf("%p\n", mn);
    char *s = calloc(128, sizeof(char));

    scanf("%s", s);
    printf("%s\n", s);

    free(s);
}

int str_length(char *s) {
    int i = 0;
    while (*s != '\0') {
        i++;
        s++;
    }
    return i;
}

char * strdel(char *s, int pos, int n) {
    for (int i = pos; i < str_length(s) - n; i++) {
        s[i] = s[i + n];
    }
    return s;
}

char *strins(char *s, int pos, char *s2) {
    for (int i = str_length(s) - 1; i >= pos; i--) {
        s[i + str_length(s2)] = s[i];
    }
    for (int i = 0; i < str_length(s2); i++) {
        s[pos + i] = s2[i];
    }
    return s;
}


