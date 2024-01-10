#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timelib.h"

typedef struct {
    char name[10];
    int k_intervale, *lung_interval;
    unsigned int *data;
    TTimezone *tz;
} Persoana;

TTimezone *get_timezone(char *name, TTimezone *fus_orar, int T)
{
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

int compara_persoane(const void *a, const void *b) {
    Persoana *x = (Persoana *)a;
    Persoana *y = (Persoana *)b;
    return strcmp(x->name, y->name);
}

int compara_numere(const void *a, const void *b) {
    unsigned int *x = (unsigned int *)a;
    unsigned int *y = (unsigned int *)b;
    return *x - *y;
}

void unificare_intervale(Persoana *x) {
    // Sortam intervalele in ordine cronologica
    qsort(x->data, x->k_intervale, sizeof(unsigned int), compara_numere);
    // Unificam intervalele
    for ( int i = 0 ; i < x->k_intervale - 1 ; i++ ) {
        if ( x->data[i] + x->lung_interval[i] * 3600 >= (*x).data[i + 1] ) {
            x->lung_interval[i] = (x->data[i + 1] - x->data[i]) / 3600 + x->lung_interval[i + 1];
            for ( int j = i + 1 ; j < x->k_intervale - 1 ; j++ ) {
                x->data[j] = x->data[j + 1];
                x->lung_interval[j] = x->lung_interval[j + 1];
            }
            x->k_intervale--;
            i--;
        }
    }

}

int main()
{
    // TODO Task 9
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
        char nume_timezone[5];
        scanf("%s", nume_timezone);
        pers[i].tz = get_timezone(nume_timezone, fus_orar, T);
        scanf("%d", &pers[i].k_intervale);
        pers[i].data = calloc(pers[i].k_intervale, sizeof(unsigned int));
        pers[i].lung_interval = calloc(pers[i].k_intervale, sizeof(int));
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
    /*
    // Afisam intervalele unificate
    
    for ( int i = 0 ; i < nr_Pers ; i++ ) {
        printf("%s\n", pers[i].name);
        for ( int j = 0 ; j < pers[i].k_intervale ; j++ ) {
            TDateTimeTZ dt;
            dt = convertUnixTimestampToDateTimeTZ(pers[i].data[j], fus_orar, get_timezone_index(fus_orar, pers[i].tz, T));
            printDateTimeTZ(dt);
            printf(" %d\n", pers[i].lung_interval[j]);
        }
    }
    */

    // Calculam timpul de la care incepem verificarea
    unsigned int min_num = pers[0].data[0];
    for ( int i = 0 ; i < nr_Pers ; i++ ) {
        for ( int j = 0 ; j < pers[i].k_intervale ; j++) {
            if ( pers[i].data[j] < min_num )
                min_num = pers[i].data[j];
        }
    }
    // Calculam timpul pana la care verificam
    unsigned int max_num = pers[0].data[0] + pers[0].lung_interval[0] * 3600;
    for ( int i = 0 ; i < nr_Pers ; i++ ) {
        for ( int j = 0 ; j < pers[i].k_intervale ; j++) {
            if ( pers[i].data[j] + pers[i].lung_interval[j] > max_num )
                max_num = pers[i].data[j] + pers[i].lung_interval[j] * 3600;
        }
    }
    // Luam fiecare timp pe rand si vedem cate persoane au timp pentru eveniment
    // In plus, verificam doar din ora in ora
    // Pentru a putea folosi aceasta abordare, trebuie unificare intervalele de timp la fiecare persoana
    static int event_start, am_gasit_solutie;
    for ( event_start = min_num ; event_start <= max_num - durata_eveniment * 3600; event_start += 3600 ) {
        int nr_pers_disponibile = 0;
        for ( int j = 0 ; j < nr_Pers ; j++ ) {
            for ( int k = 0 ; k < pers[j].k_intervale ; k++ ) {
                if ( event_start >= pers[j].data[k] && event_start + durata_eveniment * 3600  <= pers[j].data[k] + pers[j].lung_interval[k] * 3600 ) {
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
    if ( am_gasit_solutie == 0 ) {
        printf("imposibil\n");
    } else {
        // Inainte de afisare, sortam persoanele dupa nume
        qsort(pers, nr_Pers, sizeof(Persoana), compara_persoane);
        for ( int j = 0 ; j < nr_Pers ; j++ ) {
            int ok = 0;
            printf("%s : ", pers[j].name);
            for ( int k = 0 ; k < pers[j].k_intervale ; k++ ) {
                if ( event_start >= pers[j].data[k] && event_start + durata_eveniment * 3600 <= pers[j].data[k] + pers[j].lung_interval[k] * 3600 ) {
                    TDateTimeTZ dt;
                    dt = convertUnixTimestampToDateTimeTZ(event_start, fus_orar, get_timezone_index(fus_orar, pers[j].tz, T));
                    printDateTimeTZ(dt);
                    ok = 1;
                    break;
                }
            }
            if ( ok == 0 )
                printf("invalid\n");
        }
    }
    /*
    for ( int i = 0 ; i < nr_Pers ; i++ ) {
        for ( int j = 0 ; j < pers[i].k_intervale ; j++)
            printDateTimeTZ(convertUnixTimestampToDateTimeTZ(pers[i].data[j], fus_orar, get_timezone_index(fus_orar, pers[i].tz, T)));
    }
    */
    return 0;
}
