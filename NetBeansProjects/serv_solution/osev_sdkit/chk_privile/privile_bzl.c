#include "commo_header.h"

#include "privi_utili.h"
#include "privile_obje.h"
#include "privile_bzl.h"

//

/*
int privbzl_create(char *data_directory) {
    strcpy(_privi_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int privbzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

//

int osev_privile_bzl(user_privi *user_poin, uint32 priv_mask) {
    if (!user_poin) return -1;
    dist_privi *priv_poin;
    role_privi **role_poin = user_poin->role_poin;
    //
    int role_inde, priv_inde;
    for (role_inde = 0x00; (MAX_ROLE_SIZE > role_inde) && role_poin[0x00] && INVA_POIN_VALU != role_poin[0x00]; role_inde++, role_poin++) {
        priv_poin = role_poin[0x00]->priv_array;
        for (priv_inde = 0x00; (MAX_PRIVI_SIZE > priv_inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); priv_inde++, priv_poin++) {
            if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi))) {
                if (PRIVI_SCOPE(priv_mask & priv_poin->privile_mask) && PRIVI_VALUE(priv_mask & priv_poin->privile_mask))
                    return 0x00;
            }
        }
    }
    //
    return -1;
}

//

int levin_privile_bzl(user_privi *user_poin, osv_oid_t *ole_oid, uint32 priv_mask) {
    if (!user_poin) return -1;
    dist_privi * priv_poin;
    role_privi **role_poin = user_poin->role_poin;
    //
    int role_inde, priv_inde;
    for (role_inde = 0x00; (MAX_ROLE_SIZE > role_inde) && role_poin[0x00] && INVA_POIN_VALU != role_poin[0x00]; role_inde++, role_poin++) {
        priv_poin = role_poin[0x00]->priv_array;
        for (priv_inde = 0x00; (MAX_PRIVI_SIZE > priv_inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); priv_inde++, priv_poin++) {
            if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi))) {
                if (sidcmp(ole_oid, &priv_poin->oid) && PRIVI_SCOPE(priv_mask & priv_poin->privile_mask) && PRIVI_VALUE(priv_mask & priv_poin->privile_mask))
                    return 0x00;
            }
        }
    }
    //
    return -1;
}

//

int levcq_privile_bzl(user_privi *user_poin, osv_oid_t *ole_oid, osv_oid_t *coq_oid, coqu_pvmk *priv_mask) {
    if (!user_poin) return -1;
    dist_privi * priv_poin;
    role_privi **role_poin = user_poin->role_poin;
    //
    int role_inde, priv_inde;
    for (role_inde = 0x00; (MAX_ROLE_SIZE > role_inde) && role_poin[0x00] && INVA_POIN_VALU != role_poin[0x00]; role_inde++, role_poin++) {
        priv_poin = role_poin[0x00]->priv_array;
        for (priv_inde = 0x00; (MAX_PRIVI_SIZE > priv_inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); priv_inde++, priv_poin++) {
            if (memcmp(&INVA_PRIV_VALU, priv_poin, sizeof (dist_privi))) {
                if (sidcmp(ole_oid, &priv_poin->oid) && PRIVI_SCOPE(priv_mask->ole_pmk & priv_poin->privile_mask) && PRIVI_VALUE(priv_mask->ole_pmk & priv_poin->privile_mask))
                    return 0x00;
                if (sidcmp(coq_oid, &priv_poin->oid) && PRIVI_SCOPE(priv_mask->coq_pmk & priv_poin->privile_mask) && PRIVI_VALUE(priv_mask->coq_pmk & priv_poin->privile_mask))
                    return 0x00;
            }
        } 
    }
    //
    return -1;
}

//

int osev_priv_bzl(char *contn, osv_oid_t *oid, dist_privi *priv_dist) {
    if (!((SCOP_OSEV | SCOP_OSDB) & priv_dist->privile_mask)) return -1;
    role_privi role_dat;
    conoda * coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) return -1;
    if (live_load_bzl((char *) &role_dat, coval, contn, oid)) return -1;
    //
    dist_privi * priv_poin = role_dat.priv_array;
    int inde;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++) {
        mapid_unique(&priv_poin->oid);
        if (!memcmp(priv_dist, priv_poin, sizeof (dist_privi)))
            return -1;
    }
    //
    return 0x00;
}

int osdb_priv_bzl(char *contn, osv_oid_t *oid, dist_privi *priv_dist) {
    if (!((SCOP_OSDB | SCOP_EOBJ) & priv_dist->privile_mask)) return -1;
    role_privi role_dat;
    conoda * coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) return -1;
    if (live_load_bzl((char *) &role_dat, coval, contn, oid)) return -1;
    //
    dist_privi * priv_poin = role_dat.priv_array;
    int inde;
    for (inde = 0x00; (MAX_PRIVI_SIZE > inde) && memcmp(&ZERO_PRIV_VALU, priv_poin, sizeof (dist_privi)); inde++, priv_poin++) {
        mapid_unique(&priv_poin->oid);
        if (!memcmp(priv_dist, priv_poin, sizeof (dist_privi)))
            return -1;
    }
    //
    return 0x00;
}

//

int osev_role_bzl(user_privi *user_poin, role_privi *role_poin) {
    if (ROLE_TYPE_OSEV != role_poin->role_type) return -1;
    //
    role_privi **user_role = user_poin->role_poin;
    int inde;
    for (inde = 0x00; (MAX_ROLE_SIZE > inde) && user_role[0x00]; inde++, user_role++) {
        if (role_poin == user_role[0x00])
            return -1;
    }
    //
    return 0x00;
}

int osdb_role_bzl(user_privi *user_poin, role_privi *role_poin) {
    if (ROLE_TYPE_OSDB != role_poin->role_type) return -1;
    //
    role_privi **user_role = user_poin->role_poin;
    int inde;
    for (inde = 0x00; (MAX_ROLE_SIZE > inde) && user_role[0x00]; inde++, user_role++) {
        if (role_poin == user_role[0x00])
            return -1;
    }
    //
    return 0x00;
}

// 
