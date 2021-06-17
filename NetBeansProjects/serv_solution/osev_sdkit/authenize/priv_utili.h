
/* 
 * File:   priv_utili.h
 * Author: Administrator
 *
 * Created on 2018.4.3, PM 5:05
 */

#ifndef PRIV_UTILI_H
#define PRIV_UTILI_H

#include "liv_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct priv_cont {
        char *cont_name; // contain name
        char *clas_type;
    };

    //
#define DEFA_ROLE_CLAS  "role"
#define DEFA_USER_CLAS  "user"
    //
#define AUTH_ROLES_CONT  "roles_con"
#define AUTH_OUSER_CONT  "ouser_con"
#define AUTH_CUSER_CONT  "cuser_con"

    //

    extern struct priv_cont _priv_data_[];
    int check_priv_data(cont_data *conda, struct priv_cont *priv_data);
    int destro_priv_data(char *roles_conta, char *ouser_conta, char *cuser_conta);
    int creat_priv_data(conoda *coval, struct priv_cont *priv_data);

    //
    int live_recu_load(struct liv_list **llsth, conoda *coval, char *contn);
    int live_insert(conoda *coval, char *contn, void *data);
    int live_load(void *data, conoda *coval, char *contn, osv_oid_t *oid);
    int live_save(conoda *coval, char *contn, void *data, osv_oid_t *oid);
    int live_remove(conoda *coval, char *contn, osv_oid_t *oid);


#ifdef __cplusplus
}
#endif

#endif /* PRIV_UTILI_H */

