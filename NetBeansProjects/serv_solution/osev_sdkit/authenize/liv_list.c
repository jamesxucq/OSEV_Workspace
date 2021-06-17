
#include "liv_list.h"

//

struct liv_list *appe_live_list(struct liv_list **llsth, void *liv_data, int liv_len) {
    struct liv_list *llistmp = (struct liv_list *) malloc(sizeof (struct liv_list));
    if (!llistmp) return NULL;
    //
    llistmp->liv_data = malloc(liv_len);
    if (!llistmp->liv_data) {
        free(llistmp);
        return NULL;
    }
    memcpy(llistmp->liv_data, liv_data, liv_len);
    //
    LL_APPEND(*llsth, llistmp);
    return llistmp;
}

struct liv_list *addi_live_list(struct liv_list **llsth, int liv_len) {
    struct liv_list *llistmp = (struct liv_list *) malloc(sizeof (struct liv_list));
    if (!llistmp) return NULL;
    //
    llistmp->liv_data = malloc(liv_len);
    if (!llistmp->liv_data) {
        free(llistmp);
        return NULL;
    }
    //
    LL_APPEND(*llsth, llistmp);
    return llistmp;
}

void dele_live_list(struct liv_list *llist) {
    struct liv_list *llistmp;
    while (llist) {
        llistmp = llist;
        llist = llist->next;
        free(llistmp->liv_data);
        free(llistmp);
    }
}

void dele_livlst(struct liv_list **llsth, struct liv_list *llist) {
    LL_DELETE(*llsth, llist)
    free(llist->liv_data);
    free(llist);
}

#define LL_DELETE_LIV(posi, head, dele) { \
    LDECLTYPE(head) _tmp; \
    if ((head)->liv_data == (dele)) (head)=(head)->next; \
    else { \
        _tmp = head; \
        while (_tmp->next && ((_tmp->next)->liv_data != (dele))) _tmp = _tmp->next; \
        if (_tmp->next) { \
            posi = _tmp->next; \
            _tmp->next = posi->next; \
        } \
    } \
}

void dele_livdat(struct liv_list **llsth, void *ldata) {
    struct liv_list *llist = NULL;
    LL_DELETE_LIV(llist, *llsth, ldata)
    if (llist) {
        free(llist->liv_data);
        free(llist);
    }
}