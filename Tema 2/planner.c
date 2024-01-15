#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timelib.h"

enum { sec_in_ora = 3600 };
typedef struct {
    char name[4 + 4 + 3];
    int k_intervale, *lung_interval;
    unsigned int *data;
    TTimezone *tz;
} Persoana;

TTimezone *get_timezone(char *name, TTimezone *fus_orar, int T) {
    for ( int i = 0; i < T; i++ ) {
        if ( strcmp(name, fus_orar[i].name) == 0 )
            return &fus_orar[i];
    }
    return NULL;
}

int get_timezone_index(TTimezone *fus_orar, TTimezone *tz, int T) {
    for ( int i = 0; i < T; i++ ) {
        if ( fus_orar[i].utc_hour_difference == tz->utc_hour_difference )
            return i;
    }
    return -1;
}

// Folosita pentru ordonarea alfabetica a persoanelor
int compara_persoane(const void *a, const void *b) {
    Persoana *x = (Persoana *)a;
    Persoana *y = (Persoana *)b;
    return strcmp(x->name, y->name);
}

// Folosita pentru ordonarea crescatoare a intervalelor
int compara_numere(const void *a, const void *b) {
    unsigned int *x = (unsigned int *)a;
    unsigned int *y = (unsigned int *)b;
    return (int)*x - (int)*y;
}

void unificare_intervale(Persoana *x) {
    // Sortam intervalele in ordine cronologica
    qsort(x->data, x->k_intervale, sizeof(unsigned int), compara_numere);
    // Unificam intervalele
    for ( int i = 0 ; i < x->k_intervale - 1 ; i++ ) {
        if ( x->data[i] + x->lung_interval[i] * sec_in_ora >= (*x).data[i + 1] ) {
            // Uneori, primul interval este mai mare decat al doilea
            if ( x->data[i + 1] - x->data[i] + x->lung_interval[i + 1] >  x->lung_interval[i] * sec_in_ora  )
                x->lung_interval[i] = ((int)(x->data[i + 1] - x->data[i])) / sec_in_ora + x->lung_interval[i + 1];
            else
                x->lung_interval[i] = x->lung_interval[i];
            // Stergem intervalul unificat
            for ( int j = i + 1 ; j < x->k_intervale - 1 ; j++ ) {
                x->data[j] = x->data[j + 1];
                x->lung_interval[j] = x->lung_interval[j + 1];
            }
            x->k_intervale--;
            i--;
        }
    }
}

int main() {
    // Task 9
    static int T, nr_Pers, nr_min_Pers, durata_eveniment;
    scanf("%d", &T);
    TTimezone *fus_orar = calloc(T, sizeof(TTimezone));
    for ( int i = 0; i < T; i++ ) {
        scanf("%s", fus_orar[i].name);
        scanf("%hhd", &fus_orar[i].utc_hour_difference);
    }
    scanf("%d", &nr_Pers);
    Persoana *pers = calloc(nr_Pers, sizeof(Persoana));
    for ( int i = 0; i < nr_Pers; i++ ) {
        scanf("%s", pers[i].name);
        char nume_timezone[4 + 2];
        scanf("%s", nume_timezone);
        pers[i].tz = get_timezone(nume_timezone, fus_orar, T);
        scanf("%d", &pers[i].k_intervale);
        // Aparent unele persoane nu au timp deloc pentru eveniment
        // In acest caz, alocam un singur interval de timp
        // Ca sa trecem de valgrind
        if ( pers[i].k_intervale != 0 ) {
            pers[i].data = calloc(pers[i].k_intervale, sizeof(unsigned int));
            pers[i].lung_interval = calloc(pers[i].k_intervale, sizeof(int));
        } else {
            pers[i].data = calloc(1, sizeof(unsigned int));
            pers[i].lung_interval = calloc(1, sizeof(int));
        }
        for ( int j = 0; j < pers[i].k_intervale; j++ ) {
            static int an, luna, zi, ora;
            scanf("%d %d %d %d", &an, &luna, &zi, &ora);
            TDateTimeTZ dt;
            dt.date.day = zi;
            dt.date.month = luna;
            dt.date.year = an;
            dt.time.hour = ora;
            dt.time.min = 0;
            dt.time.sec = 0;
            dt.tz = pers[i].tz;
            pers[i].data[j] = convertDateTimeTZToUnixTimestamp(dt);
            scanf("%d", &pers[i].lung_interval[j]);
        }
    }
    scanf("%d", &nr_min_Pers);
    scanf("%d", &durata_eveniment);
    // Unificam intervalele de timp la fiecare persoana
    for ( int i = 0 ; i < nr_Pers ; i++ )
        unificare_intervale(&pers[i]);

    // Calculam timpul de la care incepem verificarea
    static int nr_Pers_care_are_timp = 0;
    while ( pers[nr_Pers_care_are_timp].k_intervale == 0 )
        nr_Pers_care_are_timp++;
    unsigned int min_num = pers[nr_Pers_care_are_timp].data[0];
    for ( int i = 0 ; i < nr_Pers ; i++ ) {
        for ( int j = 0 ; j < pers[i].k_intervale ; j++ ) {
            if ( pers[i].data[j] < min_num )
                min_num = pers[i].data[j];
        }
    }
    // Calculam timpul pana la care verificam
    unsigned int max_num = pers[nr_Pers_care_are_timp].data[0]
    + pers[nr_Pers_care_are_timp].lung_interval[0] * sec_in_ora;
    for ( int i = 0 ; i < nr_Pers ; i++ ) {
        for ( int j = 0 ; j < pers[i].k_intervale ; j++ ) {
            if ( pers[i].data[j] + pers[i].lung_interval[j] > max_num )
                max_num = pers[i].data[j] + pers[i].lung_interval[j] * sec_in_ora;
        }
    }
    // Luam fiecare timp pe rand si vedem cate persoane au timp pentru eveniment
    // In plus, verificam doar din ora in ora
    // Pentru a putea folosi aceasta abordare, trebuie unificare intervalele de timp la fiecare persoana
    static unsigned int event_start, am_gasit_solutie;
    for ( event_start = min_num ; event_start <= max_num - durata_eveniment * sec_in_ora; event_start += sec_in_ora ) {
        int nr_pers_disponibile = 0;
        for ( int j = 0 ; j < nr_Pers ; j++ ) {
            for ( int k = 0 ; k < pers[j].k_intervale ; k++ ) {
                if ( event_start >= pers[j].data[k] && event_start + durata_eveniment * sec_in_ora
                <= pers[j].data[k] + pers[j].lung_interval[k] * sec_in_ora ) {
                    nr_pers_disponibile++;
                    break;
                }
            }
        }
        if ( nr_pers_disponibile >= nr_min_Pers ) {
            am_gasit_solutie = 1;
            break;
        }
    }
    // Afisam ora la care participa fiecare persoana in functie de tz propriu
    // (Doar daca se poate)
    if ( am_gasit_solutie == 0 ) {
        printf("imposibil\n");
    } else {
        // Inainte de afisare, sortam persoanele dupa nume
        qsort(pers, nr_Pers, sizeof(Persoana), compara_persoane);
        for ( int j = 0 ; j < nr_Pers ; j++ ) {
            int ok = 0;
            printf("%s: ", pers[j].name);
            for ( int k = 0 ; k < pers[j].k_intervale ; k++ ) {
                if ( event_start >= pers[j].data[k] && event_start + durata_eveniment * sec_in_ora
                <= pers[j].data[k] + pers[j].lung_interval[k] * sec_in_ora ) {
                    TDateTimeTZ dt;
                    dt = convertUnixTimestampToDateTimeTZ(event_start, fus_orar,
                    get_timezone_index(fus_orar, pers[j].tz, T));
                    printDateTimeTZ(dt);
                    ok = 1;
                    break;
                }
            }
            if ( ok == 0 )
                printf("invalid\n");
        }
    }
    // Task 10
    // Eliberam memoria
    free(fus_orar);
    for ( int i = 0 ; i < nr_Pers ; i++ ) {
            free(pers[i].data);
            free(pers[i].lung_interval);
    }
    free(pers);
    return 0;
}
