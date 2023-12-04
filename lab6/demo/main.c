#include "utils.h"

#include <stdio.h>

int main(void) {
    // demo_bitwise();
    // pointers_demo();
    int n = 0xdeadbeef;
    // n ^= 0xff;
    // n ^= 0x2300;
    // n ^= 0xdead0000;
    // uint8_t *s = binary_representation(&n, 4);

    // print_binary_rep(s, 4);

    // free(s);
    char *s = binary_representation(&n, 4);
    print_binary_rep(s, 4);
    free(s);
    s = malloc(sizeof(char) * 128);
    
    scanf("%[^\n]", s);
    printf("%s\n", s);
    free(s);
    return 0;
}