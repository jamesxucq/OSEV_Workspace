
#include "synta_tree.h"
#include "optim_synta.h"


//

static int recur_synta(oper_node *synt_node) {
    // printf("----- recur_synta -----\n");
/*
    if (TERM_TOKE == synt_node->node_type) {
        // printf("leaf, stri_valu:%s\n", synt_node->leno->stri_valu);
        return 0x00;
    }
*/
/*
    recur_synta(synt_node->left_chil);
    recur_synta(synt_node->righ_chil);
*/
    // printf("node, node_type:%u, stri_valu:%s\n", synt_node->node_type, synt_node->leno->stri_valu);
    return 0x00;
}

//

int optim_synta_tree(oper_node *synt_head) {
    recur_synta(synt_head);
    //
    return 0x00;
}
