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

typedef struct {
    char *nume, *mail;
} TContact;

typedef struct TMail {
    TContact *src, *dst;
    char *mesaj;
    int data;
    struct TMail *replyof;
} TMail;

typedef struct {
    int nrCrtMails, nrMaxMails, nrCrtContacts, nrMaxContacts;
    TMail *mails;
    TContact *contacts;
} TClient;

TClient *alocaElement(int nrMaxMails, int nrMaxContacts) {
    TClient *x = calloc(1, sizeof(TClient));
    x->nrMaxContacts = nrMaxContacts;
    x->nrMaxMails = nrMaxMails;
    x->mails = calloc(nrMaxMails, sizeof(TMail));
    x->contacts = calloc(nrMaxContacts, sizeof(TContact));
    return x;
}

TContact *getContact(TClient *c, char *mail) {
    for ( int i = 0 ; i < c->nrCrtContacts ; i++ ) {
        if ( strcmp(c->contacts[i].mail, mail) == 0 ) {
            return &c->contacts[i];
        }
    }
    c->contacts[c->nrCrtContacts].mail = calloc(strlen(mail), sizeof(char));
    strcpy(c->contacts[c->nrCrtContacts].mail, mail);
    c->nrCrtContacts++;
    return &c->contacts[c->nrCrtContacts - 1];
}

TMail *writeMail(TClient *c, char *mailsrc, char *maildst, char *msj, TMail *replayto) {
    if ( c->nrCrtMails == c->nrMaxMails )
        return NULL;
    c->mails[c->nrCrtMails].dst = getContact(c, maildst);
    c->mails[c->nrCrtMails].src = getContact(c, mailsrc);
    c->mails[c->nrCrtMails].replyof = replayto;
    c->mails[c->nrCrtMails].mesaj = msj;
    c->nrCrtMails++;
    return &c->mails[c->nrCrtMails - 1];
}

void AfiThread(TClient *c, TMail *mail) {
    while ( mail->replyof != NULL )
        mail = mail->replyof;
    printf("from: %s to %s: %s\n", mail->src->mail, mail->dst->mail, mail->mesaj);
    int cnt = 1;
    for ( int i = 0 ; i < c->nrCrtMails ; i++ ) {
        if ( &c->mails[i] == mail ) {
            printf("from: %s to %s: %s reply %d %d\n", c->mails[i].src->mail, c->mails[i].dst->mail, c->mails[i].mesaj, cnt, c->mails[i].data);
            cnt++;
        }
    }
    /*
    nu
    */
}

TClient *dezalocare(TClient **x) {
    free((*x)->contacts);
    free((*x)->mails);
    free((*x));
    free(x);
    return NULL;
}