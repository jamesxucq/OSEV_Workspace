#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility/utlist.h"
#include "dyli_list.h"
#include "conoda.h"

//
struct cono_list *_conta_list_;

//

struct cono_list *appe_clist_new(struct cono_list **clsth) {
    struct cono_list *clistmp = (struct cono_list *) malloc(sizeof (struct cono_list));
    if (!clistmp) return NULL;
    memset(clistmp, '\0', sizeof (struct cono_list));
    //
    clistmp->_osdb_ = clistmp->cono_valu.osdb_name;
    clistmp->_oid_ = &clistmp->cono_valu.oid;
    LL_APPEND(*clsth, clistmp);
    return clistmp;
}

inline void clist_dele(struct cono_list *clist) {
    struct cono_list *clistmp;
    while (clist) {
        clistmp = clist;
        clist = clist->next;
        dyhand_dele(clistmp->cono_valu.hando.dyha_list);
        action_dele(clistmp->cono_valu.handa.ocuse_hm);
        action_dele(clistmp->cono_valu.hando.ocuse_hm);
        cache_dele(clistmp->cono_valu.conda.conto_hm);
        action_dele(clistmp->cono_valu.conda.contn_hm);
        free(clistmp);
    }
}

//

conoda *find_conto_osdb(struct cono_list *clist, char *osdb) {
    struct cono_list *clistmp;
    for (clistmp = clist; clistmp; clistmp = clistmp->next) {
        if (!strcmp(osdb, clistmp->_osdb_))
            return &clistmp->cono_valu;
    }
    //
    return NULL;
}

//

struct cono_list *find_clstn(struct cono_list *clist, char *osdb) {
    struct cono_list *clistmp;
    for (clistmp = clist; clistmp; clistmp = clistmp->next) {
        if (!strcmp(osdb, clistmp->_osdb_))
            return clistmp;
    }
    //
    return NULL;
}

struct cono_list *find_clsto(struct cono_list *clist, osv_oid_t *oid) {
    struct cono_list *clistmp;
    for (clistmp = clist; clistmp; clistmp = clistmp->next) {
        if (oidcmp(oid, clistmp->_oid_))
            return clistmp;
    }
    //
    return NULL;
}

//

void close_clist(struct cono_list **clsth, struct cono_list *clist) {

}
