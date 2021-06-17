
#include "quer_plan.h"
#include "find_plan.h"

//

static plan_node *initi_find_plan(plan_node *quep) {
    printf("initi_find_plan\n");
    quep->acti_oper = INIT_QUERY_ACCO;
    return ++quep;
}

static plan_node *final_find_plan(plan_node *quep) {
    printf("final_find_plan\n");
    quep->acti_oper = FINAL_QUDRY_ACCO;
    return ++quep;
}

//

int creat_find_plan_single(plan_node *quer_plan, char *quer_conta, oper_node *synt_head) {
    plan_node *que_tok = quer_plan;
    //
    if (!(que_tok = initi_find_plan(que_tok))) return -1;
    if (!(que_tok = open_curso_sing(que_tok, quer_conta))) return -1;
    if (!(que_tok = recur_synta(que_tok, synt_head, quer_conta))) return -1;
    set_initi_valu(quer_plan, que_tok - 0x01);
    if (!(que_tok = close_curso_sing(que_tok, quer_conta))) return -1;
    if (!(que_tok = final_find_plan(que_tok))) return -1;
    (que_tok)->acti_oper = INVA_ACCO;
    //
    printf("creat_find_plan_single end.\n");
    return 0x00;
}

//

int creat_find_plan_multip(plan_node *quer_plan, char quer_conta[SOUR_COTE][OBJE_LENGTH], oper_node *synt_head) {
    plan_node *que_tok = quer_plan;
    //
    if (!(que_tok = initi_find_plan(que_tok))) return -1;
    if (!(que_tok = open_curso_mult(que_tok, quer_conta))) return -1;
    // if (!(que_tok = recur_synta(que_tok, synt_head))) return -1;
    set_initi_valu(quer_plan, que_tok - 0x01);
    if (!(que_tok = close_curso_mult(que_tok, quer_conta))) return -1;
    if (!(que_tok = final_find_plan(que_tok))) return -1;
    que_tok->acti_oper = INVA_ACCO;
    //
    return 0x00;
}
