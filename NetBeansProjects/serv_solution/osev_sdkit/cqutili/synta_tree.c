#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synta_tree.h"
#include "gramm_analy.h"

//

leaf_node *new_leaf_vato(valu_toke *valtok) {
    // printf("--- new_leaf_vato\n");
    leaf_node *leno = (leaf_node *) malloc(sizeof (leaf_node));
    if (!leno) return NULL;
    memcpy(leno, valtok, sizeof (leaf_node));
    //
    return leno;
}



//

oper_node *new_oper_leaf(uint opnum, leaf_node *leno) {
    // printf("--- new_oper_leaf\n");
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    memset(opno, 0x00, sizeof (oper_node));
    opno->node_type = opnum;
    opno->leno = leno;
    //
    return opno;
}

//

oper_node *new_oper_node(pastat *state, uint opnum, oper_node *leno, oper_node *riod) {
    // printf("--- new_oper_node, opnum:%u, leno->node_type:%u, riod->node_type:%u\n", opnum, leno->node_type, riod->node_type);
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    memset(opno, 0x00, sizeof (oper_node));
    opno->node_type = opnum;
    opno->left_chil = leno;
    opno->righ_chil = riod;
    //
    state->synt_head = opno;
    return opno;
}

oper_list *new_oper_list(oper_list *olist, oper_node *opno) {
    oper_list *list_temp = (oper_list *) malloc(sizeof (oper_list));
    if (!list_temp) return NULL;
    memset(list_temp, 0x00, sizeof (oper_list));
    if (olist) list_temp->next = olist;
    //
    list_temp->opno = opno;
    return list_temp;
}

//

void recu_dele(oper_node *ople_node) {
    if (!((int *) ople_node)[0x00]) {
        if (ople_node->left_chil) recu_dele(ople_node->left_chil);
        if (ople_node->righ_chil) recu_dele(ople_node->righ_chil);
    }
    free(ople_node);
}

//

oper_node *expr_add_collate(pastat *state, uint opnum, leaf_node *leno, oper_node *riod) {
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    //
    return opno;
}

//

oper_node *expr_function(pastat *state, uint opnum, leaf_node *leno, leaf_node *riod) {
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    //
    return opno;
}

oper_node *binary_unary_null(pastat *state, oper_node *leno, oper_node *riod, uint opnum) {
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    //
    return opno;
}