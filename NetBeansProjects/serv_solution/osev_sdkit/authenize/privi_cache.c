#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "privi_cache.h"
// #include "shape/sha_stru.h"
#include "privi_obje.h"

//
#define ROLE_BACKET_SIZE    512

//
actionmap *_ldata_hm_;
cachemap *_ouser_hm_;
cachemap *_cuser_hm_;
//

list_data* new_ldata() {
    list_data *ldata = (list_data *) malloc(sizeof (list_data));
    if (!ldata) return NULL;
    memset(ldata, '\0', sizeof (list_data));
    //
    return ldata;
}

void free_ldata(void* ldata) {
    if (ldata) free(ldata);
}


//

static int build_orole_cache(cachemap *role_hm, struct liv_list *rlist) {
    role_privi *role_poin;
    //
    for (; rlist; rlist = rlist->next) {
        role_poin = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_OSEV == role_poin->role_type)
            cache_insert(&role_poin->oid, role_poin, role_hm);
    }
    //
    return 0x00;
}

static int build_crole_cache(cachemap *role_hm, struct liv_list *rlist) {
    role_privi *role_poin;
    //
    for (; rlist; rlist = rlist->next) {
        role_poin = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_OSDB == role_poin->role_type)
            cache_insert(&role_poin->oid, role_poin, role_hm);
    }
    //
    return 0x00;
}

//

static int build_user_cache(cachemap *user_hm, struct liv_list *ulist) {
    user_privi *user_poin;
    //
    for (; ulist; ulist = ulist->next) {
        user_poin = (user_privi *) ulist->liv_data;
        cache_insert(user_poin->user_name, user_poin, user_hm);
    }
    //
    return 0x00;
}

static int user_oid_poin(struct liv_list *ulist, cachemap *role_hm) {
// printf("user_oid_poin\n");
    user_privi *user_poin;
    //
    int inde, poin;
    for (; ulist; ulist = ulist->next) {
        user_poin = (user_privi *) ulist->liv_data;
        osv_oid_t *role_oid = user_poin->role_oid;
        for (inde = 0x0, poin = 0x00; (MAX_ROLE_SIZE > inde) && !IS_ZERO_OID(role_oid[0x00]); inde++, role_oid++) {
// char oid_stri[OID_LINE_LEN];
// printf("oid_stri:|%s|\n", oidstr(oid_stri, role_oid));
            if (!IS_INVA_OID(role_oid[0x00])) {
                mapid_unique(role_oid);
                user_poin->role_poin[poin++] = (role_privi *) cache_value((void *) &role_oid[0x00], role_hm);
            }
        }
        user_poin->role_poin[poin] = NULL;
    }
    //
    return 0x00;
}

int creat_ouser_cache(cachemap *ouser_hm, struct liv_list *role_list, struct liv_list *ouse_list) {
    cachemap *role_hm = creat_oid_hm(ROLE_BACKET_SIZE);
    if (!role_hm) return -1;
    if (build_orole_cache(role_hm, role_list)) {
        cache_dele(role_hm);
        return -1;
    }
    //
    if (user_oid_poin(ouse_list, role_hm)) {
        cache_dele(role_hm);
        return -1;
    }
    cache_dele(role_hm);
    if (build_user_cache(ouser_hm, ouse_list))
        return -1;
    //
    return 0x00;
}

int creat_cuser_cache(cachemap *cuser_hm, struct liv_list *role_list, struct liv_list *cuse_list) {
    cachemap *role_hm = creat_oid_hm(ROLE_BACKET_SIZE);
    if (!role_hm) return -1;
    if (build_crole_cache(role_hm, role_list)) {
        cache_dele(role_hm);
        return -1;
    }
    //
    if (user_oid_poin(cuse_list, role_hm)) {
        cache_dele(role_hm);
        return -1;
    }
    cache_dele(role_hm);
    if (build_user_cache(cuser_hm, cuse_list))
        return -1;
    //
    return 0x00;
}

//