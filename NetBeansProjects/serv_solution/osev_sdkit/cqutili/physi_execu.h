
/* 
 * File:   physi_execu.h
 * Author: James
 *
 * Created on 2019.3.26, 8:57
 */

#ifndef PHYSI_EXECU_H
#define PHYSI_EXECU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"
#include "quer_plan.h"

    //
    int execu_physi_find(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, plan_node *quer_plan);
    
    //
    int execu_physi_drop(rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, plan_node *quer_plan);
    
    //
    int execu_physi_each(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_meth *dlmep, plan_node *quer_plan);


#ifdef __cplusplus
}
#endif

#endif /* PHYSI_EXECU_H */

