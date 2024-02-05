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
#include <stdarg.h>

typedef struct TPlayer{
    int id;
    char *nume;
    int crtLife, victorii;
    void (*action)(struct TPlayer*,...);
} TPlayer;

typedef struct {
    TPlayer *p1, *p2;
    int dmg, time;
} TFight;

typedef struct {
    int nrCrtPlayers, nrMaxPlayers;
    int nrCrtFights, nrMaxFights;
    int maxLife;
    TPlayer *players;
    TFight *fights;
} TGame;

TGame *alocaJoc(int nrMaxPlayers, int nrMaxFights) {
    TGame *x = calloc(1, sizeof(TGame));
    x->nrMaxFights = nrMaxFights;
    x->nrMaxPlayers = nrMaxPlayers;
    x->players = calloc(nrMaxPlayers, sizeof(TPlayer));
    x->fights = calloc(nrMaxFights, sizeof(TFight));
    return x;
}

void action(TPlayer *player, ...) {
    va_list valist;
    va_start(valist, player);
    if ( player == NULL ) {
        TPlayer *x = va_arg(valist, TPlayer*);
        int y = va_arg(valist, int);
        x->crtLife -= y;
    } else {
        int y = va_arg(valist, int);
        player->crtLife += y;
    }
    va_end(valist);
}

int cmp(const void* a, const void* b) {
    TFight *x = (TFight*) a;
    TFight *y = (TFight*) b;
    return x->time - y->time;
}

void sortFights(TGame *x) {
    qsort(x->fights, x->nrCrtFights, sizeof(TFight), cmp);
}

TPlayer *computeKills(TGame *x, int *max) {
    for ( int i = 0 ; i < x->nrCrtFights ; i++ ) {
        x->fights[i].p2->crtLife -= x->fights[i].dmg;
        if ( x->fights[i].p2->crtLife <= 0 )
            x->fights[i].p1->victorii++;
    }
    *max = 0;
    for ( int i = 0 ; i < x->nrCrtPlayers ; i++ ) {
        if ( x->players[i].victorii > *max )
            *max = x->players[i].victorii;
    }
    for ( int i = 0 ; i < x->nrCrtPlayers ; i++ ) {
        if ( x->players[i].victorii == *max ) {
            return &x->players[i];
        }
    }
    return NULL;
}

void FinalJoc(TGame *x, FILE *out) {
    sortFights(x);
    for ( int i = 0 ; i <= x->nrCrtFights ; i++ ) {
        x->fights[i].p2 -= x->fights[i].dmg;
        fprintf(out, "(%d) %s ii provoaca %d lui %s", x->fights[i].time, x->fights[i].p1->nume, x->fights[i].dmg, x->fights[i].p2->nume);
        if ( x->fights[i].p2->crtLife <= 0 ) {
            x->fights[i].p1->victorii++;
            fprintf(out, "%s este omorat. %s are %d victorie", x->fights[i].p2->nume, x->fights[i].p1->nume, x->fights[i].p1->victorii);
        }
        fprintf(out, "\n");
    }
} 

void main(void) {
    TPlayer *a = calloc(1, sizeof(TPlayer)), *b = calloc(1, sizeof(TPlayer)), *c = calloc(1, sizeof(TPlayer));
    action(a, 15);
    action(NULL, b, 69);
    printf("%d %d\n", a->crtLife, b->crtLife);

}