

#include "clas_list.h"

#define CLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    add->next = NULL; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

//
method *appe_mlist_new(method **mlsth) {
    method *mlistmp = (method *) malloc(sizeof (method));
    if (!mlistmp) return NULL;
    memset(mlistmp, '\0', sizeof (method));
    //
    CLIST_APPEND(*mlsth, mlistmp);
    return mlistmp;
}

//
inline void mlist_dele(method *mlist) {
    method *mlistmp;
    while (mlist) {
        mlistmp = mlist;
        mlist = mlist->next;
        free(mlistmp);
    }
}