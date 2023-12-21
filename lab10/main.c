#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ex1() {
	FILE *fp = fopen("data.in", "r");
	int N, M;
	int *v1, *v2;
	v1 = malloc(100 * sizeof(int));
	v2 = malloc(100 * sizeof(int));
	fscanf(fp, "%d", &N);
	for (int i = 0; i < N; ++i) {
		fscanf(fp, "%d", &v1[i]);
	}

	fscanf(fp, "%d", &M);
	for (int i = 0; i < M; ++i) {
		fscanf(fp, "%d", &v2[i]);
	}

	fclose(fp);
	FILE *fp2 = fopen("data.out", "w");
	int i = 0, j = 0;
	fprintf(fp2, "%d\n", N + M);

	while (i < N && j < M) {
		if (v1[i] < v2[j]) {
			fprintf(fp2, "%d ", v1[i]);
			++i;
		} else {
			fprintf(fp2, "%d ", v2[j]);
			++j;
		}
	}

	while (i < N) {
		fprintf(fp2, "%d ", v1[i]);
		++i;
	}

	while (j < M) {
		fprintf(fp2, "%d ", v2[j]);
		++j;
	}

	fclose(fp2);
}

char *get_word_pointer(char *line, const char *w1, const char *w2) {
	char *iter = line;
	while (*iter != '\0') {
		if (strncmp(iter, w1, strlen(w1)) == 0) {
			return iter;
		}
		if (strncmp(iter, w2, strlen(w2)) == 0) {
			return iter;
		}
		++iter;
	}
	return NULL;
}

void ex2() {
	FILE *fp = fopen("data2.in", "r");
	FILE *fp2 = fopen("data2.out", "w");
	char *cuv1, *cuv2;
	cuv1 = malloc(100 * sizeof(char));
	cuv2 = malloc(100 * sizeof(char));

	fscanf(fp, "%s", cuv1);
	fscanf(fp, "%s", cuv2);

	char *line = malloc(1000 * sizeof(char));
	char *aux = malloc(1000 * sizeof(char));

	while (fscanf(fp, "%s", aux) == 1) {
		memset(line, 0, 1000);
		if (strncmp(aux, cuv1, strlen(cuv1)) == 0) {
			strncat(line, cuv2, strlen(cuv2));
			strncat(line, " ", 1);
		} else if (strncmp(aux, cuv2, strlen(cuv2)) == 0) {
			strncat(line, cuv1, strlen(cuv1));
			strncat(line, " ", 1);
		} else {
			strncat(line, aux, strlen(aux));
			strncat(line, " ", 1);
		}
		fputs(line, fp2);
	}

	fclose(fp);
	return;

	line = fgets(line, 1000, fp);
	while (line != NULL) {
		printf("%s\n", line);
		memset(aux, 0, 1000);
		char *word = get_word_pointer(line, cuv1, cuv2);
		while (word != NULL) {
			strncat(aux, line, word - line);
			if (strncmp(word, cuv1, strlen(cuv1)) == 0) {
				strncat(aux, cuv2, strlen(cuv2));
				word += strlen(cuv1);
			} else {
				strncat(aux, cuv1, strlen(cuv1));
				word += strlen(cuv2);
			}
			word = get_word_pointer(word, cuv1, cuv2);
		}
		fputs(aux, fp2);
		line = fgets(line, 1000, fp);
	}
}

void ex3() {
	FILE *fp = fopen("data3.in", "r");
	FILE *fp2 = fopen("data3.out", "w");

	char *line = malloc(1000 * sizeof(char));

	line = fgets(line, 1000, fp);
	char *aux = calloc(1000, sizeof(char));
	while (line != NULL) {
		char *chr = line;
		while (chr < line + strlen(line)) {
			if (*chr == ' ' || *chr == '\t' || *chr == '\n') {
				++chr;
				continue;
			}
			aux[strlen(aux)] = *chr;
			++chr;
		}
		if (strlen(aux) > 0) {
			aux[strlen(aux)] = '\n';
			fputs(aux, fp2);
		}
		memset(aux, 0, 1000);
		line = fgets(line, 1000, fp);
	}
	return;
}

void ex4() {
	FILE *fp1, *fp2, *fp3;
	fp1 = fopen("data41.in", "r");
	fp2 = fopen("data42.in", "r");
	fp3 = fopen("data4.out", "w");

	char *buf = malloc(10 * sizeof(char));
	int count = fread(buf, sizeof(char), 10, fp1);
	while (count > 0) {
		fwrite(buf, sizeof(char), 10, fp3);
		count = fread(buf, sizeof(char), 10, fp1);
	}

	count = fread(buf, sizeof(char), 10, fp2);
	while (count > 0) {
		fwrite(buf, sizeof(char), 10, fp3);
		count = fread(buf, sizeof(char), 10, fp2);
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

int main(void) {
	ex4();

	return 0;
}


