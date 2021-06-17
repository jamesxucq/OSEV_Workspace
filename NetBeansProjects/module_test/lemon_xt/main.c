/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: james
 *
 * Created on 2021年2月23日, 上午9:42
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "lexic.h"
#include "lemon_t.h"

//

static int parse_line(valu_toke vtsta[STACK_SIZE], char *line_txt) {
    char *last_str = line_txt;
    //
    valu_toke *valtok = vtsta;
    int inde = 0x00;
    for (; (last_str = get_vtoke(valtok, last_str)); inde++, valtok++) {
        if (STACK_SIZE == inde) return -1;
        printf("kind:|%X|, str:|%s|\n", valtok->vtok_kind, valtok->stri);
printf("last_str:%s\n", last_str);        
        if (INVA_TOKE == valtok->vtok_kind) break;
    }
        printf("kind:|%X|, str:|%s|\n", valtok->vtok_kind, valtok->stri);
    //
    return 0x00;
}



/*
 * 
 */
static char line_txt[1024];

int main(int argc, char** argv) {
    valu_toke vtsta[STACK_SIZE];

    //
    strcpy(line_txt, "534+66-13*2");
    printf("****** parse line:%s\n", line_txt);
    if (parse_line(vtsta, line_txt)) {
        printf("parse line error!\n");
        return -1;
    }
    printf("****** parse end.\n");
    //

    void* pParser = ParseAlloc(malloc);
    valu_toke *valtok = vtsta;
    for (; INVA_TOKE != valtok->vtok_kind; valtok++) {
        switch (valtok->vtok_kind) {
            case TK_INTEGER:
                Parse(pParser, TK_INTEGER, valtok->lolo_valu);
                break;
            case TK_PLUS:
            case TK_MINUS:
            case TK_TIMES:
            case TK_DIVIDE:
                Parse(pParser, valtok->vtok_kind, 0);
                break;
            default:
                break;
        }
        // Parse(pParser, TK_INTEGER, 2);
    }
    Parse(pParser, 0, 0);
    ParseFree(pParser, free);
    //
    return (EXIT_SUCCESS);
}



