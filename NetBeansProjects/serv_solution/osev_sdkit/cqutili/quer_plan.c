
#include "plan_utili.h"
#include "quer_plan.h"

//
plan_node *open_curso_sing(plan_node *quep, char *quer_conta) {
    quep->acti_oper = OPEN_CONTE_ACCO;
    strcpy(quep->cont_name, quer_conta);
    return ++quep;
}

plan_node *close_curso_sing(plan_node *quep, char *quer_conta) {
    // printf("close_curso_sing\n");
    quep->acti_oper = CLOSE_CONTE_ACCO;
    strcpy(quep->cont_name, quer_conta);
    return ++quep;
}

//

plan_node *open_curso_mult(plan_node *quep, char quer_conta[SOUR_COTE][OBJE_LENGTH]) {
    int inde = 0x00;
    for (; (SOUR_COTE > inde) && !quer_conta[inde][0x00]; inde++, quep++) {
        quep->acti_oper = OPEN_CONTE_ACCO;
        strcpy(quep->cont_name, quer_conta[inde]);
    }
    //
    return quep;
}

plan_node *close_curso_mult(plan_node *quep, char quer_conta[SOUR_COTE][OBJE_LENGTH]) {
    int inde = 0x00;
    for (; (SOUR_COTE > inde) && !quer_conta[inde][0x00]; inde++, quep++) {
        quep->acti_oper = CLOSE_CONTE_ACCO;
        strcpy(quep->cont_name, quer_conta[inde]);
    }
    //
    return quep;
}

//
static plan_node *inse_plan_node(oper_node *synt_node, plan_node *left_chil, plan_node *quer_plan, char *quer_conta) {
    // printf("--- node, node_type:%u, stri_valu:%s\n", synt_node->node_type, synt_node->leno->stri_valu);
    plan_node *que_tok = NULL;

    //
    switch (OPER_TYPE(synt_node->node_type)) {
        case OR_TOKE:
            que_tok = appe_or_node(quer_plan, left_chil - 0x01, quer_plan - 0x01);
            break;
        case AND_TOKE:
            que_tok = appe_and_node(quer_plan, left_chil - 0x01, quer_plan - 0x01);
            break;
        case NOT_TOKE:
            que_tok = appe_not_node(left_chil, left_chil - 0x01);
            break;
        case IS_TOKE:
            break;
        case MATCH_TOKE:
            break;
        case LIKE_KW_TOKE:
            break;
        case BETWEEN_TOKE:
            break;
        case IN_TOKE:
            break;
        case NOT_EQUAL_TOKE:
            que_tok = appe_noeq_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        case EQUAL_TOKE:
            que_tok = appe_equa_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        case GREAT_THAN_TOKE:
            que_tok = appe_grth_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        case LESS_EQUAL_TOKE:
            que_tok = appe_leeq_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        case LESS_THAN_TOKE:
            que_tok = appe_leth_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        case GREAT_EQUAL_TOKE:
            que_tok = appe_greq_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        case ESCAPE_TOKE:
            break;
        case PLUS_TOKE:
            que_tok = appe_plus_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        case MINUS_TOKE:
            que_tok = appe_minu_node(quer_plan, synt_node->left_chil, synt_node->righ_chil, quer_conta);
            break;
        default:
            return NULL;
    }
    //
    return que_tok;
}

/*
             |>|
             / \
           |ax||0| 
 *  */
//

plan_node *recur_synta(plan_node *quer_plan, oper_node *synt_node, char *quer_conta) {
    plan_node *left_chil, *que_tok;
    // printf("--- recur_synta, node_type:%u, stri_valu:%s\n", synt_node->node_type, synt_node->leno->stri_valu);
    if (TERM_TOKE == synt_node->node_type) return quer_plan;
    //
    left_chil = recur_synta(quer_plan, synt_node->left_chil, quer_conta);
    if (!left_chil) return NULL;
    que_tok = recur_synta(left_chil, synt_node->righ_chil, quer_conta);
    if (!que_tok) return NULL;
    //
    return inse_plan_node(synt_node, left_chil, que_tok, quer_conta);
}

//
void set_initi_valu(plan_node *quep, plan_node *plan_head) {
    quep->child = plan_head;
    plan_head->acti_oper |= PLAN_HEAD_ACCO;
}