
/* 
 * File:   quer_plan.h
 * Author: James
 *
 * Created on 2018.12.14, PM 2:27
 */

#ifndef QUER_PLAN_H
#define QUER_PLAN_H

#include "commo_header.h"
#include "synta_tree.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define PLAN_ITEM_SZIE 1024

    //
#define INVA_ACCO           0x00000000

    // position code
#define PLAN_HEAD_ACCO      0x10000000
#define POSI_CODE(POSCOD)   (POSCOD & 0xF0000000)

    // action code
#define INIT_QUERY_ACCO     0x00010000
#define FINAL_QUDRY_ACCO    0x00020000
#define OPEN_CONTE_ACCO     0x00040000
#define CLOSE_CONTE_ACCO    0x00080000
#define RESUL_SET_ACCO      0x00100000
#define OPERA_SET_ACCO      0x00200000
#define ACTI_CODE(ACTCOD)   (ACTCOD & 0x0FFF0000)

    // value code
#define TEXT_VALU           0x00000100
#define LOLO_NUMB_VALU      0x00000200
#define DOUB_NUMB_VALU      0x00000400
#define ID_VALU             0x00000800
#define VALU_CODE(VALCOD)   (VALCOD & 0x0000FF00)

    // operation code
    // OR AND NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
    // GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS
#define OR_OPCO             0x00000001
#define AND_OPCO            0x00000003
#define NOT_OPCO            0x00000005
#define IS_OPCO             0x00000007
#define MATCH_OPCO          0x00000009
#define LIKE_KW_OPCO        0x0000000B
#define BETWEEN_OPCO        0x0000000D
#define IN_OPCO             0x0000000F
#define NOT_EQUAL_OPCO      0x00000011
#define EQUAL_OPCO          0x00000013
#define GREAT_THAN_OPCO     0x00000015
#define LESS_EQUAL_OPCO     0x00000017
#define LESS_THAN_OPCO      0x00000019
#define GREAT_EQUAL_OPCO    0x0000001B
#define ESCAPE_OPCO         0x0000001D
#define PLUS_OPCO           0x0000001F
#define MINUS_OPCO          0x00000021
#define OPER_CODE(OPECOD)   (OPECOD & 0x000000FF)

    //

    typedef struct plan_node_t {
        unsigned int acti_oper;
        //
        char cont_name[CONTA_LENGTH]; // container name

        union {
            struct plan_node_t *left_chil;
            struct plan_node_t *child;
            char source_str[MAX_TEXT_LEN];
        };

        //

        union {
            struct plan_node_t *righ_chil;
            long long lolo_valu;
            double doub_valu;
            char stri_valu[MAX_TEXT_LEN];
        };
        // result_set;
        FILE *result_set;
    } plan_node;

    //
    plan_node *open_curso_sing(plan_node *quep, char *quer_conta);
    plan_node *close_curso_sing(plan_node *quep, char *quer_conta);

    //
    plan_node *open_curso_mult(plan_node *quep, char quer_conta[SOUR_COTE][OBJE_LENGTH]);
    plan_node *close_curso_mult(plan_node *quep, char quer_conta[SOUR_COTE][OBJE_LENGTH]);

    //
    plan_node *recur_synta(plan_node *quer_plan, oper_node *synt_node, char *quer_conta);
    void set_initi_valu(plan_node *quep, plan_node *plan_head);

#ifdef __cplusplus
}
#endif

#endif /* QUER_PLAN_H */

