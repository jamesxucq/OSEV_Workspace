/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   token.h
 * Author: James
 *
 * Created on 2019年3月18日, 上午8:54
 */

#ifndef TOKEN_H
#define TOKEN_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define MAX_TOKE_SIZE 512

    //

    typedef enum {
        ALPHA_TERM,
        TEXT_TERM,
        LOLO_NUMB_TERM,
        DOUB_NUMB_TERM,
    } termin;


    //

    typedef struct leaf_node_t {
        termin term_type;
        long long lolo_valu;
        double doub_valu;
        char stri[MAX_TOKE_SIZE];
    } leaf_node;

    typedef struct leaf_list_t {
        struct leaf_list_t *next;
        leaf_node *opno;
    } leaf_list;
    
    
    //
    typedef struct oper_node_t {
        int node_type;

        union {
            struct oper_node_t *oper_leno;
            leaf_node *leaf_term;
            leaf_list *leaf_item;
        };
        struct oper_node_t *oper_rino;
        void *list_next;
    } oper_node;


#ifdef __cplusplus
}
#endif

#endif /* TOKEN_H */

