
/* 
 * File:   privi_ctrl.h
 * Author: James Xu
 *
 * Created on 2016.12.27, AM 9:59
 */

#ifndef PRIVI_CTRL_H
#define PRIVI_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int load_privi_data(cachemap *ouser_hm, cachemap *cuser_hm, struct priv_list *alist, conoda *coval);
    int dele_privi_data(cachemap *ouser_hm, cachemap *cuser_hm, struct priv_list *alist);

    //
    role_privi *find_osev_role(struct liv_list *role_list, char *role_name);
    int osev_role_used(struct liv_list *ouse_list, char *role_name);
    role_privi *find_osdb_role(struct liv_list *role_list, char *role_name);
    int osdb_role_used(struct liv_list *cuse_list, char *role_name);

    //
    user_privi *find_user_privi(struct liv_list *user_list, char *user_name);

    //
    int build_auth_valid(char *valid, user_privi *user_poin);

    //
    int check_privi_oid(role_privi *role_poin, osv_oid_t *oid);
    int reset_privile_mask(role_privi *role_poin, osv_oid_t *oid, uint32 leval);

    //
    int opriv_dist_leoid(osv_oid_t *oid, uint32 *leve_mask, char *dist_name, uint32 priv_mask);
    int dpriv_dist_leoid(osv_oid_t *oid, uint32 *leve_mask, char *dist_name, uint32 priv_mask);

#ifdef __cplusplus
}
#endif

#endif /* PRIVI_CTRL_H */

