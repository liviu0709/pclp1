#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ex.h"

void ex1(char *s, char c) {
    char *p = s, *cp = calloc(256, sizeof(char));
    char *cp_p = cp; int counter = 0;
    while (*p != '\0') {
        int written = 0;
        if (*p == c) {
            written = sprintf(cp_p, "%d", ++counter);
        } else {
            written = sprintf(cp_p, "%c", *p);
        }
        p++; cp_p += written;
        if (cp_p > cp + 255) {
            break;
        }
    }
    strncpy(s, cp, 256); // assuming s is at least 256 bytes long
    return;
}

static int cmpstr(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}
void ex2(int n, char **s) {
    qsort(s, n, sizeof(char *), cmpstr);
}

void ex3() {
    int count = 0, i = 0;
    char *s = malloc(256);
    char **sentence = malloc(256 * sizeof(char *));
    for (int i = 0; i < 256; i++) {
        sentence[i] = malloc(256 * sizeof(char));
    }
    scanf ("%s", sentence[0]);
    for (i = 1; i < 256 && strchr(".,;!?", sentence[i - 1][strlen(sentence[i - 1]) - 1]) == NULL; i++) { // while the number of words is less than 256 and the last character of the previous word is not a punctuation mark
        scanf("%s", sentence[i]);
    }
    sentence[i - 1][strlen(sentence[i - 1]) - 1] = '\0'; // remove the punctuation mark
    scanf("%s", s);
    for (int j = 0; j < i; j++) {
        if (strcmp(sentence[j], s) == 0) {
            count++;
        }
    }
    printf("%d\n", count);
    free(s);
    for (int i = 0; i < 256; i++) {
        free(sentence[i]);
    }
    free(sentence);
}

static int matches_last_2_characters(const char* src, const char* target) {
    int src_len = strlen(src);
    int target_len = strlen(target);
    if (src_len < 2 || target_len < 2) {
        return 0;
    }
    return src[src_len - 1] == target[target_len - 1] && src[src_len - 2] == target[target_len - 2];
}

static int cmp_ex4(const void *a, const void *b) {
    char **a_p = (char **)a, **b_p = (char **)b;
    int a_len = strlen(*a_p), b_len = strlen(*b_p);
    if (a_len == b_len) {
        return strcmp(*a_p, *b_p);
    }
    return b_len - a_len;
}

void ex4() {
    char **sentence = malloc(256 * sizeof(char *));
    for (int i = 0; i < 256; i++) {
        sentence[i] = malloc(256 * sizeof(char));
    }
    scanf ("%s", sentence[0]);
    int i = 0;
    for (i = 1; i < 256 && strchr(".,;!?", sentence[i - 1][strlen(sentence[i - 1]) - 1]) == NULL; i++) { // while the number of words is less than 256 and the last character of the previous word is not a punctuation mark
        scanf("%s", sentence[i]);
    }
    sentence[i - 1][strlen(sentence[i - 1]) - 1] = '\0'; // remove the punctuation mark

    // let us use the following notation to substitute a dictionary:
    // char ***; each element is an array of words, where the first element is the string formed from the trailing characters
    char ***dict = malloc(256 * sizeof(char **));
    int dict_len = 0;
    for (int j = 0; j < i; j++) { // for each word in sentence
        // inefficient search but that is not the purpose here
        int found = 0;
        for (int k = 0; k < dict_len; k++) { // for each entry in dict, currently available (initially none)
            if (matches_last_2_characters(dict[k][0], sentence[j])) {
                found = 1; // found a suitable entry in dict, will place the word at the end of it if possible
                char **p;
                for (p = dict[k]; *p != NULL && p < dict[k] + 64; p++); 
                if (p == dict[k] + 64) {
                    printf("Error: dictionary word limit reached for %s termination\n", dict[k][0]);
                    continue;
                }
                *p = malloc(64 * sizeof(char));
                snprintf(*p, 64, "%s", sentence[j]);
                break;
            }
        }
        if (!found) {
            // no suitable entry found, will place the word in a newly created entry
            dict[dict_len] = malloc(64 * sizeof(char *));
            dict[dict_len][0] = malloc(64 * sizeof(char));
            snprintf(dict[dict_len][0], 64, "%s", sentence[j]);
            dict_len++;
        }
    }

    // for all entries in dict, sort themby word length, then lexicographically
    for (int j = 0; j < dict_len; j++) {
        int len = 0;
        for (char **p = dict[j]; *p != NULL && p < dict[j] + 64; p++) {
            len++;
        }
        qsort(dict[j], len, sizeof(char *), cmp_ex4);
    }

    // print dict, for debug
    for (int j = 0; j < dict_len; j++) {
        printf("%s", dict[j][0]);
        for (char **p = dict[j] + 1; *p != NULL && p < dict[j] + 64; p++) {
            printf(" %s", *p);
        }
        printf("\n");
    }

    // for each entry in dict, for the first two words (if any), see if their cumulative length is the greatest so far
    int max_len = 0;
    char *rw1, *rw2;
    for (int j = 0; j < dict_len; j++) {
        int len = 0;
        char *w1 = dict[j][0];
        char *w2 = dict[j][1]; // if null, treated later
        len = w2 == NULL ? strlen(w1) : strlen(w1) + strlen(w2);
        if (len > max_len) {
            max_len = len;
            rw1 = w1;
            rw2 = w2;
        } else if (len == max_len) {
            if (strcmp(w1, rw1) < 0) {
                rw1 = w1;
                rw2 = w2;
            }
        }
    }
    printf("%d\n", max_len);
    printf("%s\n", rw1); // rw1 is guaranteed to be non-null
    if (rw2 != NULL) {
        printf("%s\n", rw2);
    }
}

void ex5_bis(const char* str) {
    int len = strlen(str);
    char *l = str, *r = str + len - 1;
    int offset = 0;
    while (offset < len / 2) {
        if (*(l + offset) != *(r - offset))
            break;
        offset++;
    }

    char result[256];
    snprintf(result, offset + 1, "%s", str); // +1 to include the string terminator
    printf("%s\n", result);
    return;
}

static char* strrstr(const char* haystack, const char* needle) {
    int haystack_len = strlen(haystack);
    int needle_len = strlen(needle);
    if (needle_len > haystack_len) {
        return NULL;
    }
    for (int i = haystack_len - needle_len; i >= 0; i--) {
        if (strncmp(haystack + i, needle, needle_len) == 0) {
            return haystack + i;
        }
    }
    return NULL;
}

void ex5(const char* str) {
    char *aux = malloc(256 * sizeof(char));
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) { // can you guess why i used a reversed loop?
        snprintf(aux, i + 1, "%s", str);
        printf("%s\n", aux);
        if (strrstr(str, aux) > str) {
            printf("%s\n", aux);
            return;
        }
    }
}