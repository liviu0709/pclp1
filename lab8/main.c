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

// 1|"Se citeste de la tastatura un cuvant format din litere mici si mare ale
// alfabetului englez (fara whitespace) si un caracter (cuvantul are mai putin de
// 100 de caractere). Sa se inlocuiasca fiecare aparitie a caracterului in
// cuvantul intial cu numarul de aparitii ale caracterului pana in momentul
// respectiv

void ex1() {
    char *s = malloc(100 * sizeof(char));
    char c;
    scanf("%s %c", s, &c);
    int cnt = 0;
    for ( int i = 0 ; i < strlen(s) ; i++ ) {
        if ( s[i] == c ) {
            cnt++;
            s[i] = cnt + '0';
        }
    }
    printf("%s\n", s);
}

// Sa citeste un numar natural N (1 <= N <= 50) urmat de N cuvinte cu lungimea
// cel mult 50. Sa se sorteze cuvintele in ordine lexicografica

void ex2() {
    int n = 0;
    scanf("%d", &n);
    char **v = malloc(n * sizeof(char*));
    for ( int i = 0 ; i < n ; i++ ) {
        v[i] = malloc(50 * sizeof(char));
        scanf("%s", v[i]);
    }
    for ( int i = 0 ; i < n ; i++ ) {
        for ( int j = i + 1 ; j < n ; j++ ) {
            if ( strcmp(v[i], v[j]) > 0 ) {
                char *aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    for ( int i = 0 ; i < n ; i++ ) {
        printf("%s ", v[i]);
    }
    printf("\n");
    for ( int i = 0 ; i < n ; i++ ) {
        free(v[i]);
    }
    free(v);
}

/* Se citeste de la tastatura o propozitie (cuvinte separate prin unul sau mai
multe spatii, care se termina cu un semn de punctuatie: '.', '!' sau '?').
Pe urmatoarea linie se citeste un cuvant. Sa se determine de cate ori apare
cuvantul in propozitia data
*/

void ex3() {
    char **s = malloc(100 * sizeof(char*));
    char *cuv = malloc(100 * sizeof(char));
    for ( int i = 0 ; i < 100 ; i++ ) {
        s[i] = malloc(100 * sizeof(char));
    }
    int n = 0;
    for ( ; ; n++ ) {
        scanf("%s", s[n]);
        if( s[n][strlen(s[n]) - 1] == '.' || s[n][strlen(s[n]) - 1] == '!' || s[n][strlen(s[n]) - 1] == '?' ) {
            break;
        }
    }
    scanf("%s", cuv);
    int nr_aparitii = 0;
    for ( int i = 0 ; i < n ; i++ )
        if ( strstr(s[i], cuv) != NULL )
            nr_aparitii++;
    printf("Cuvantul data a aparut de %d ori\n", nr_aparitii);
}

/*
Se citeste de la tastatura o propozitie (cuvinte separate prin unul sau mai
multe spatii, tab-uri). Sa se afiseze cea mai lunga pereche de cuvinte care
rimeaza. Doua cuvinte rimeaza daca ultimele 2 caractere sunt egale. Lungime
unei perechi de cuvinte este lungimea primului cuvant + lungimea celui
de-al doilea cuvant. Se va afisa mai intai cuvantul minim lexicografic din
pereche. Se garanteaza ca nu exista mai multe perechi de cuvinte care rimeaza
cu lungime maxima (output-ul este unic).
*/

void ex4() {
    char **s = malloc(100 * sizeof(char*));
    for ( int i = 0 ; i < 100 ; i++ ) {
        s[i] = malloc(100 * sizeof(char));
    }
    int n = 0;
    for ( ; ; n++ ) {
        scanf("%s", s[n]);
        if( s[n][strlen(s[n]) - 1] == '.' || s[n][strlen(s[n]) - 1] == '!' || s[n][strlen(s[n]) - 1] == '?' ) {
            s[n][strlen(s[n]) - 1] = '\0';
            break;
        }
    }
    n++;
    int max = 0;
    for ( int i = 0 ; i < n ; i++ ) {
        for ( int j = i + 1 ; j < n ; j++ ) {
            if ( s[i][strlen(s[i]) - 1] == s[j][strlen(s[j]) - 1] && s[i][strlen(s[i]) - 2] == s[j][strlen(s[j]) - 2] ) {
                if ( strlen(s[i]) + strlen(s[j]) - 2 > max ) {
                    max = strlen(s[i]) + strlen(s[j]) - 2;
                }
            }
        }
    }
    for ( int i = 0 ; i < n ; i++ ) {
        for ( int j = i + 1 ; j < n ; j++ ) {
            if ( s[i][strlen(s[i]) - 1] == s[j][strlen(s[j]) - 1] && s[i][strlen(s[i]) - 2] == s[j][strlen(s[j]) - 2] ) {
                if ( strlen(s[i]) + strlen(s[j]) - 2 == max ) {
                    if ( strcmp(s[i], s[j]) < 0 ) {
                        printf("%s %s\n", s[i], s[j]);
                    } else {
                        printf("%s %s\n", s[j], s[i]);
                    }
                }
            }
        }
    }

}

/*
Se citeste de la tastatura un cuvant format din litere mari, litere mici si
cifre. Sa se afiseze cel mai lung prefix al cuvantului diferit de cuvantul
intreg, care este si sufix si acestuia. Un prefix al unui string este un
substring (pozitii consecutive) care incepe pe pe prima pozitie. Un sufix al
unui string este un substring care se termina pe ultima pozitie.
Atentie, nu consideram prefixul egal cu intreg cuvantul.
*/
void ex5() {
    char *s = malloc(100 * sizeof(char));
    scanf("%s", s);
    int i, ok = 1;
    for ( i = 0 ; i < strlen(s) / 2 ; i++ ) {
        //printf("%c %c\n", s[i], s[strlen(s) - i - 1]);
        if ( s[i] != s[strlen(s) - i - 1] ) {
            ok = 0;
            break;
        }
    }
    if ( i == 0 ) {
        printf("Nu exista");
    } else {
        for ( int j = 0 ; j < i ; j++ ) {
            printf("%c", s[j]);
        }
    }
    printf("\n");
}

/*
Se se implementeze o structura de date care suporta urmatoarele operatii:
 
  1 cuvant - adauga cuvantul in multimea de cuvinte. Daca cuvantul
    exista deja atunci operatia nu aduce noi modificari;
  2 cuvant - sterge cuvantul din set-ul de cuvinte daca acesta exista;
  3 cuvant - afiseaza DA sau NU in functie de apartenenta cuvantului
    la set-ul de cuvinte.
 
Toate cuvintele citite vor conține doar litere mici și litere mari ale
alfabetului englez. Se citește de la tastatura numărul de operații (N) urmat
de N linii fiecare descriind o anumita operație.
Inițial, setul de cuvinte este vid
*/
struct cuvant {
    char **s;
    int n;
    void (*adauga)(struct cuvant *this, char *s);
    void (*sterge)(struct cuvant *this, char *s); // acest this poate fi inlocuit cu orice altceva, e doar un nume
    void (*afiseaza)(struct cuvant *this, char *s); // nu ma intereseaza functionalitatea de -> in loc de . la structuri
} stiva;

//functia adauga
void adauga(struct cuvant *this, char *s) {
    int ok = 1;
    for ( int i = 0 ; i < this->n ; i++ ) {
        if ( strcmp(this->s[i], s) == 0 ) {
            ok = 0;
            break;
        }
    }
    if ( ok == 1 ) {
        this->s[this->n] = malloc(100 * sizeof(char));
        strcpy(this->s[this->n], s);
        this->n++;
    }
}

void sterge(struct cuvant *this, char *s) {
    int ok = 0;
    for ( int i = 0 ; i < this->n ; i++ ) {
        if ( strcmp(this->s[i], s) == 0 ) {
            ok = 1;
            free(this->s[i]);
            for ( int j = i ; j < this->n - 1 ; j++ ) {
                strcpy(this->s[j], this->s[j + 1]);
            }
            this->n--;
            break;
        }
    }
    if ( ok == 0 ) {
        printf("Cuvantul nu exista in lista\n");
    }
}

void afiseaza(struct cuvant *this, char *s) {
    int ok = 0;
    for ( int i = 0 ; i < this->n ; i++ ) {
        if ( strcmp(this->s[i], s) == 0 ) {
            ok = 1;
            break;
        }
    }
    if ( ok == 1 ) {
        printf("DA\n");
    } else {
        printf("NU\n");
    }
}

int** alocMatrice( int n, int m ) {
    int **v = malloc( n * sizeof(int*));
    for( int i = 0 ; i < n ; i++ ) {
        v[i] = malloc( m * sizeof(int));
    }
    return v;
}

void free_v( int **v, int n ) {
    for( int i = 0 ; i < n ; i++ ) {
        free(v[i]);
    }
    free(v);
}

int main(void) {
    /*int n, m, dist;
    scanf("%d%d%d", &n, &m, &dist);
    int **v = alocMatrice(n, m), **gol = alocMatrice(n, m);
    for( int i = 0 ; i < n ; i++ ) {
        for( int j = 0 ; j < m ; j++ ) {
            scanf("%d", &v[i][j]);
        }
    }*/
    // ex1();
    //ex2();
    //ex3();
    //ex4();
    //ex5
    stiva.s = malloc(100 * sizeof(char*));
    stiva.n = 0;
    stiva.adauga = adauga;
    stiva.sterge = sterge;
    stiva.afiseaza = afiseaza;
    int n;
    scanf("%d", &n);
    for ( int i = 0 ; i < n ; i++ ) {
        int op;
        char *s = malloc(100 * sizeof(char));
        scanf("%d %s", &op, s);
        switch ( op ) {
            case 1:
                stiva.adauga(&stiva, s);
                break;
            case 2:
                stiva.sterge(&stiva, s);
                break;
            case 3:
                stiva.afiseaza(&stiva, s);
                break;
        }
        free(s);
    }
}
 