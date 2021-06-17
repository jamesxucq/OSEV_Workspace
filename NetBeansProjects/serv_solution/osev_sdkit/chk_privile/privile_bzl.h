
/* 
 * File:   privile_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.30, PM 2:18
 */

#ifndef PRIVILE_BZL_H
#define PRIVILE_BZL_H

#include "privi_utili.h"
#include "authen_bzl.h"
#include "privile_obje.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    //    int privbzl_create(char *data_directory);
    //    int privbzl_destroy();

    //
#define OPRIV_STATU     (SCOP_OSEV | SVOD_ODBM)
#define DPRIV_STATU     (SCOP_OSEV | SVOD_ODBM)

#define OPRIV_PRIVI     (SCOP_OSEV | SVOD_PRIVI)
#define DPRIV_PRIVI     (SCOP_OSEV | SVOD_PRIVI)

#define MPRIV_INVOK(INVTYP)     minvo_privi[INVTYP]
#define CPRIV_INVOK(INVTYP)     cinvo_privi[INVTYP]

#define PRIVI_CONST(CONTYP)     const_privi[CONTYP]
#define PRIVI_QUERY(QUETYP)     query_privi[QUETYP]

    int osev_privile_bzl(user_privi *user_poin, uint32 priv_mask);
    int levin_privile_bzl(user_privi *user_poin, osv_oid_t *ole_oid, uint32 priv_mask);
    int levcq_privile_bzl(user_privi *user_poin, osv_oid_t *ole_oid, osv_oid_t *coq_oid, coqu_pvmk *priv_mask);

    //
    //    uint32 osev_privile_bzl(uint32 user_id);
    //    uint32 osdb_privile_bzl(osv_oid_t *osdb_oid, uint32 user_id);
    //
    int osev_priv_bzl(char *contn, osv_oid_t *oid, dist_privi *priv_dist);
    int osdb_priv_bzl(char *contn, osv_oid_t *oid, dist_privi *priv_dist);

    //
    int osev_role_bzl(user_privi *user_poin, role_privi *role_poin);
    int osdb_role_bzl(user_privi *user_poin, role_privi *role_poin);

    //

#ifdef __cplusplus
}
#endif

#endif /* PRIVILE_BZL_H */

