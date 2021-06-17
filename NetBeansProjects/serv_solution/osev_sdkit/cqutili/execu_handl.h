
/* 
 * File:   execu_handl.h
 * Author: james
 *
 * Created on 2021.6.1, PM1:56
 */

#ifndef EXECU_HANDL_H
#define EXECU_HANDL_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "quer_plan.h"
#include "conte_resou.h"

    //
    int hand_resul_set(plan_node *quer_plan, physi_conte *phy_con, rive_ha *stora_ha);
    int hand_opera_set(plan_node *quer_plan);
    //
    int hand_final_find(prod_data *sresp, plan_node *quep);
    int hand_final_drop(rive_conne *rvcon, rive_ha *stora_ha, char *cont_name, plan_node *quep);
    int hand_final_each(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_meth *dlmep, plan_node *quep);


#ifdef __cplusplus
}
#endif

#endif /* EXECU_HANDL_H */

