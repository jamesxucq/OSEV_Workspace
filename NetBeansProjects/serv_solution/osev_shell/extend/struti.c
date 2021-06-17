#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "struti.h"
//

char *space_delim(char *stri) {
    char *str = strchr(stri, ':');
    if (str) str++;
    return str;
}

//

static char *have_define(char *stri) {
    char *toke = stri;
    while (' ' == toke[0x00]) toke++;
    if ('{' == toke[0x00]) return toke;
    return NULL;
}

static char *pass_define(char *stri) {
    char *toke;
    int tok_num = 0x00;
    //
    for (toke = stri; (toke = strpbrk(toke, "{}")); toke++) {
        if ('{' == toke[0x00]) ++tok_num;
        else if ('}' == toke[0x00]) --tok_num;
        if (!tok_num) break;
    }
    //
    return toke + 0x01;
}

char *find_metho_decla(char *nspac, char *clas_data) {
    char *tokep, *toksp;
    //
    toksp = strchr(clas_data, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(nspac, clas_data, toksp - clas_data);
    //
    tokep = strchr(tokep + 0x01, ';');
    if (!tokep) return NULL;
    return tokep + 0x01;
}

//

char *find_metho_defin(char *nspac, char *clas_data) {
    char *tokep, *toksp;
    //
    toksp = strchr(clas_data, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(nspac, clas_data, toksp - clas_data);
    if (!have_define(tokep + 0x01)) return NULL;
    //
    return pass_define(tokep + 0x01);
}

//

static char *find_defin_decla(char *nspac, char *clas_data) {
    char *tokep, *toksp;
    //
    toksp = strchr(clas_data, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(nspac, clas_data, toksp - clas_data);
    if (!have_define(tokep + 0x01)) return tokep + 0x01;
    //
    return pass_define(tokep + 0x01);
}

//

char *split_class_conte(char *clas_defin, char *clas_data) {
    char *tokep, *toksp;
    char nspac[CLASS_LENGTH];
    //
    if (!(toksp = kill_inval(clas_data))) return NULL;
    tokep = find_defin_decla(nspac, toksp);
    while (tokep) {
        if (!space_delim(nspac)) {
            strzcpy(clas_defin, toksp, tokep - toksp);
            break;
        }
        //
        if (!(toksp = kill_inval(tokep))) return NULL;
        tokep = find_defin_decla(nspac, toksp);
    }
    //
    return tokep;
}

//

char *pass_class_conte(char *clas_data) {
    char *tokep, *toksp;
    char nspac[CLASS_LENGTH];
    //
    if (!(toksp = kill_inval(clas_data))) return NULL;
    tokep = find_defin_decla(nspac, toksp);
    while (tokep) {
        if (!space_delim(nspac)) break;
        //
        if (!(toksp = kill_inval(tokep))) return NULL;
        tokep = find_defin_decla(nspac, toksp);
    }
    //
    return tokep;
}

//

int class_conte_type(char *clas_data) {
    char *toke = kill_inval(clas_data);
    if (!toke) return -1;
    //
    toke = strchr(toke, '<');
    if (!toke) return 0x00;
    toke = strchr(toke + 0x01, '>');
    if (!toke) return 0x00;
    //
    if (!have_define(toke + 0x01)) return 0x00;
    return 0x01;
}
