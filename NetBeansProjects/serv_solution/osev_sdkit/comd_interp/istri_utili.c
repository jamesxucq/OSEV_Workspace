#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "istri_utili.h"

//

char *decode_const_invok(char *data_line, char **paras, char *requ_data, int req_len) {
    printf("decode_const_invok\n");
    char *last_str = data_line;
    int parse_len = 0x00;
    unsigned short enlen;
    char nval_cont[PARAM_LENGTH], *parse_tok = requ_data;
    //
    parse_tok = pstyl_obje_ex(nval_cont, &enlen, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    lmcpy_o(paras[0x00], nval_cont, enlen, last_str);
    parse_len += enlen;
    printf("1 req_len:%d, parse_len:%d, nval_cont:%s\n", req_len, parse_len, nval_cont);
    //
    if (req_len > parse_len) {
        parse_tok = pstyl_stri(nval_cont, parse_tok);
        if (!parse_tok) {
            paras[0x01] = NULL;
            return NULL;
        }
        lscpy_o(paras[0x01], nval_cont, last_str);
        printf("2 req_len:%d, parse_len:%d, nval_cont:%s\n", req_len, parse_len, nval_cont);
    }
    //
    return last_str;
}

//

char *decode_invok_list(char *data_line, char **paras, char *requ_data, int req_len) {
    printf("decode_invok_list\n");
    char *last_str = data_line;
    int parse_len = 0x00;
    unsigned short enlen;
    char nval_cont[PARAM_LENGTH], *parse_tok = requ_data;
    parse_tok = pstyl_stri_ex(nval_cont, &enlen, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    lscpy_o(paras[0x00], nval_cont, last_str);
    parse_len += enlen;
    printf("1 nval_cont:%s\n", nval_cont);
    //
    unsigned int nval_int;
    parse_tok = pstyl_uint(&nval_int, parse_tok);
    if (!parse_tok) {
        printf("3 nval_cont\n");
        paras[0x01] = NULL;
        return NULL;
    }
    lmcpy_o(paras[0x01], &nval_int, sizeof (unsigned int), last_str);
    parse_len += PSTY_INT_ELEN;
    printf("2 req_len:%d, parse_len:%d, nval_int:%u\n", req_len, parse_len, nval_int);
    //
    if (req_len != parse_len) return NULL;
    return last_str;
}