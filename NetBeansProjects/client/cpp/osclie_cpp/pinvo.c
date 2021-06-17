#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "osev_common/commo_header.h"
#include "pinvo.h"


//

static char *delim_start(char *stri) {
    char *toke = stri;
    for (; isalnum(toke[0x00]); toke++);
    return toke;
}

static char *delim_end(char *stri) {
    char *toke = stri;
    for (; '\0' != toke[0x00] && !isalnum(toke[0x00]); toke++);
    return toke;
}

// 0x00:object method 0x01:only method 0x02:command

static int comd_meth_type(char *stri) {
    if (':' == stri[0x00]) return 0x01;
    char *toksp = delim_start(stri);
    char *tokep = delim_end(toksp);
    if (tokep && toksp) {
        for (; tokep >= toksp; toksp++) {
            if (':' == toksp[0x00]) return 0x00;
        }
    }
    return 0x02;
}

static char *space_conte(char *obje_meth, char *stri) {
    char *toksp = stri;
    for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
    //
    char *toke = toksp;
    for (; '\0' != toke[0x00]; ++toke)
        if ('(' == toke[0x00] || '<' == toke[0x00]) break;

    //
    char *tokep = toke;
    for (; toksp != tokep && ' ' == tokep[-1]; tokep--);
    //
    strzcpy(obje_meth, toksp, tokep - toksp);
    return toke;
}

#define SPACE_DELIM_TOK ':'

static int check_sptok(char *start, char *end) {
    // printf("start:|%s| end:|%s|\n", start, end);
    if (start == end) return 0x00;
    else if (start && end) {
        for (; end >= start; start++) {
            if (SPACE_DELIM_TOK == start[0x00]) return 0x00;
        }
    }
    //
    return -1;
}

static int split_array(char *space_array[SPACE_NUMB], char *stri) {
    char *toke = stri;
    //
    int inde = 0x00;
    for (; '\0' != toke[0x00]; inde++) {
        char *delisp = delim_start(toke);
        char *deliep = delim_end(delisp);
        if (check_sptok(delisp, deliep)) return -1;
        //
        space_array[inde] = toke;
        MKZERO(delisp);
        // printf("space_array[inde]:|%s|\n", space_array[inde]);
        toke = deliep;
    }
    space_array[inde] = NULL;
    //
    return 0x00;
}

static void creat_space(char *obje, char *metho, char **space_array) {
    char *last_str = obje;
    last_str = lscpy(last_str, space_array[0x00]);
    //
    char **array_tok = space_array + 0x01;
    char *last_tok = array_tok[0x00];
    for (array_tok++; array_tok[0x00]; array_tok++) {
        last_str = lccpy(last_str, ':');
        last_str = lscpy(last_str, last_tok);
        last_tok = array_tok[0x00];
    }
    lscpy(metho, last_tok);
}

static char *split_obje_metho(char *obje, char *metho, char *stri) {
    char obje_meth[OBJE_LENGTH + METH_LENGTH];
    char *parse_tok = space_conte(obje_meth, stri);
    // printf("obje_meth:|%s| stri:|%s|\n", obje_meth, stri);
    //
    char *space_array[SPACE_NUMB];
    if (split_array(space_array, obje_meth)) return NULL;
    //
    creat_space(obje, metho, space_array);
    return parse_tok;
}

//

static char *method_space(char *name, char *stri) {
    char *toksp, *tokep;
    //
    for (toksp = stri; '\0' != toksp[0x00]; ++toksp)
        if (' ' != toksp[0x00] && ':' != toksp[0x00]) break;
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep)
        if (' ' == tokep[0x00] || '(' == tokep[0x00] || '<' == tokep[0x00]) break;
    //
    strzcpy(name, toksp, tokep - toksp);
    return tokep;
}

static char *split_command(char *obje, char *metho, char *line_str) {
    char *parse_tok = kill_blank(line_str);
    // 0x00:object method 0x01:only method 0x02:command
    switch (comd_meth_type(parse_tok)) {
        case 0x00:
            // printf("[debug]split_command, method parse_tok:%s\n", parse_tok);
            parse_tok = split_obje_metho(obje, metho, parse_tok);
            // printf("[debug]split_command, method parse_tok:%s\n", parse_tok);
            // printf("[debug]split_command, method parse_tok:%s\n", parse_tok);
            break;
        case 0x01:
        case 0x02:
            strcpy(obje, "odb");
            // printf("[debug]split_command, cmd parse_tok:%s\n", parse_tok);
            parse_tok = method_space(metho, parse_tok);
            // printf("[debug]split_command, cmd parse_tok:%s\n", parse_tok);
            break;
    }
    //
    return parse_tok;
}


//

static char *next_param(char *para_str, char *stri) {
    char *toksp, *tokep;
    char tok;
    //
    for (toksp = stri; '\0' != toksp[0x00]; toksp++) {
        tok = toksp[0x00];
        if (' ' != tok && '(' != tok && ')' != tok && ',' != tok && ';' != tok && '>' != tok)
            break;
    }
    //
    if ('"' == toksp[0x00]) {
        for (tokep = toksp + 0x01; '"' != tokep[0x00]; tokep++)
            if ('\\' == tokep[0x00]) tokep++;
        ++tokep;
    } else {
        for (tokep = toksp; '\0' != tokep[0x00]; tokep++) {
            tok = tokep[0x00];
            if (' ' == tok || '(' == tok || ')' == tok || ',' == tok || ';' == tok)
                break;
        }
    }
    strzcpy(para_str, toksp, tokep - toksp);
    //
    for (; '\0' != tokep[0x00]; tokep++) {
        tok = tokep[0x00];
        if (' ' != tok && '(' != tok && ')' != tok && ',' != tok && ';' != tok && '>' != tok)
            break;
    }
    //
    return tokep;
}

static int paras_parsing(char *paras_line, char **paras, char *line_txt) {
    char *parse_tok = line_txt;
    char para_str[PARAM_LENGTH];
    // printf("[debug]param_parsing line_txt:|%s|\n", line_txt);
    char *last_str = paras_line;
    char **paras_tok = paras;
    //
    int inde = 0x00;
    for (; ('\0' != parse_tok[0x00]) && PARAM_NUMB > inde; inde++, paras_tok++) {
        parse_tok = next_param(para_str, parse_tok);
        // printf("[debug]param_parsing parse_tok:|%s|\n", parse_tok);
        if ('\0' == para_str[0x00]) break;
        lscpy_s(paras_tok[0x00], para_str, last_str);
        // printf("[debug]param_parsing paras_tok[0x00]:|%s|\n", paras_tok[0x00]);
    }
    paras_tok[0x00] = NULL;
    //
    return 0x00;
}

//

static int bulid_invok_paras(osv_pstyl_t *pscon, char *para_str) {
    char paras_line[LARGE_TEXT_SIZE];
    char *invo_paras[PARAM_NUMB];
    if (-1 == paras_parsing(paras_line, invo_paras, para_str)) return -1;
    //
    unsigned short colen = encode_pstyle(pscon->pstyl_str + sizeof (obje_entry), invo_paras);
    if (((unsigned short) - 1) == colen) return -1;
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = colen;
    pscon->colen = objen->colen + sizeof (obje_entry);
    //
    return pscon->colen;
}

int parse_invok_metho(osv_pstyl_t *pscon, char *para_str) {
    char obje_ident[OBJE_LENGTH];
    char comd_metho[METH_LENGTH];
    char *parse_tok = split_command(obje_ident, comd_metho, para_str);
    if (!parse_tok) return -1;
    //
    unsigned short enlen = 0x00;
    unsigned short colen = strlen(obje_ident) + 0x01;
    char *last_str = stri_pstyl_ex(pscon->pstyl_str + sizeof (obje_entry), obje_ident, colen);
    enlen += sizeof (stri_entry) + colen;
    colen = strlen(comd_metho) + 0x01;
    last_str = stri_pstyl_ex(last_str, comd_metho, colen);
    enlen += sizeof (stri_entry) + colen;
    //
    osv_pstyl_t ivkpa;
    if (-1 == bulid_invok_paras(&ivkpa, parse_tok)) return -1;
    obje_pstyl(last_str, ivkpa.pstyl_str, ivkpa.colen);
    enlen += ivkpa.colen;
    //
    obje_entry *objen = (obje_entry *) pscon->pstyl_str;
    objen->notyp = noty_obje;
    objen->colen = enlen;
    pscon->colen = objen->colen + sizeof (obje_entry);
    //
    return pscon->colen;
}