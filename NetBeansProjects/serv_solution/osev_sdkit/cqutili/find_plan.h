
/* 
 * File:   find_plan.h
 * Author: james
 *
 * Created on 2021.6.1, AM9:11
 */

#ifndef FIND_PLAN_H
#define FIND_PLAN_H

#ifdef __cplusplus
extern "C" {
#endif

    int creat_find_plan_single(plan_node *quer_plan, char *quer_conta, oper_node *synt_head);
    int creat_find_plan_multip(plan_node *quer_plan, char quer_conta[SOUR_COTE][OBJE_LENGTH], oper_node *synt_head);


#ifdef __cplusplus
}
#endif

#endif /* FIND_PLAN_H */

