#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "parse_utili.h"

//

// -1:error 0x00:normal 0x01:constructor

int check_space_type(char *clasn, char *metnm, char *decla, char *space) {
    char *toksp = kill_blank(space);
    if (!toksp) return -1;
    char *tokep = strchr(toksp, ':');
    if (!tokep) return -1;
    strzcpy(clasn, toksp, tokep - toksp);
    //
    toksp = strpbrk(++tokep, " (");
    if (!toksp) return -1;
    strzcpy(metnm, tokep, toksp - tokep);
    //
    if ('(' != toksp[0x00]) toksp = strchr(toksp + 0x01, '(');
    if (!toksp) return -1;
    tokep = strchr(tokep, ')');
    if (!tokep) return -1;
    strzcpy(decla, toksp, tokep - toksp + 0x01);
    //
    if (strcmp(clasn, metnm)) return 0x00;
    return 0x01;
}

char *split_space(char *clasn, char *metnm, char *space) {
    char *toksp = kill_blank(space);
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    strzcpy(clasn, toksp, tokep - toksp);
    strcpy(metnm, tokep + 0x01);
    //
    return clasn;
}

//

char *split_space_ex(char *clasn, char *metnm, char *space) {
    char *toksp = kill_blank(space);
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    strzcpy(clasn, toksp, tokep - toksp);
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(metnm, tokep + 0x01, toksp - tokep - 0x01);
    //
    return toksp;
}

//

char *split_metho_ex(char *clasn, char *metnm, char *decla, char *space) {
    char *toksp = kill_blank(space);
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    strzcpy(clasn, toksp, tokep - toksp);
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(metnm, tokep + 0x01, toksp - tokep - 0x01);
    //
    if ('<' != toksp[0x00]) toksp = strchr(toksp + 0x01, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(decla, toksp, tokep - toksp + 0x01);
    //
    return tokep + 0x01;
}

//

char *build_retyp_parse(char *retyn, char *parsn, char *handn) {
    char *last_str = lccpy(retyn, '_');
    last_str = lscpy(last_str, handn);
    lscpy(last_str, "_retype_");
    //
    last_str = lscpy(parsn, "_parse_");
    last_str = lscpy(last_str, handn);
    lccpy(last_str, '_');
    //
    return parsn;
}

char *build_obsc_name(char *osize, char *bindn, char *solvn, char *clasn) {
    char * last_str = lccpy(osize, '_');
    last_str = lscpy(last_str, clasn);
    lscpy(last_str, "_size_");
    //
    last_str = lscpy(bindn, "_bind_");
    last_str = lscpy(last_str, clasn);
    lccpy(last_str, '_');
    //
    last_str = lscpy(solvn, "_solve_");
    last_str = lscpy(last_str, clasn);
    lccpy(last_str, '_');
    //
    return osize;
}

char *split_metn(char *metnm, char *parsn, char *space) {
    char *toke = strchr(space, ':');
    if (!toke) return NULL;
    strcpy(metnm, toke + 0x01);
    char *last_str = lscpy(parsn, "p_");
    lscpy(last_str, metnm);
    //
    return metnm;
}

//

char *split_clame(char *clame, char *space) {
    char *toksp = kill_blank(space);
    if (!toksp) return NULL;
    char *tokep = strpbrk(toksp, " <");
    if (!tokep) return NULL;
    strzcpy(clame, toksp, tokep - toksp);
    return clame;
}

