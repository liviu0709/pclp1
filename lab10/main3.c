#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("data2.in", "r");
    char *line = malloc(100 * sizeof(char));
    fgets(line, 100, fp);
    printf("%s\n", line);
    return 0;
}
