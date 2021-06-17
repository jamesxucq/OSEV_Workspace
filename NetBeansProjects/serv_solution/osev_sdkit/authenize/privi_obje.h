
/* 
 * File:   privi_obje.h
 * Author: James Xu
 *
 * Created on 2017.12.13, AM 9:18
 */

#ifndef PRIVI_OBJE_H
#define PRIVI_OBJE_H

#include "commo_header.h"
#include "liv_list.h"
// #include "shape/shape.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern int _hashmap_size_;

    //
    struct priv_list _priv_list_;

    //
    int initi_privi_data(struct priv_list *alist, conoda *coval);
    int final_privi_data(struct priv_list *alist);

    //
    role_privi *oadd_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name);
    int odel_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name);
    int ogran_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask);
    int orevk_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask);

    //
    role_privi *dadd_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name);
    int ddel_role_data(conoda *coval, struct liv_list **role_lsth, char *role_name);
    int dgran_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask);
    int drevk_priv_data(conoda *coval, role_privi *role_poin, dist_privi *priv_dist, uint32 leve_mask);

    //
    user_privi *addi_ouser_data(conoda *coval, struct liv_list **ouse_lsth, char *ouse_name, char *salt_paswd);
    int dele_ouser_data(conoda *coval, struct liv_list **ouse_lsth, user_privi *user_poin);
    int ogran_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin);
    int orevk_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin);
    //
    user_privi *addi_cuser_data(conoda *coval, struct liv_list **cuse_lsth, char *cuse_name, char *salt_paswd);
    int dele_cuser_data(conoda *coval, struct liv_list **cuse_lsth, user_privi *user_poin);
    int dgran_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin);
    int drevk_role_data(conoda *coval, user_privi *user_poin, role_privi *role_poin);

    //


#ifdef __cplusplus
}
#endif

#endif /* PRIVI_OBJE_H */

