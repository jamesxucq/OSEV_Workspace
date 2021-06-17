#ifndef AUTHEN_BZL_H
#define AUTHEN_BZL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"
#include "priv_utili.h"
#include "privi_obje.h"

    //
    int authbzl_create(int max_connecting);
    int authbzl_destroy();

    //
    //    int creat_autho_bzl();

    /* auth_db operator section */
    list_data *osev_ldata_bzl(char *action_key, char *user_name);
    list_data *osvn_ldata_bzl(char *action_key);
    list_data *osdb_ldata_bzl(char *action_key, char *user_name, osv_oid_t *osdb_oid, char *osdb);
    list_data *odbn_ldata_bzl(char *action_key, osv_oid_t *osdb_oid, char *osdb);

    void auth_epoll_exception(char *action_key);
    int erase_auth_cache_end(char *action_key);

    //
#define LIST_ROLE   0x01
#define LIST_USER   0x02
    int olist_role_bzl(prod_data *sresp, char *role_name);
    int olist_user_bzl(prod_data *sresp, char *ouse_name);
    int dlist_role_bzl(prod_data *sresp, char *role_name);
    int dlist_user_bzl(prod_data *sresp, char *cuse_name);

    //
#define ADDI_ROLE   0x01
#define DELE_ROLE   0x02
#define GRANT_PRIV   0x03
#define REVOKE_PRIV   0x04
    // osev role
    int oadd_role_bzl(prod_data *sresp, char *role_name);
    int odel_role_bzl(prod_data *sresp, char *role_name);
    int ogran_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask);
    int orevk_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask);
    // data role
    int dadd_role_bzl(prod_data *sresp, char *role_name);
    int ddel_role_bzl(prod_data *sresp, char *role_name);
    int dgran_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask);
    int drevk_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask);

    //
    int reloa_privi_bzl(prod_data *sresp);

    //
#define ADDI_USER   0x01
#define DELE_USER   0x02
#define GRANT_ROLE   0x03
#define REVOKE_ROLE   0x04
    // osev user
    int oadd_user_bzl(prod_data *sresp, char *ouse_name, char *salt_paswd);
    int odel_user_bzl(prod_data *sresp, char *ouse_name);
    int ogran_role_bzl(prod_data *sresp, char *ouse_name, char *role_name);
    int orevk_role_bzl(prod_data *sresp, char *ouse_name, char *role_name);
    // data user
    int dadd_user_bzl(prod_data *sresp, char *cuse_name, char *salt_paswd);
    int ddel_user_bzl(prod_data *sresp, char *cuse_name);
    int dgran_role_bzl(prod_data *sresp, char *cuse_name, char *role_name);
    int drevk_role_bzl(prod_data *sresp, char *cuse_name, char *role_name);

    //
    int check_reque_bzl(char *valid, char *req_valid, char *req_salt);
    uint32 reset_privalu_bzl(osv_oid_t *oid, char *osdb);
    uint32 reset_privile_bzl(osv_oid_t *oid, uint32 leve_mask);

    //
#define live_load_bzl(liv_data, coval, contn, oid) live_load(liv_data, coval, contn, oid)



#ifdef __cplusplus
}
#endif

#endif /* AUTHEN_BZL_H */

