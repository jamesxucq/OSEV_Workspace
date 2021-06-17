/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexic.h"


//

typedef enum {
    INITIAL_STATUS,
    LOLO_PART_STATUS,
    DOT_STATUS,
    DOUB_PART_STATUS,
    ALPHA_PART_STATUS,
    QUOTE_PART_STATUS
} lexer_status;


//

char *get_vtoke(valu_toke *valtok, char *line_txt) {
    char *paspo;
    char *tokpo = valtok->stri;
    lexer_status status = INITIAL_STATUS;
    char cha0, cha1, cha2;

    //
    valtok->vtok_kind = INVA_TOKE;
    if ('\0' == line_txt[0x00]) return NULL;

    //
    paspo = line_txt;
    for (; '\0' != paspo[0x00]; paspo++) {
        cha0 = paspo[0x00];
        //
        if (LOLO_PART_STATUS == status && !isdigit(cha0) && '.' != cha0) {
            valtok->vtok_kind = LOLO_NUMB_TOKE;
            valtok->lolo_valu = atoll(valtok->stri);
            return paspo;
        } else if (DOUB_PART_STATUS == status && !isdigit(cha0) && '.' != cha0) {
            valtok->vtok_kind = DOUB_NUMB_TOKE;
            valtok->doub_valu = atof(valtok->stri);
            return paspo;
        } else if (ALPHA_PART_STATUS == status && !isalnum(cha0) && ':' != cha0) {
            valtok->vtok_kind = ALPHA_TOKE;
            tokpo[0x00] = '\0';
            return paspo;
        } else if (QUOTE_PART_STATUS == status) {
            tokpo[0x00] = cha0;
            tokpo++;
            if ('\'' == cha0) {
                valtok->vtok_kind = TEXT_TOKE;
                tokpo[0x00] = '\0';
                return paspo + 0x01;
            }
            continue;
        } else if (isspace(cha0)) {
            if ('\n' != cha0) {
                valtok->vtok_kind = INVA_TOKE;
                return paspo;
            }
            continue;
        }
        //
        if ((MAX_TOKE_SIZE - 0x07) <= (tokpo - valtok->stri)) {
            printf("valtok too long.\n");
            return NULL;
        }
        tokpo[0x00] = cha0;
        tokpo++;
        if ('\\' == cha0) {
            paspo++;
            tokpo[0x00] = paspo[0x00];
            tokpo++;
            continue;
        }
        cha1 = paspo[0x01];
        cha2 = paspo[0x02];
        //
        if (('&' == cha0) && ('&' == cha1)) {
            valtok->vtok_kind = AND_TOKE;
            return paspo + 0x02;
        } else if (('A' == cha0) && ('N' == cha1) && ('D' == cha2)) {
            valtok->vtok_kind = AND_TOKE;
            return paspo + 0x03;
        } else if ((('|' == cha0) && ('|' == cha1)) || (('O' == cha0) && ('R' == cha1))) {
            valtok->vtok_kind = OR_TOKE;
            return paspo + 0x02;
        } else if ('!' == cha0) {
            if ('=' == cha1) {
                valtok->vtok_kind = NOT_EQUAL_TOKE;
                return paspo + 0x02;
            } else {
                valtok->vtok_kind = NOT_TOKE;
                return paspo + 0x01;
            }
        } else if (('N' == cha0) && ('O' == cha1) && ('T' == cha2)) {
            valtok->vtok_kind = NOT_TOKE;
            return paspo + 0x03;
        } else if ('(' == cha0) {
            valtok->vtok_kind = LEFT_PARENT_TOKE;
            return paspo + 0x01;
        } else if (')' == cha0) {
            valtok->vtok_kind = RIGHT_PARENT_TOKE;
            return paspo + 0x01;
        } else if ('<' == cha0) {
            if ('=' == cha1) {
                valtok->vtok_kind = NOT_MORE_TOKE;
                return paspo + 0x02;
            } else {
                valtok->vtok_kind = LESS_THAN_TOKE;
                return paspo + 0x01;
            }
        } else if ('>' == cha0) {
            if ('=' == cha1) {
                valtok->vtok_kind = NOT_LESS_TOKE;
                return paspo + 0x02;
            } else {
                valtok->vtok_kind = GREAT_THAN_TOKE;
                return paspo + 0x01;
            }
        } else if ('=' == cha0) {
            if ('<' == cha1) {
                valtok->vtok_kind = NOT_MORE_TOKE;
                return paspo + 0x02;
            } else if ('>' == cha1) {
                valtok->vtok_kind = NOT_LESS_TOKE;
                return paspo + 0x02;
            } else {
                valtok->vtok_kind = EQUAL_TOKE;
                return paspo + 0x01;
            }
        } else if (('I' == cha0) && ('N' == cha1)) {
            valtok->vtok_kind = IN_TOKE;
            return paspo + 0x02;
        } else if (('B' == cha0) && ('E' == cha1) && ('T' == cha2) && ('W' == paspo[0x03])
                && ('E' == paspo[0x04]) && ('E' == paspo[0x05])&& ('N' == paspo[0x06])) {
            valtok->vtok_kind = BETWEEN_TOKE;
            return paspo + 0x07;
        } else if ('+' == cha0) {
            valtok->vtok_kind = TK_PLUS;
            return paspo + 0x01;
        } else if ('-' == cha0) {
            valtok->vtok_kind = TK_MINUS;
            return paspo + 0x01;
        } else if ('*' == cha0) {
            valtok->vtok_kind = TK_TIMES;
            return paspo + 0x01;
        } else if ('/' == cha0) {
            valtok->vtok_kind = TK_DIVIDE;
            return paspo + 0x01;
        } else if (isdigit(cha0)) {
            if (INITIAL_STATUS == status) {
                status = LOLO_PART_STATUS;
            } else if (DOT_STATUS == status) {
                status = DOUB_PART_STATUS;
            }
        } else if ('.' == cha0) {
            if (LOLO_PART_STATUS == status) {
                status = DOT_STATUS;
            } else {
                printf("syntax error.\n");
                return NULL;
            }
        } else if (isalpha(cha0) || (':' == cha0)) {
            if (INITIAL_STATUS == status) status = ALPHA_PART_STATUS;
        } else if ('\'' == cha0) {
            if (INITIAL_STATUS == status) status = QUOTE_PART_STATUS;
        } else {
            printf("bad character(%c)\n", cha1);
            return NULL;
        }
    }
    //
    if (LOLO_PART_STATUS == status) {
        valtok->vtok_kind = LOLO_NUMB_TOKE;
        valtok->lolo_valu = atoll(valtok->stri);
        return paspo;
    } else if (DOUB_PART_STATUS == status) {
        valtok->vtok_kind = DOUB_NUMB_TOKE;
        valtok->doub_valu = atof(valtok->stri);
        return paspo;
    } else if (ALPHA_PART_STATUS == status) {
        valtok->vtok_kind = ALPHA_TOKE;
        tokpo[0x00] = '\0';
        return paspo;
    } else if (QUOTE_PART_STATUS == status ) {
        printf("bad character(%c)\n", cha1);
        return NULL;
    }
    //
    return NULL;
}


