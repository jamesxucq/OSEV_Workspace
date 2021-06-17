#include <stdlib.h>
#include <string.h>

#include "cona_list.h"

//
#define COLIST_PREPEND(head, add) { \
    add->next = head; \
    head = add; \
}

contain *appe_conta(cont_list **colsth) {
    contain *conta;
    conta = (contain *) malloc(sizeof (contain));
    if (!conta) return NULL;
    //
    cont_list *colist;
    colist = (cont_list *) malloc(sizeof (cont_list));
    if (!colist) {
        free(conta);
        return NULL;
    }
    colist->conta = conta;
    //
    COLIST_PREPEND((*colsth), colist)
    return conta;
}

void dele_colst(cont_list *colist) {
    cont_list *colitmp;
    while (colist) {
        colitmp = colist;
        colist = colist->next;
        free(colitmp);
    }
}


void cona_free(void *conta) {
    if (conta) free(conta);
}