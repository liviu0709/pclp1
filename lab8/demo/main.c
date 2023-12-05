#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ex.h"

int main(void) {
    // char s[256] = "abcdedcbabcdebcda";
    // char c = 'c';

    // ex1(s, c);
    // printf("%s\n", s);


    // int n;
    // scanf("%d", &n);
    // char **s = malloc(n * sizeof(char *));

    // for (int i = 0; i < n; i++) {
    //     s[i] = malloc(100 * sizeof(char));
    //     scanf("%s", s[i]);
    // }

    // ex2(n, s);

    // for (int i = 0; i < n; i++) {
    //     printf("%s\n", s[i]);
    // }

    // ex3();
    // ex4();
    // ex5_bis("abc13248925cabc");
    ex5("abc13248925cabc");
}

// int test(void) {
//     char c = 'a';
//     char *s = "hellohellohellohellohello";
//     char *s2 = calloc(10, 1);

//     char s3[20] = "helloworld";

//     // strcat(s2, "hello");
//     int a = 16;

//     // fgets(s2, 10, stdin);
//     // scanf("%s", s2);
//     // printf("%s\n", s2);
//     // memset(s2, 0, 10);
//     snprintf(s2, 3, "world");
//     printf("%d\n", strchr(s3, 'o') - s3);
//     printf("%d\n", strstr(s3, s2) - s3);
//     // strcat(s2, "hello");
//     // strncat(s2, "hello", 3);
//     printf("%s\n", s2);
// }

