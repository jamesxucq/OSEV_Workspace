#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clas_load.h"
#include "clas_list.h"
#include "conv_utili.h"

#define CLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    add->next = NULL; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

inherit *appe_ilist_new(inherit **ilsth) {
    inherit *ilistmp = (inherit *) malloc(sizeof (inherit));
    if (!ilistmp) return NULL;
    memset(ilistmp, '\0', sizeof (inherit));
    //
    CLIST_APPEND(*ilsth, ilistmp);
    return ilistmp;
}

inline void ilist_dele(inherit *ilist) {
    inherit *ilistmp;
    while (ilist) {
        ilistmp = ilist;
        ilist = ilist->next;
        free(ilistmp);
    }
}

//

metho *appe_mlist_new(metho **mlsth) {
    metho *mlistmp = (metho *) malloc(sizeof (metho));
    if (!mlistmp) return NULL;
    memset(mlistmp, '\0', sizeof (metho));
    //
    CLIST_APPEND(*mlsth, mlistmp);
    return mlistmp;
}

metho *appe_mlist_txt(metho **mlsth, char *meth_txt) {
    metho *mlistmp = (metho *) malloc(sizeof (metho));
    if (!mlistmp) return NULL;
    memset(mlistmp, '\0', sizeof (metho));
    //
    CLIST_APPEND(*mlsth, mlistmp);
    strcpy(mlistmp->meth_txt, meth_txt);
    return mlistmp;
}

inline void mlist_dele(metho *mlist) {
    metho *mlistmp;
    while (mlist) {
        mlistmp = mlist;
        mlist = mlist->next;
        free(mlistmp);
    }
}

metho *find_metho(metho *mlist, char *metnm) {
    printf("find_metho\n");
    while (mlist) {
        printf("metnm:%s meth_name:%s\n", metnm, mlist->meth_name);
        if (!strcmp(metnm, mlist->meth_name))
            break;
        mlist = mlist->next;
    }
    //
    return mlist;
}

metho *find_metho_ex(metho *mlist, char *metnm, char *decla) {
    char vtype[METH_LENGTH];
    if (!conv_decla_vtype(vtype, decla)) return NULL;
    printf("find_metho\n");
    while (mlist) {
        printf("metnm:%s meth_name:%s\n", metnm, mlist->meth_name);
        if (!strcmp(metnm, mlist->meth_name) && !strcmp(vtype, mlist->param_type))
            break;
        mlist = mlist->next;
    }
    //
    return mlist;
}

metho *dele_metho(metho **mlsth, char *metnm, char *paras) {
    char parat[PARAM_LENGTH];
    if (conv_ointe_type_decl(parat, paras)) return NULL;
    //
    metho *mlistmp = *mlsth;
    metho *prev_node;
    if (!mlistmp) return NULL;
    //
    if (strcmp(metnm, mlistmp->meth_name) && strcmp(parat, mlistmp->param_type)) {
        prev_node = mlistmp;
        mlistmp = mlistmp->next;
        while (mlistmp) {
            if (!strcmp(metnm, mlistmp->meth_name) && !strcmp(parat, mlistmp->param_type)) {
                prev_node->next = mlistmp->next;
                break;
            }
            prev_node = mlistmp;
            mlistmp = mlistmp->next;
        }
    } else *mlsth = mlistmp->next;
    //
    return mlistmp;
}

metho *dele_metho_ex(metho **mlsth, char *metnm, char *decla) {
    char vtype[METH_LENGTH];
    if (!conv_decla_vtype(vtype, decla)) return NULL;
    //
    metho *mlistmp = *mlsth;
    metho *prev_node;
    if (!mlistmp) return NULL;
    //
    if (strcmp(metnm, mlistmp->meth_name) && strcmp(vtype, mlistmp->param_type)) {
        prev_node = mlistmp;
        mlistmp = mlistmp->next;
        while (mlistmp) {
            if (!strcmp(metnm, mlistmp->meth_name) && !strcmp(vtype, mlistmp->param_type)) {
                prev_node->next = mlistmp->next;
                break;
            }
            prev_node = mlistmp;
            mlistmp = mlistmp->next;
        }
    } else *mlsth = mlistmp->next;
    //
    return mlistmp;
}

int modi_metho(metho *mlist, char *metnm, char *meth_txt) {
    printf("modi_metho\n");
    while (mlist) {
        if (!strcmp(metnm, mlist->meth_name)) {
            strcpy(mlist->meth_txt, meth_txt);
            break;
        }
        mlist = mlist->next;
    }
    //
    return 0x00;
}

//

inherit *addi_imeth(inherit **ilsth, char *metnm, char *parat, char *iclas) {
    inherit *ilistmp = appe_ilist_new(ilsth);
    if (!ilistmp) return NULL;
    strcpy(ilistmp->method, metnm);
    strcpy(ilistmp->parat, parat);
    strcpy(ilistmp->iclas, iclas);
    //
    return ilistmp;
}

inherit *dele_imeth(inherit **ilsth, char *metnm, char *parat, char *iclas) {
    inherit *ilistmp = *ilsth;
    inherit *prev_node;
    if (!ilistmp) return NULL;
    //
    if (strcmp(metnm, ilistmp->method) || strcmp(parat, ilistmp->parat) || strcmp(iclas, ilistmp->iclas)) {
        prev_node = ilistmp;
        ilistmp = ilistmp->next;
        while (ilistmp) {
            if (!strcmp(metnm, ilistmp->method) && !strcmp(parat, ilistmp->parat) && !strcmp(iclas, ilistmp->iclas)) {
                prev_node->next = ilistmp->next;
                break;
            }
            prev_node = ilistmp;
            ilistmp = ilistmp->next;
        }
    } else *ilsth = ilistmp->next;
    //
    return ilistmp;
}