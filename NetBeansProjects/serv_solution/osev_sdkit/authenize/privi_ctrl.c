#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "astri_utili.h"
#include "osev_struct.h"
#include "privile_bzl.h"
#include "privi_cache.h"
#include "privi_ctrl.h"
#include "privi_obje.h"
#include "conoda_bzl.h"

// for debug

/*
static char *echo_role_privi(char *last_str, role_privi *role_poin) {
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
*/

/*
static char *echo_dist_privi(char *last_str, dist_privi *priv_poin) {
    char oid_stri[OID_LINE_LEN];
    last_str = lscpy(last_str, "    |");
    last_str = lscpy(last_str, oidstr(oid_stri, &priv_poin->oid));
    last_str = lccpy(last_str, '|');
    last_str = lsprif(last_str, "%08X", priv_poin->privile_mask);
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}
*/

//

static void comple_role_list(struct liv_list *role_list) {
    // char strTemp[1024];
    //char *last_str = lscpy(strTemp, "comple_role_list\n");
    int inde;
    struct liv_list * rlist = role_list;
    for (; rlist; rlist = rlist->next) {
// last_str = echo_role_privi(last_str, (role_privi *) rlist->liv_data);
        dist_privi *priv_poin = ((role_privi *) rlist->liv_data)->priv_array;
        for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++) {
// last_str = echo_dist_privi(last_str, priv_poin);
            if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi)))
                mapid_unique(&priv_poin->oid);
// last_str = echo_dist_privi(last_str, priv_poin);
        }
    }
// printf("%s\n", strTemp);
}

//

int load_privi_data(cachemap *ouser_hm, cachemap *cuser_hm, struct priv_list *alist, conoda *coval) {
    if (initi_privi_data(alist, coval))
        return -1;
    if (creat_ouser_cache(ouser_hm, alist->role_list, alist->ouse_list))
        return -1;
    if (creat_cuser_cache(cuser_hm, alist->role_list, alist->cuse_list))
        return -1;
    comple_role_list(alist->role_list);
    //
    return 0x00;
}

int dele_privi_data(cachemap *ouser_hm, cachemap *cuser_hm, struct priv_list *alist) {
    if (_cuser_hm_) cache_clear(cuser_hm);
    if (_ouser_hm_) cache_clear(ouser_hm);
    //
    if (final_privi_data(alist)) return -1;
    return 0x00;
}

// 0x01:exists 0x00:not exists

role_privi *find_osev_role(struct liv_list *role_list, char *role_name) {
    role_privi *role_poin;
    struct liv_list *rlist = role_list;
    for (; rlist; rlist = rlist->next) {
        role_poin = (role_privi *) rlist->liv_data;
        if ((ROLE_TYPE_OSEV == role_poin->role_type) && !strcmp(role_name, role_poin->role_name))
            return role_poin;
    }
    //
    return NULL;
}

int osev_role_used(struct liv_list *ouse_list, char *role_name) {
    //
    return 0x00;
}

//

role_privi *find_osdb_role(struct liv_list *role_list, char *role_name) {
    struct liv_list *rlist = role_list;
    for (; rlist; rlist = rlist->next) {
        if (!strcmp(role_name, ((role_privi *) rlist->liv_data)->role_name))
            return (role_privi *) rlist->liv_data;
    }
    //
    return NULL;
}

int osdb_role_used(struct liv_list *cuse_list, char *role_name) {

    //
    return 0x00;
}


//

user_privi *find_user_privi(struct liv_list *user_list, char *user_name) {
    struct liv_list *ulist = user_list;
    for (; ulist; ulist = ulist->next) {
        if (!strcmp(user_name, ((user_privi *) ulist->liv_data)->user_name))
            return (user_privi *) ulist->liv_data;
    }
    //
    return NULL;
}

//

int build_auth_valid(char *valid, user_privi *user_poin) {
    unsigned char ecb_key[KEY_LENGTH];
    build_authen_key(ecb_key, user_poin->salt);
    //
    unsigned char password[PASWD_LENGTH];
    crypto_decode_ecb(password, (unsigned char *) user_poin->password, ecb_key);
    sprintf(valid, "%s:%s", user_poin->user_name, password);
    //
    return 0x00;
}

//

int check_privi_oid(role_privi *role_poin, osv_oid_t *oid) {
    int inde;
    dist_privi *priv_poin = role_poin->priv_array;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++) {
        if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi)) && oidcmp(oid, &priv_poin->oid))
            return 0x01;
    }
    //
    return 0x00;
}

int reset_privile_mask(role_privi *role_poin, osv_oid_t *oid, uint32 leve_mask) {
    uint32 leval = INVA_PRIV;
    //
    int inde;
    dist_privi *priv_poin = role_poin->priv_array;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++) {
        mapid_unique(&priv_poin->oid);
        if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi)) && oidcmp(oid, &priv_poin->oid)) {
            if (SCOP_OSDB & priv_poin->privile_mask) {
                leval = priv_poin->privile_mask & leve_mask;
                priv_poin->privile_mask = CLEAR_SLEVE(priv_poin->privile_mask);
                priv_poin->privile_mask |= leval;
            } else if (SCOP_EOBJ & priv_poin->privile_mask) {
                if (!(LEVE_FOUP & priv_poin->privile_mask))
                    priv_poin->privile_mask = CLEAR_COEN(priv_poin->privile_mask);
            }
        }
    }
    //
    return 0x00;
}

//

int opriv_dist_leoid(osv_oid_t *oid, uint32 *leve_mask, char *dist_name, uint32 priv_mask) {
    if (SCOP_OSDB & priv_mask) {
        conoda *coval = find_conto_bzl(dist_name);
        if (!coval) return -1;
        memcpy(oid, &coval->oid, sizeof (osv_oid_t));
        leve_mask[0x00] = coval->leve_mask;
    } else if (SCOP_OSEV & priv_mask) {
        creat_objeid_osev(oid);
        leve_mask[0x00] = OSDB_LEVE_OTTF;
    }
    //
    return 0x00;
}

//

int dpriv_dist_leoid(osv_oid_t *oid, uint32 *leve_mask, char *dist_name, uint32 priv_mask) {
    char osdb[OSDB_LENGTH];
    char conta[OBJE_LENGTH];
    //
    if (SCOP_OSDB & priv_mask) {
        conoda *coval = find_conto_bzl(dist_name);
        if (!coval) return -1;
        memcpy(oid, &coval->oid, sizeof (osv_oid_t));
        leve_mask[0x00] = coval->leve_mask;
    } else if (SCOP_EOBJ & priv_mask) {
        if (split_conta(osdb, conta, dist_name)) return -1;
        conoda *coval = find_conto_bzl(osdb);
        if (!coval) return -1;
        leve_mask[0x00] = coval->leve_mask;
        contain *contp = (contain *) action_value(conta, coval->conda.contn_hm);
        if (!contp) return -1;
        memcpy(oid, &contp->oid, sizeof (osv_oid_t));
    }
    //
    return 0x00;
}