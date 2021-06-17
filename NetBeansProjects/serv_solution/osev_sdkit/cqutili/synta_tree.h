
/* 
 * File:   synta_tree.h
 * Author: James
 *
 * Created on 2018.12.10, PM 4:43
 */

#ifndef SYNTA_TREE_H
#define SYNTA_TREE_H

#ifdef __cplusplus
extern "C" {
#endif
    //
#include <stdlib.h>
#include "valtok.h"


    // abstract syntax tree
    /*
        typedef struct leaf_node_t {
            termin term_type;
            long long lolo_valu;
            double doub_valu;
            char stri[MAX_TOKE_SIZE];
        } leaf_node;
     */
    typedef struct valu_toke_t leaf_node;

    //

    typedef struct leaf_list_t {
        struct leaf_list_t *next;
        leaf_node *opno;
    } leaf_list;

    //
#define NEW_LEAF_NODE(LEAF_NODE) \
    LEAF_NODE = (leaf_node *) malloc(sizeof (leaf_node)); \
    memset(LEAF_NODE, 0x00, sizeof(leaf_node));

#define NEW_LEAF_VATO(LEAF_NODE, VALU_TOKE) \
    LEAF_NODE = (leaf_node *) malloc(sizeof (leaf_node)); \
    memcpy(LEAF_NODE, VALU_TOKE, sizeof(leaf_node));

#define LEAF_NODE_DELE(LEAF_NODE)    free(LEAF_NODE)

    //
    leaf_node *new_leaf_vato(valu_toke *valtok);

    //

    typedef struct oper_node_t {
        uint node_type;
        //

        union {
            struct oper_node_t *left_chil;
            leaf_node *leno;
            leaf_list *lealst;
        };
        //

        union {
            struct oper_node_t *righ_chil;
            void *list_next;
        };
    } oper_node;

    typedef struct oper_list_t {
        struct oper_list_t *next;
        oper_node *opno;
    } oper_list;

    //
#define PARSE_SUCCESS     0x00
#define PARSE_FAULT       -1

    typedef struct parse_stat_t {
        oper_node *synt_head;
        int accept;
        char *erro_msg;
    } pastat;

    //
    oper_node *new_oper_leaf(uint opnum, leaf_node *leno);

    //
#define NEW_OPERA_NODE(OPER_NODE) \
    OPER_NODE = (oper_node *) malloc(sizeof (oper_node)); \
    memset(OPER_NODE, 0x00, sizeof(oper_node));

    //
    oper_node *new_oper_node(pastat *state, uint opnum, oper_node *leno, oper_node *riod);
    oper_list *new_oper_list(oper_list *olist, oper_node *opno);

    //
    void recu_dele(oper_node *ople_node);
#define DESTROY_STREE(TREE_HEAD)    recu_dele(TREE_HEAD)

    //
#define OPER_NODE_DELE(OPER_NODE)    free(OPER_NODE)
    void oper_list_dele(oper_list *olist);

    //
    oper_node *expr_add_collate(pastat *state, uint opnum, leaf_node *leno, oper_node *riod);
    oper_node *expr_function(pastat *state, uint opnum, leaf_node *leno, leaf_node *riod);
    oper_node *binary_unary_null(pastat *state, oper_node *leno, oper_node *riod, uint opnum);





#ifdef __cplusplus
}
#endif

#endif /* SYNTA_TREE_H */

