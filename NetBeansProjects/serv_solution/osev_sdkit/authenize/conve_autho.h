
/* 
 * File:   conve_autho.h
 * Author: Administrator
 *
 * Created on 2018.3.19, PM 2:18
 */

#ifndef CONVE_AUTHO_H
#define CONVE_AUTHO_H

#include "commo_header.h"
#include "privi_obje.h"

#ifdef __cplusplus
extern "C" {
#endif

// 
int oconv_role_name(prod_data *sresp, conoda *coval, role_privi *role_poin);
int dconv_role_name(prod_data *sresp, conoda *coval, role_privi *role_poin);
int oconv_role_all(prod_data *sresp, conoda *coval, struct liv_list *role_list);
int dconv_role_all(prod_data *sresp, conoda *coval, struct liv_list *role_list);

//
void conve_user_name(prod_data *sresp, user_privi *user_poin);
void conve_user_all(prod_data *sresp, struct liv_list *ouse_list);
// void conve_authen_stat(prod_data *sresp, unsigned int auth_valu);


#ifdef __cplusplus
}
#endif

#endif /* CONVE_AUTHO_H */

