/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lexic.h
 * Author: james
 *
 * Created on 2021年2月23日, 上午9:12
 */

#ifndef LEXIC_H
#define LEXIC_H

#include "lemon_t.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define STACK_SIZE 256

#define MAX_TOKE_SIZE 256

    /*
     * && AND || OR ! NOT ( ) < > == != >= <= BETWEEN IN
     */

    /*
     * () (l-r)
     * ! NOT (r-l)
     * < > >= <= (l-r)
     * == != (l-r)
     * BETWEEN IN (l-r)
     * && AND (l-r)
     * || OR (l-r)
     */

    //
    typedef struct valu_toke_t {
        unsigned int vtok_kind;
        long long lolo_valu;
        double doub_valu;
        char stri[MAX_TOKE_SIZE];
    } valu_toke;
    
//
    
    ///
    /*
     * && AND || OR ! NOT ( ) < > == != <= >= BETWEEN IN
     */

    //
#define INVA_TOKE           0x00000000
    
    //
#define TK_PLUS                             1
#define TK_MINUS                            2
#define TK_DIVIDE                           3
#define TK_TIMES                            4
#define TK_INTEGER                          5
    
    //
    
#define ALPHA_TOKE          0x00000006
#define TEXT_TOKE           0x00000007
#define LOLO_NUMB_TOKE      TK_INTEGER // 0x00000004
#define DOUB_NUMB_TOKE      0x00000008
//
#define OR_TOKE             0x00000010
#define AND_TOKE            0x00000020
#define NOT_TOKE            0x00000040
#define LEFT_PARENT_TOKE    0x00000080
#define RIGHT_PARENT_TOKE   0x00000100
#define LESS_THAN_TOKE      0x00000200
    //
#define GREAT_THAN_TOKE     0x00000400
#define EQUAL_TOKE          0x00000800
#define NOT_EQUAL_TOKE      0x00001000
#define NOT_MORE_TOKE       0x00002000
#define NOT_LESS_TOKE       0x00004000
#define IN_TOKE             0x00008000
#define BETWEEN_TOKE        0x00010000
    //
// #define END_LINE_TOKE       0x00020000

    
    //
 char *get_vtoke(valu_toke *valtok, char *line_txt);
    

#ifdef __cplusplus
}
#endif

#endif /* LEXIC_H */

