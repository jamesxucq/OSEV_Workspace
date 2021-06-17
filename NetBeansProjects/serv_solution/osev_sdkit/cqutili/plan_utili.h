
#ifndef PLAN_UTILI_H
#define PLAN_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif
    //
#include <stdlib.h>

#include "quer_plan.h"
    
    //
    plan_node *appe_noeq_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);
    plan_node *appe_equa_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);
    plan_node *appe_grth_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);
    plan_node *appe_leeq_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);
    plan_node *appe_leth_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);
    plan_node *appe_greq_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);
    plan_node *appe_plus_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);
    plan_node *appe_minu_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta);

    //
    plan_node *appe_or_node(plan_node *quer_plan, plan_node *left_chil, plan_node *rich_chil);
    plan_node *appe_and_node(plan_node *quer_plan, plan_node *left_chil, plan_node *rich_chil);
    plan_node *appe_not_node(plan_node *quer_plan, plan_node *left_chil);

#ifdef __cplusplus
}
#endif

#endif /* PLAN_UTILI_H */
