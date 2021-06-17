
#include "quer_plan.h"
#include "plan_utili.h"


//

/*
#define TEXT_TOKE           0x00050000 // general
#define LOLO_NUMB_TOKE      0x00070000 // general
#define DOUB_NUMB_TOKE      0x00090000 // general
 */

plan_node *appe_noeq_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_noeq_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO | NOT_EQUAL_OPCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case TEXT_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

//

plan_node *appe_equa_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_equa_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO | EQUAL_OPCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case TEXT_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

plan_node *appe_grth_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_grth_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
        que_tok->acti_oper |= GREAT_THAN_OPCO;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
        que_tok->acti_oper |= LESS_THAN_OPCO;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case TEXT_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

plan_node *appe_leeq_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_leeq_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
        que_tok->acti_oper |= LESS_EQUAL_OPCO;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
        que_tok->acti_oper |= GREAT_EQUAL_OPCO;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case TEXT_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

plan_node *appe_leth_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_leth_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
        que_tok->acti_oper |= LESS_THAN_OPCO;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
        que_tok->acti_oper |= GREAT_THAN_OPCO;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case TEXT_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

plan_node *appe_greq_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_greq_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
        que_tok->acti_oper |= GREAT_EQUAL_OPCO;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
        que_tok->acti_oper |= LESS_EQUAL_OPCO;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case TEXT_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

plan_node *appe_plus_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_plus_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO | PLUS_OPCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        case TEXT_TOKE:
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

plan_node *appe_minu_node(plan_node *quer_plan, oper_node *leno, oper_node *rino, char *quer_conta) {
    printf("appe_minu_node\n");
    plan_node *que_tok = quer_plan;
    //
    que_tok->acti_oper = RESUL_SET_ACCO | MINUS_OPCO;
    leaf_node *leno1, *leno2;
    if (ID_TOKE == leno->leno->vtok_kind) {
        leno1 = leno->leno;
        leno2 = rino->leno;
    } else {
        leno2 = leno->leno;
        leno1 = rino->leno;
    }
    //
    strcpy(que_tok->source_str, leno1->stri_valu);
    switch (leno2->vtok_kind) {
        case LOLO_NUMB_TOKE:
            que_tok->lolo_valu = leno2->lolo_valu;
            que_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            que_tok->doub_valu = leno2->doub_valu;
            que_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(que_tok->stri_valu, leno2->stri_valu);
            que_tok->acti_oper |= ID_VALU;
            break;
        case TEXT_TOKE:
        default:
            return NULL;
    }
    strcpy(que_tok->cont_name, quer_conta);
    que_tok->result_set = NULL;
    //
    return ++que_tok;
}

//

plan_node *appe_or_node(plan_node *quer_plan, plan_node *left_chil, plan_node *rich_chil) {
    printf("appe_or_node\n");
    quer_plan->acti_oper = OPERA_SET_ACCO | OR_OPCO;
    quer_plan->left_chil = left_chil;
    quer_plan->righ_chil = rich_chil;
    quer_plan->result_set = NULL;
    return ++quer_plan;
}

plan_node *appe_and_node(plan_node *quer_plan, plan_node *left_chil, plan_node *rich_chil) {
    printf("appe_and_node\n");
    quer_plan->acti_oper = OPERA_SET_ACCO | AND_OPCO;
    quer_plan->left_chil = left_chil;
    quer_plan->righ_chil = rich_chil;
    quer_plan->result_set = NULL;
    return ++quer_plan;
}

plan_node *appe_not_node(plan_node *quer_plan, plan_node *left_chil) {
    printf("appe_not_node\n");
    quer_plan->acti_oper = OPERA_SET_ACCO | NOT_OPCO;
    quer_plan->left_chil = left_chil;
    quer_plan->result_set = NULL;
    return ++quer_plan;
}