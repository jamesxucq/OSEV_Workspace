
#include "quer_plan.h"
#include "dope_plan.h"

//

static plan_node *initi_dope_plan(plan_node *quep) {
    printf("initi_find_plan\n");
    quep->acti_oper = INIT_QUERY_ACCO;
    return ++quep;
}

//

static plan_node *final_dope_plan(plan_node *quep, char *quer_conta) {
    printf("final_find_plan\n");
    quep->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(quep->cont_name, quer_conta);
    return ++quep;
}

//

int creat_plan_dope(plan_node *quer_plan, char *quer_conta, oper_node *synt_head) {
    plan_node *que_tok = quer_plan;
    //
    if (!(que_tok = initi_dope_plan(que_tok))) return -1;
    if (!(que_tok = open_curso_sing(que_tok, quer_conta))) return -1;
    if (!(que_tok = recur_synta(que_tok, synt_head, quer_conta))) return -1;
    set_initi_valu(quer_plan, que_tok - 0x01);
    if (!(que_tok = close_curso_sing(que_tok, quer_conta))) return -1;
    if (!(que_tok = final_dope_plan(que_tok, quer_conta))) return -1;
    (que_tok)->acti_oper = INVA_ACCO;
    //
    printf("creat_plan_quer_single end.\n");
    return 0x00;
}