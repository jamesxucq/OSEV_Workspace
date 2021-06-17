#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "pars_utili.h"

//

static char *couple_bracket(char *stri) {
    if (!stri || '(' != stri[0x00]) return NULL;
    char *toke = stri + 0x01;
    //
    for (; '\0' != toke[0x00]; toke++) {
        if ('(' == toke[0x00]) {
            for (toke++; isdigit(toke[0x00]); toke++);
            if (')' != toke[0x00]) return NULL;
        } else if (')' == toke[0x00]) break;
    }
    if ('\0' == toke[0x00]) return NULL;
    //
    return toke;
}

/*
 <(void)int>
 <(x int)>
 <(void)int, (x int)>
 */

// -1:error 0x01:single 0x02:double

static int inte_count(char **last_char, char *meth_inte, char *meth_txt) {
    char *toksp = strchr(meth_txt, '<');
    if (!toksp) return -1;
    char *tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return -1;
    //
    strzcpy(meth_inte, toksp, tokep - toksp + 0x01);
    int inte_numb = 0x00;
    for (toksp = meth_inte; '\0' != toksp[0x00]; toksp++) {
        if ('(' == toksp[0x00]) {
            toksp = couple_bracket(toksp);
            if (!toksp) break;
            inte_numb++;
        }
    }
    //
    if (last_char) *last_char = tokep + 0x01;
    return inte_numb;
}

// -1:error 0x00:inn_out 0x01:inn 0x02:out

static int iointe_type_si(char *meth_inte) {
    char *toksp = strchr(meth_inte, '(');
    if (!toksp) return -1;
    char *tokep = couple_bracket(toksp);
    if (!tokep) return -1;
    //
    int ioitype = 0x01;
    for (tokep++; '\0' != tokep[0x00]; tokep++) {
        if (isalpha(tokep[0x00])) {
            ioitype = 0x02;
            break;
        }
    }
    //
    return ioitype;
}

static int parse_iointe_sio(char *meth_ointe, char *meth_inte, int ioitype) {
    char *toksp, *tokep;
    if (0x02 == ioitype) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        strzcpy(meth_ointe, toksp, tokep - toksp + 0x01);
    }
    //
    return 0x00;
}

// -1:error 0x00:inn_out 0x01:out_inn

static int iointe_type_do(char *meth_inte) {
    char *toksp = meth_inte;
    int check_times = 0x02;
    int ointe_numb = 0x00;
    int ioitype = 0x00;
    //
    while (check_times--) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        char *tokep = couple_bracket(toksp);
        if (!tokep) return -1;
        //
        char *toknp = ++tokep;
        for (; '\0' != toknp[0x00]; toknp++) {
            if (',' == toknp[0x00]) {
                break;
            } else if (isalpha(toknp[0x00])) {
                ioitype = check_times;
                ointe_numb++;
                break;
            }
        }
        //
        toksp = strchr(toknp, ',');
    }
    //
    return 0x01 == ointe_numb ? ioitype : -1;
}

static int parse_iointe_doo(char *meth_ointe, char *meth_inte, int ioitype) {
    char *tokep, *toksp = meth_inte;
    if (!ioitype) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        toksp = strchr(tokep + 0x01, ',');
        if (!toksp) return -1;
    }
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return -1;
    strzcpy(meth_ointe, toksp, tokep - toksp + 0x01);
    //
    return 0x00;
}

// -1:error 0x00:inn_out 0x01:inn 0x02:out

int parse_ohead(char *meth_ointe, char *decla) {
    // printf("phe meth_txt:%s\n", meth_txt);
    char meth_inte[METH_LENGTH];
    int ioitype = -1;
    //
    int inte_numb = inte_count(NULL, meth_inte, decla);
    // printf("phe inte_numb:%d\n", inte_numb);
    switch (inte_numb) {
        case 0x01:
            ioitype = iointe_type_si(meth_inte);
            // printf("its ioitype:%d\n", ioitype);
            if (-1 == ioitype || 0x01 == ioitype) break;
            parse_iointe_sio(meth_ointe, meth_inte, ioitype);
            break;
        case 0x02:
            ioitype = iointe_type_do(meth_inte);
            // printf("itd ioitype:%d\n", ioitype);
            if (-1 == ioitype) break;
            parse_iointe_doo(meth_ointe, meth_inte, ioitype);
            ioitype = 0x00;
            break;
        default:
            return -1;
            break;
    }
    //
    return ioitype;
}

//

char *parse_ointe(char *data_type, char *param) {
    // printf("param:|%s|\n", param);
    char *tokep, *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00] || ')' == toksp[0x00] || isdigit(toksp[0x00]); toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    //
    toksp = strchr(toksp + 0x01, ' ');
    if (!toksp) return NULL;
    for (; ' ' == toksp[0x00]; toksp++);
    tokep = strpbrk(toksp + 0x01, ", ()");
    if (!toksp) return NULL;
    strzcpy(data_type, toksp, tokep - toksp);
    //
    return tokep + 0x01;
}