#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../struti.h"
#include "commo_header.h"
#include "pcattr.h"
#include "clas_list.h"
#include "pars_utili.h"
#include "parse.h"

//

static int parse_metho_decla(method **mlsth, char *clas_data) {
    char *tokep, *toksp;
    method *mlist;
    char nspac[METH_LENGTH];
// printf("pm clas_data:%s\n", clas_data);
    char *metnm;
    if (!(toksp = kill_inval(clas_data))) return -1;
    while (toksp) {
        tokep = find_metho_decla(nspac, toksp);
        if ((metnm = space_delim(nspac))) {
            mlist = appe_mlist_new(mlsth);
            strcpy(mlist->meth_name, metnm);
            strzcpy(mlist->meth_txt, toksp, tokep - toksp);
// printf("meth_name:%s meth_txt:%s\n", mlist->meth_name, mlist->meth_txt);
        }
        //
        toksp = kill_inval(tokep);
    }
    //
    return 0x00;
}

static int parse_metho_conte(method **mlsth, char *clas_data) {
    char *tokep, *toksp;
    method *mlist;
    char nspac[METH_LENGTH];
// printf("pm clas_data:%s\n", clas_data);
    char *metnm;
    toksp = kill_inval(clas_data);
    while (toksp) {
        tokep = find_metho_defin(nspac, toksp);
        if ((metnm = space_delim(nspac))) {
            mlist = appe_mlist_new(mlsth);
            strcpy(mlist->meth_name, metnm);
            strzcpy(mlist->meth_txt, toksp, tokep - toksp);
// printf("meth_name:%s meth_txt:%s\n", mlist->meth_name, mlist->meth_txt);
        }
        //
        toksp = kill_inval(tokep);
    }
    //
    return 0x00;
}

//

class_meta *parse_class_conte(class_meta *clasm, char *clas_data) {
    char conte_data[LARGE_TEXT_SIZE];
    char *last_str = clas_data;
    if (CTYPE_CLAS_CONTE & clasm->conte_type) {
        if (CTYPE_CLAS_ATTRIB & clasm->conte_type) {
            last_str = split_class_attri(conte_data, last_str);
            if (!last_str) return NULL;
            if (!parse_attrib(&clasm->obje_oid, clasm->clasn, &clasm->version, &clasm->integrity, conte_data)) return NULL;
        }
        //
        last_str = split_class_conte(clasm->clas_decl, last_str);
        if (!last_str) return NULL;
        if (parse_metho_decla(&clasm->meth_list, last_str)) return NULL;
    } else if (CTYPE_METH_CONTE & clasm->conte_type) {
        if (CTYPE_CLAS_ATTRIB & clasm->conte_type) {
            last_str = split_class_attri(conte_data, last_str);
            if (!last_str) return NULL;
            if (!parse_attrib(&clasm->obje_oid, clasm->clasn, &clasm->version, &clasm->integrity, conte_data)) return NULL;
        }
        //
        last_str = split_class_conte(clasm->clas_decl, last_str);
        if (!last_str) return NULL;
        if (parse_metho_conte(&clasm->meth_list, last_str)) return NULL;
    }
    //
    return clasm;
}

//

int conv_conte_type(char *conv_data) {
    int contype = 0x00;
    //
    char *last_str = conv_data;
    last_str = find_class_attri(last_str);
    if (last_str) contype |= CTYPE_CLAS_ATTRIB;
    else last_str = conv_data;
    //
    last_str = pass_class_conte(last_str);
    int cctype = class_conte_type(last_str);
    switch (cctype) {
        case 0x00:
            contype |= CTYPE_CLAS_CONTE;
            break;
        case 0x01:
            contype |= CTYPE_METH_CONTE;
            break;
        case -1:
            contype = 0x00;
            break;
    }
    //
    return contype;
}
