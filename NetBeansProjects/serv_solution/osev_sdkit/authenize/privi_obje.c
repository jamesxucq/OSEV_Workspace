
//
#include "privile_obje.h"
#include "privi_obje.h"
#include "priv_utili.h"
#include "osev_struct.h"
#include "liv_list.h"

//
dist_privi INVA_PRIV_VALU = {
    {INVA_UINT_VALU, INVA_UINT_VALU, INVA_UINT_VALU},
    INVA_UINT_VALU
};

dist_privi ZERO_PRIV_VALU = {
    {0x00, 0x00, 0x00},
    0x00
};

//
int _hashmap_size_;

//
struct priv_list _priv_list_;

// for test

static char *p_role_privi(char *last_str, role_privi *role_poin) {
    char oid_stri[OID_LINE_LEN];
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, oidstr(oid_stri, &role_poin->oid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, role_poin->role_name);
    last_str = lccpy(last_str, '|');
    if (ROLE_TYPE_OSEV == role_poin->role_type)
        last_str = lscpy(last_str, "OSEV");
    else if (ROLE_TYPE_OSDB == role_poin->role_type)
        last_str = lscpy(last_str, "ODB");
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

static void print_role_privi(struct liv_list *role_list) {
    char temp[512];
    struct liv_list * rlist = role_list;
    printf("role_privi -------------\n");
    for (; rlist; rlist = rlist->next) {
        p_role_privi(temp, (role_privi *) rlist->liv_data);
        printf(temp);
    }
}

static char *p_user_privi(char *last_str, user_privi *user_poin) {
    char oid_stri[OID_LINE_LEN];
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, oidstr(oid_stri, &user_poin->oid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, user_poin->user_name);
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

static void print_user_privi(struct liv_list *user_list) {
    char temp[512];
    struct liv_list * ulist = user_list;
    printf("user_privi -------------\n");
    for (; ulist; ulist = ulist->next) {
        p_user_privi(temp, (user_privi *) ulist->liv_data);
        printf(temp);
    }
}

//

int initi_privi_data(struct priv_list *alist, conoda *coval) {
    printf("size role_privi:%lu\n", sizeof (role_privi));
    if (live_recu_load(&alist->role_list, coval, AUTH_ROLES_CONT)) {
        _LOG_WARN("recurs roles exception.");
        return -1;
    }
    print_role_privi(alist->role_list);
    //
    printf("size user_privi:%lu\n", sizeof (user_privi));
    if (live_recu_load(&alist->ouse_list, coval, AUTH_OUSER_CONT)) {
        _LOG_WARN("recurs ouser exception.");
        return -1;
    }
    print_user_privi(alist->ouse_list);
    //
    if (live_recu_load(&alist->cuse_list, coval, AUTH_CUSER_CONT)) {
        _LOG_WARN("recurs cuser exception.");
        return -1;
    }
    print_user_privi(alist->cuse_list);
    //
    return 0x00;
}

//

int final_privi_data(struct priv_list *alist) {
    DELE_LIVE_LIST(alist->cuse_list)
    DELE_LIVE_LIST(alist->ouse_list)
    DELE_LIVE_LIST(alist->role_list)
            //
    return 0x00;
}

//

user_privi *addi_ouser_data(conoda *coval, struct liv_list **ouse_lsth, char *ouse_name, char *salt_paswd) {
    struct liv_list *ulist = addi_live_list(ouse_lsth, sizeof (user_privi));
    if (!ulist) return NULL;
    user_privi *user_poin = (user_privi *) ulist->liv_data;
    //
    strcpy(user_poin->user_name, ouse_name);
    creat_objeid_obj(&user_poin->oid);
    printf("salt_paswd:%s\n", salt_paswd);
    decode_salt_paswd(user_poin->salt, user_poin->password, salt_paswd);
    memset(user_poin->role_oid, '\0', MAX_ROLE_SIZE * sizeof (osv_oid_t));
    //
    if (live_insert(coval, AUTH_OUSER_CONT, user_poin)) {
        dele_livlst(ouse_lsth, ulist);
        return NULL;
    }
    return user_poin;
}

//

int dele_ouser_data(conoda *coval, struct liv_list **ouse_lsth, user_privi *user_poin) {
    if (live_remove(coval, AUTH_OUSER_CONT, &user_poin->oid)) return -1;
    dele_livdat(ouse_lsth, (void *) user_poin);
    return 0x00;
}

//

static int inse_role_cache(user_privi *user_poin, role_privi *role_poin) {
    role_privi **user_role = user_poin->role_poin;
    int inde;
    for (inde = 0x00; (MAX_ROLE_SIZE > inde) && user_role[0x00] && INVA_POIN_VALU != user_role[0x00]; inde++, user_role++);
    if (MAX_ROLE_SIZE == inde) return -1;
    user_role[0x00] = role_poin;
    //
    return 0x00;
}

static int inse_role_data(conoda *coval, char *contn, osv_oid_t *oid, role_privi *role_poin) {
    user_privi user_dat;
    if (live_load((char *) &user_dat, coval, contn, oid)) return -1;
    //
    osv_oid_t *role_oid = user_dat.role_oid;
    int inde;
    for (inde = 0x00; (MAX_ROLE_SIZE > inde) && !IS_ZERO_OID(role_oid[0x00]) && !IS_INVA_OID(role_oid[0x00]); inde++, role_oid++);
    if (MAX_ROLE_SIZE == inde) return -1;
    // memcpy(role_oid, &role_poin->oid, sizeof (osv_oid_t));
    mapid_invalid(role_oid);
    ((osv_oid_i *) role_oid)->stoid = ((osv_oid_i *) & role_poin->oid)->stoid;
    //
    if (live_save(coval, contn, (char *) &user_dat, oid)) return -1;
    return 0x00;
}

int ogran_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin) {
    if (inse_role_data(coval, AUTH_OUSER_CONT, &user_poin->oid, role_poin)) return -1;
    if (inse_role_cache(user_poin, role_poin)) return -1;
    return 0x00;
}

//

static int dele_role_cache(user_privi *user_poin, role_privi *role_poin) {
    role_privi **user_role = user_poin->role_poin;
    int inde;
    for (inde = 0x00; (MAX_ROLE_SIZE > inde) && user_role[0x00]; inde++, user_role++) {
        if (role_poin == user_role[0x00]) {
            user_role[0x00] = INVA_POIN_VALU;
            break;
        }
    }
    //
    return 0x00;
}

static int dele_role_data(conoda *coval, char *contn, osv_oid_t *oid, role_privi *role_poin) {
    user_privi user_dat;
    if (live_load((char *) &user_dat, coval, contn, oid)) return -1;
    //
    osv_oid_t *role_oid = user_dat.role_oid;
    int inde;
    for (inde = 0x00; (MAX_ROLE_SIZE > inde) && !IS_ZERO_OID(role_oid[0x00]); inde++, role_oid++) {
        if (sidcmp(&role_poin->oid, role_oid)) {
            memcpy(role_oid, &INVA_OID_VALU, sizeof (osv_oid_t));
            break;
        }
    }
    //
    if (live_save(coval, contn, (char *) &user_dat, oid)) return -1;
    return 0x00;
}

int orevk_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin) {
    if (dele_role_data(coval, AUTH_OUSER_CONT, &user_poin->oid, role_poin)) return -1;
    if (dele_role_cache(user_poin, role_poin)) return -1;
    return 0x00;
}

//

user_privi *addi_cuser_data(conoda *coval, struct liv_list **cuse_lsth, char *cuse_name, char *salt_paswd) {
    struct liv_list *ulist = addi_live_list(cuse_lsth, sizeof (user_privi));
    if (!ulist) return NULL;
    user_privi *user_poin = (user_privi *) ulist->liv_data;
    //
    strcpy(user_poin->user_name, cuse_name);
    creat_objeid_obj(&user_poin->oid);
    printf("salt_paswd:%s\n", salt_paswd);
    decode_salt_paswd(user_poin->salt, user_poin->password, salt_paswd);
    memset(user_poin->role_oid, '\0', MAX_ROLE_SIZE * sizeof (osv_oid_t));
    //
    if (live_insert(coval, AUTH_CUSER_CONT, user_poin)) {
        dele_livlst(cuse_lsth, ulist);
        return NULL;
    }
    return user_poin;
}

//

int dele_cuser_data(conoda *coval, struct liv_list **cuse_lsth, user_privi *user_poin) {
    if (live_remove(coval, AUTH_CUSER_CONT, &user_poin->oid)) return -1;
    dele_livdat(cuse_lsth, (void *) user_poin);
    return 0x00;
}

int dgran_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin) {
    if (inse_role_data(coval, AUTH_CUSER_CONT, &user_poin->oid, role_poin)) return -1;
    if (inse_role_cache(user_poin, role_poin)) return -1;
    //
    return 0x00;
}

int drevk_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin) {
    if (dele_role_data(coval, AUTH_CUSER_CONT, &user_poin->oid, role_poin)) return -1;
    if (dele_role_cache(user_poin, role_poin)) return -1;
    return 0x00;
}

//

role_privi *oadd_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name) {
    struct liv_list *rlist = addi_live_list(role_lsth, sizeof (role_privi));
    if (!rlist) return NULL;
    role_privi *role_poin = (role_privi *) rlist->liv_data;
    //
    role_poin->role_type = ROLE_TYPE_OSEV;
    strcpy(role_poin->role_name, role_name);
    creat_objeid_obj(&role_poin->oid);
    memset(role_poin->priv_array, '\0', MAX_PRIVI_SIZE * sizeof (dist_privi));
    //
    if (live_insert(coval, AUTH_ROLES_CONT, role_poin)) {
        dele_livlst(role_lsth, rlist);
        return NULL;
    }
    // for debug
    char temp[512];
    p_role_privi(temp, role_poin);
    printf("role_privi --------------------------------\n");
    printf(temp);
    return role_poin;
}

int odel_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name) {
    role_privi *role_poin;
    struct liv_list *rlist = role_lsth[0x00];
    for (; rlist; rlist = rlist->next) {
        role_poin = (role_privi *) rlist->liv_data;
        if (!strcmp(role_name, role_poin->role_name))
            break;
    }
    if (!rlist) return -1;
    //
    if (live_remove(coval, AUTH_ROLES_CONT, &role_poin->oid)) return -1;
    dele_livlst(role_lsth, rlist);
    //
    return 0x00;
}

//

static int inse_priv_cache(role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask) {
    dist_privi *priv_poin = role_poin->priv_array;
    int inde;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi))
            && memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++);
    if (MAX_PRIVI_SIZE == inde) return -1;
    //
    uint32 leval = priv_poin->privile_mask & leve_mask;
    priv_poin->privile_mask = CLEAR_SLEVE(priv_poin->privile_mask);
    priv_poin->privile_mask |= leval;
    memcpy(priv_poin, priv_dist, sizeof (dist_privi));
    //
    return 0x00;
}

static int inse_priv_data(conoda *coval, char *contn, osv_oid_t *oid, dist_privi *priv_dist) {
    role_privi role_dat;
    if (live_load((char *) &role_dat, coval, contn, oid)) return -1;
    //
    dist_privi *priv_poin = role_dat.priv_array;
    int inde;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi))
            && memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++);
    if (MAX_PRIVI_SIZE == inde) return -1;
    //
    mapid_invalid(&priv_poin->oid);
    ((osv_oid_i *) & priv_poin->oid)->stoid = ((osv_oid_i *) & priv_dist->oid)->stoid;
    priv_poin->privile_mask = priv_dist->privile_mask;
    //
    if (live_save(coval, contn, (char *) &role_dat, oid)) return -1;
    return 0x00;
}

int ogran_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask) {
    if (inse_priv_data(coval, AUTH_ROLES_CONT, &role_poin->oid, priv_dist)) return -1;
    if (inse_priv_cache(role_poin, priv_dist, leve_mask)) return -1;
    return 0x00;
}

//

static int dele_priv_cache(role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask) {
    uint32 leval = priv_dist->privile_mask & leve_mask;
    priv_dist->privile_mask = CLEAR_SLEVE(priv_dist->privile_mask);
    priv_dist->privile_mask |= leval;
    //
    dist_privi *priv_poin = role_poin->priv_array;
    int inde;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++) {
        if (!memcmp(priv_dist, priv_poin, sizeof (dist_privi))) {
            memcpy(priv_poin, &INVA_PRIV_VALU, sizeof (dist_privi));
        }
    }
    //
    return 0x00;
}

static int dele_priv_data(conoda *coval, char *contn, osv_oid_t *oid, dist_privi *priv_dist) {
    role_privi role_dat;
    if (live_load((char *) &role_dat, coval, contn, oid)) return -1;
    //
    dist_privi *priv_poin = role_dat.priv_array;
    int inde;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++) {
        //
        if (sidcmp(&priv_dist->oid, &priv_poin->oid) && (priv_dist->privile_mask == priv_poin->privile_mask)) {
            memcpy(priv_poin, &INVA_PRIV_VALU, sizeof (dist_privi));
            break;
        }
    }
    //
    if (live_save(coval, contn, (char *) &role_dat, oid)) return -1;
    return 0x00;
}

int orevk_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask) {
    if (dele_priv_data(coval, AUTH_ROLES_CONT, &role_poin->oid, priv_dist)) return -1;
    if (dele_priv_cache(role_poin, priv_dist, leve_mask)) return -1;
    return 0x00;
}

//

role_privi *dadd_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name) {
    struct liv_list *rlist = addi_live_list(role_lsth, sizeof (role_privi));
    if (!rlist) return NULL;
    role_privi *role_poin = rlist->liv_data;
    //
    role_poin->role_type = ROLE_TYPE_OSDB;
    strcpy(role_poin->role_name, role_name);
    creat_objeid_obj(&role_poin->oid);
    memset(role_poin->priv_array, '\0', MAX_PRIVI_SIZE * sizeof (dist_privi));
    //
    if (live_insert(coval, AUTH_ROLES_CONT, role_poin)) {
        dele_livlst(role_lsth, rlist);
        return NULL;
    }
    return role_poin;
}

int ddel_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name) {
    role_privi *role_poin;
    struct liv_list *rlist = role_lsth[0x00];
    for (; rlist; rlist = rlist->next) {
        role_poin = (role_privi *) rlist->liv_data;
        if (!strcmp(role_name, role_poin->role_name))
            break;
    }
    if (!rlist) return -1;
    //     
    if (live_remove(coval, AUTH_ROLES_CONT, &role_poin->oid)) return -1;
    dele_livlst(role_lsth, rlist);
    //
    return 0x00;
}

int dgran_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask) {
    if (inse_priv_data(coval, AUTH_ROLES_CONT, &role_poin->oid, priv_dist)) return -1;
    if (inse_priv_cache(role_poin, priv_dist, leve_mask)) return -1;
    return 0x00;
}

int drevk_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask) {
    if (dele_priv_data(coval, AUTH_ROLES_CONT, &role_poin->oid, priv_dist)) return -1;
    if (dele_priv_cache(role_poin, priv_dist, leve_mask)) return -1;
    return 0x00;
}


//


