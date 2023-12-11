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

/*
1|"Se citesc N numere complexe sub forma (parte reală, parte imaginară).
Să se afișeze numerele în ordine crescătoare după modulul acestora
(|a + ib| = sqrt(a^2 + b^2)). În caz de egalitate, se sortează (crescător)
după partea reala iar ulterior după partea imaginară."|"
*/

typedef struct {
    double real;
    double imag;
} Complex;

void swap(Complex *a, Complex *b) {
    Complex aux = *a;
    *a = *b;
    *b = aux;
}

void ex1() {
    int n;
    scanf("%d", &n);
    Complex *v = malloc(n * sizeof(Complex));
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf", &v[i].real, &v[i].imag);
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i; j < n; ++j) {
            if (sqrt(v[i].real * v[i].real + v[i].imag * v[i].imag) > sqrt(v[j].real * v[j].real + v[j].imag * v[j].imag)) {
                swap(&v[i], &v[j]);
            }
        }
    }
    for ( int i = 0; i < n; ++i) {
        printf("%lf %lf; ", v[i].real, v[i].imag);
    }
    printf("\n");
}

/*
"Se citesc N tupluri (nume, prenume, vârstă). Să se sorteze crescător după
nume, în caz de egalitate descrescător după prenume și în caz de egalitate
crescător după vârstă. Numele și prenumele sunt șiruri de caractere de lungime
maxim 30 ce nu conțin spații.
*/

struct info {
    char nume[31];
    char prenume[31];
    int varsta;
};

void interschimbare(struct info *a, struct info *b) {
    struct info aux = *a;
    *a = *b;
    *b = aux;
}

void ex2() {
    int n;
    scanf("%d", &n);
    struct info *v = malloc(n * sizeof(struct info));
    for (int i = 0; i < n; ++i) {
        scanf("%s %s %d", v[i].nume, v[i].prenume, &v[i].varsta);
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i; j < n; ++j) {
            if (strcmp(v[i].nume, v[j].nume) > 0) {
                interschimbare(&v[i], &v[j]);
            } else if (strcmp(v[i].nume, v[j].nume) == 0) {
                if (strcmp(v[i].prenume, v[j].prenume) < 0) {
                    interschimbare(&v[i], &v[j]);
                } else if (strcmp(v[i].prenume, v[j].prenume) == 0) {
                    if (v[i].varsta > v[j].varsta) {
                        interschimbare(&v[i], &v[j]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%s %s %d ; ", v[i].nume, v[i].prenume, v[i].varsta);
    }
    printf("\n");
}


//Se consideră următoarea structură (Big Number):

struct BigNumber {
        int nr_elemente;
        int v_elemente[502];
};

/* 
Să se implementeze o funcție care va realiza suma a 2 variabile de acest tip.
În v_elemente, la fiecare index, se află câte o cifră.
Adunarea trebuie să se facă ținând cont de carry. Numărul maxim de cifre ale
numerelor citite este 500."|"
 
*/

void insert_0( char * s ) {
    int n = strlen(s);
    for (int i = n - 1 ; i > 0; --i) {
        s[i] = s[i - 1];
    }
    s[0] = '0';
    char *sol = malloc((n + 2) * sizeof(char));
    strcpy(sol, s);
    sol[n + 1] = '\0';
    free(s);
    s = sol;
}

void ex3() {
    struct BigNumber a, b, sol;
    for (int i = 0 ; i < 502 ; i++ ) {
        b.v_elemente[i] = 0;
        a.v_elemente[i] = 0;
        sol.v_elemente[i] = 0;
    }
    // citim numerele mari caracter cu caracter
    scanf("%d", &a.nr_elemente);
    char* c = malloc((a.nr_elemente + 1) * sizeof(char));
    scanf("%s", c);
    for (int i = 0; i < a.nr_elemente; ++i) {
        a.v_elemente[i] = c[i] - '0';
    }
    scanf("%d", &b.nr_elemente);
    char *cc = malloc((b.nr_elemente + 1) * sizeof(char));
    scanf("%s", cc);
    for (int i = 0; i < b.nr_elemente; ++i) {
        b.v_elemente[i] = cc[i] - '0';
    }
    // inversam cifrele ca sa avem unitatile pe prima pozitie samd
    for (int i = 0; i < a.nr_elemente / 2; ++i) {
        int aux = a.v_elemente[i];
        a.v_elemente[i] = a.v_elemente[a.nr_elemente - i - 1];
        a.v_elemente[a.nr_elemente - i - 1] = aux;
    }
    for (int i = 0; i < b.nr_elemente / 2; ++i) {
        int aux = b.v_elemente[i];
        b.v_elemente[i] = b.v_elemente[b.nr_elemente - i - 1];
        b.v_elemente[b.nr_elemente - i - 1] = aux;
    }
    
    // inversarea permite adunarea fara dificultati!
    int maxim = a.nr_elemente > b.nr_elemente ? a.nr_elemente : b.nr_elemente;
    int minim = a.nr_elemente < b.nr_elemente ? a.nr_elemente : b.nr_elemente;
    int de_tinut_minte = 0;
    // Pt buc in care ambele numere au cifre le adunam
    for( int  i = 0 ; i < minim ; i++ ) {
        de_tinut_minte = 0;
        sol.v_elemente[i] += a.v_elemente[i] + b.v_elemente[i];
        if ( sol.v_elemente[i] > 9 ) {
            sol.v_elemente[i] -= 10;
            sol.v_elemente[i + 1] += 1;
            de_tinut_minte = 1;
        }
    }
    // Daca la ultima cifra ne confruntam cu adunarea peste ordin, crestem nr de elemente
    if( de_tinut_minte == 1 ) {
        sol.nr_elemente = maxim + 1;
    }
    else {
        sol.nr_elemente = maxim;
    }
    // Cand doar un nr are cifre, le copiem
    for( int i = minim ; i < maxim ; i++ ) {
        if (a.nr_elemente > b.nr_elemente) {
            sol.v_elemente[i] += a.v_elemente[i];
        } else {
            sol.v_elemente[i] += b.v_elemente[i];
        }
    }
    
    // rev sol
    for (int i = 0; i < sol.nr_elemente / 2; ++i) {
        int aux = sol.v_elemente[i];
        sol.v_elemente[i] = sol.v_elemente[sol.nr_elemente - i - 1];
        sol.v_elemente[sol.nr_elemente - i - 1] = aux;
    }
    // Sol reved
    for (int i = 0 ; i < sol.nr_elemente ; i++) {
        printf("%d", sol.v_elemente[i]);
    }
    printf("\n");
    
}

/*
id|enunt|exemplu
1|"(fără teste, trebuie verificată pe cod) Se dau următoarele structuri:
*/

struct song {
    int id;
    char name[30];
    char artist[30];
};

struct album {
    int id;
    int number_of_songs;
    int max_number_of_songs;
    struct song *songs;
};

/* 
Scrieți o funcție ce alocă o structură de tip album:
  struct album* allocAlbum(int id, int max_number_of_songs)
și una ce adaugă un nou cântec la album, dacă nu și-a atins limita de cântece
  void addSong(struct album* a, struct song s)."|"
*/

struct album* allocAlbum(int id, int max_number_of_songs) {
    struct album *a = malloc(sizeof(struct album));
    a->id = id;
    a->number_of_songs = 0;
    a->max_number_of_songs = max_number_of_songs;
    a->songs = malloc(max_number_of_songs * sizeof(struct song));
    return a;
}

void addSong(struct album* a, struct song s) {
    if (a->number_of_songs < a->max_number_of_songs) {
        a->songs[a->number_of_songs] = s;
        a->number_of_songs++;
    }
    else {
        printf("Albumul este plin!\n");
        printf("(Codu crapa) sau nu\n");
    }
}

/*
Se sa implementeze o coada cu doua capete având următoarea definiție:
*/
struct deque {
    int left, right;
    int elements[1000];
};

/* 
Se implementează urmatoarele operații:
* pop_front  (sterge elementul @left și incrementeză left).
* pop_back (sterge elementul @right și decrementează right);
* push_front x (adaugă x in față);
* push_back x (adaugă x la sfârșitul cozii).
* print - afișează conținutul cozii - numerele vor fi separate printr-un spațiu
  și afișate pe un singur rând;
  
Se garantează că nu vor exista mai mult de 500 de operații push_front/push_back
(în total).  Numarul total de operatii va fi mai mic de 1500. Dacă se executa
pop_front sau pop_back pe o coada vida, operațiile nu vor avea nici un efect.
Numerele din coada se pot ține pe 32 de biți cu semn."|"
*/

void pop_front(struct deque *d) {
    if (d->left <= d->right) {
        d->left++;
    }
}

void pop_back(struct deque *d) {
    if (d->left <= d->right) {
        d->right--;
    }
}

void push_front(struct deque *d, int x) {
    if (d->left > 0) {
        d->left--;
        d->elements[d->left] = x;
    }
}

void push_back(struct deque *d, int x) {
    if (d->right < 999) {
        d->right++;
        d->elements[d->right] = x;
    }
}

void print(struct deque *d) {
    for (int i = d->left; i <= d->right; ++i) {
        printf("%d ", d->elements[i]);
    }
    printf("\n");
}

/*
Să se implementeze o structură de date de tip stivă (pentru șiruri de
   caractere):
   */
 
struct deque_oneway {
    int top;
    char elements[1000][31];
};

/* 
Operațiile pe această stivă vor fi:
* pop - șterge elementul din vârful stivei (dacă stiva este goala atunci nu se
  întâmplă nimic);
* push cuv - adaugă cuvântul în vârful stivei;
* print - afișează elementele stivei începând cu cel mai vechi adăugat.
*/

void pop(struct deque_oneway *d) {
    if (d->top > 0) {
        d->top--;
    }
}

void push(struct deque_oneway *d, char *cuv) {
    if (d->top < 999) {
        d->top++;
        strcpy(d->elements[d->top], cuv);
    }
}

void print_oneway(struct deque_oneway *d) {
    for (int i = 1; i <= d->top; ++i) {
        printf("%s ", d->elements[i]);
    }
    printf("\n");
}

int main(void) {
    ex3();
}