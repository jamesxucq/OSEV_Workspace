#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "clas_list.h"
#include "clas_save.h"
#include "ostri_utili.h"
#include "conv_utili.h"
#include "clas_load.h"


//
/*
<?xml version="1.0" encoding="UTF-8"?>
<class_metada>
    <object_id>fe739b30f77c335900000000</object_id>
    <clas_name>test</clas_name>
    <clas_attr>
        <version>1</version>
        <integrity>true</integrity>
    </clas_attr>
</class_metada>
 */

//
static osv_str_t START_OBJEID_LABEL = osv_stri("<object_id>");
static osv_str_t END_OBJEID_LABEL = osv_stri("</object_id>");
static osv_str_t START_VERSION_LABEL = osv_stri("<version>");
static osv_str_t END_VERSION_LABEL = osv_stri("</version>");
static osv_str_t START_INTEGRITY_LABEL = osv_stri("<integrity>");
static osv_str_t END_INTEGRITY_LABEL = osv_stri("</integrity>");
static osv_str_t END_METADA_LABEL = osv_stri("</class_metada>");
//
static osv_str_t START_INHERIT_LABEL = osv_stri("<inherit");
static osv_str_t INHERIT_METHOD_LABEL = osv_stri("method");
static osv_str_t INHERIT_PARAT_LABEL = osv_stri("param_type");
static osv_str_t END_INHERIT_LABEL = osv_stri("</inherit>");

//
#define INTEGRI_TRUE    "true"
#define INTEGRI_FALSE    "false"

static char *parse_attrib(osv_oid_t *obje_oid, unsigned long *version, int *integrity, char *clas_data) {
    char element_value[ELEMEN_LENGTH];
    char *parse_toke;
    //
    parse_toke = clas_data;
    GET_ELEMENT_VALUE(element_value, parse_toke, START_OBJEID_LABEL, END_OBJEID_LABEL);
    if (!parse_toke) return NULL;
    stroid(obje_oid, element_value);
    //
    GET_ELEMENT_VALUE(element_value, parse_toke, START_VERSION_LABEL, END_VERSION_LABEL);
    if (!parse_toke) return NULL;
    *version = atol(element_value);
    //
    GET_ELEMENT_VALUE(element_value, parse_toke, START_INTEGRITY_LABEL, END_INTEGRITY_LABEL);
    if (!parse_toke) return NULL;
    if (!strcmp(INTEGRI_TRUE, element_value)) *integrity = 0x01;
    else if (!strcmp(INTEGRI_FALSE, element_value)) *integrity = 0x00;
    //
    return clas_data;
}

static char *parse_inherit(inherit **inhe_list, char *class_inheri) {
    char attrib_value1[ATTRIB_LENGTH], attrib_value2[ATTRIB_LENGTH];
    char element_value[ELEMEN_LENGTH];
    char *parse_toke;
    //
    inherit *ilist;
    parse_toke = class_inheri;
    GET_ATTRIB2_ELEMENT_VALUE(attrib_value1, attrib_value2, element_value, parse_toke, START_INHERIT_LABEL, INHERIT_METHOD_LABEL, INHERIT_PARAT_LABEL, END_INHERIT_LABEL)
    while (parse_toke) {
        ilist = appe_ilist_new(inhe_list);
        if (!ilist) return NULL;
        strcpy(ilist->method, attrib_value1);
        strcpy(ilist->parat, attrib_value2);
        strcpy(ilist->iclas, element_value);
        GET_ATTRIB2_ELEMENT_VALUE(attrib_value1, attrib_value2, element_value, parse_toke, START_INHERIT_LABEL, INHERIT_METHOD_LABEL, INHERIT_PARAT_LABEL, END_INHERIT_LABEL)
    }
    //
    return class_inheri;
}

//

static char *split_class_objid(char *obid_data, char *clas_data) {
    char *toksp = strstr(clas_data, START_OBJEID_LABEL.data);
    if (!toksp) return NULL;
    toksp += START_OBJEID_LABEL.len;
    char *tokep = strstr(toksp, END_OBJEID_LABEL.data);
    if (!tokep) return NULL;
    //
    if (obid_data) strzcpy(obid_data, toksp, tokep - toksp);
    return tokep + END_OBJEID_LABEL.len;
}
//

static char *split_class_attri(char *attr_data, char *clas_data) {
    char *tokep = strstr(clas_data, END_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.len;
    if (attr_data) strzcpy(attr_data, clas_data, tokep - clas_data);
    return tokep;
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

static char *find_defin_decla_ex(char *nspac, char *decla, char *clas_data) {
    char *tokep, *toksp;
    //
    toksp = strchr(clas_data, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(nspac, clas_data, toksp - clas_data);
    strzcpy(decla, toksp, tokep - toksp + 0x01);
    if (!have_define(tokep + 0x01)) return tokep + 0x01;
    //
    return pass_define(tokep + 0x01);
}

static char *space_delim(char *stri) {
    char *str = strchr(stri, ':');
    if (str) str++;
    return str;
}

static char *split_class_conte(char *clas_decl, char *clas_data) {
    char *tokep, *toksp;
    char nspac[CLASS_LENGTH];
    //
    if (!(toksp = kill_inval(clas_data))) return NULL;
    tokep = find_defin_decla(nspac, toksp);
    while (tokep) {
        if (!space_delim(nspac)) {
            strzcpy(clas_decl, toksp, tokep - toksp);
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

static int parse_method(metho **mlsth, char *clas_data) {
    char *tokep, *toksp;
    metho *mlist;
    // char define_method[LARGE_TEXT_SIZE];
    char nspac[METH_LENGTH];
    char decla[METH_LENGTH];
    // printf("pm clas_data:%s\n", clas_data);
    char *metnm;
    if (!(toksp = kill_inval(clas_data))) return -1;
    tokep = find_defin_decla_ex(nspac, decla, toksp);
    while (tokep) {
        if ((metnm = space_delim(nspac))) {
            mlist = appe_mlist_new(mlsth);
            strcpy(mlist->meth_name, metnm);
            conv_decla_vtype(mlist->param_type, decla);
            strzcpy(mlist->meth_txt, toksp, tokep - toksp);
            // printf("meth_name:%s meth_txt:%s\n", mlist->meth_name, mlist->meth_txt);
        }
        //
        if (!(toksp = kill_inval(tokep))) return -1;
        tokep = find_defin_decla_ex(nspac, decla, toksp);
    }
    //
    return 0x00;
}

clas_attr *parse_class_attri(clas_attr *clasa, char *clat_path) {
    char clas_data[ADVAN_OBJE_SIZE];
    if (!load_data(clas_data, ADVAN_OBJE_SIZE, clat_path)) return NULL;
    printf("attri load_data:|%s|\n", clas_data);
    //
    char conte_data[LARGE_TEXT_SIZE];
    char *last_str = split_class_attri(conte_data, clas_data);
    if (!last_str) return NULL;
    // printf("conte_data:%s\n", conte_data);
    if (!parse_attrib(&clasa->obje_oid, &clasa->version, &clasa->integrity, conte_data))
        return NULL;
    if (!parse_inherit(&clasa->inhe_list, last_str))
        return NULL;
    printf("version:%lu integrity:%d\n", clasa->version, clasa->integrity);
    //
    return clasa;
}

clas_meta *parse_class_conte(clas_meta *clasm, char *clas_path) {
    char clas_data[ADVAN_OBJE_SIZE];
    if (!load_data(clas_data, ADVAN_OBJE_SIZE, clas_path)) return NULL;
    printf("conte load_data:|%s|\n", clas_data);
    //
    char *last_str = split_class_conte(clasm->clas_decl, clas_data);
    printf("conte clas_decl:|%s|\n", clasm->clas_decl);
    parse_method(&clasm->meth_list, last_str);
    //
    return clasm;
}

char *parse_class_decla(char *clas_decl, char *clas_path) {
    char clas_data[ADVAN_OBJE_SIZE];
    if (!load_data(clas_data, ADVAN_OBJE_SIZE, clas_path)) return NULL;
    printf("decla load_data:|%s|\n", clas_data);
    //
    split_class_conte(clas_decl, clas_data);
    printf("decla clas_decl:|%s|\n", clas_decl);
    //
    return clas_decl;
}

//

char *find_class_objid(char *clas_obid, char *clat_path) {
    char clas_data[ADVAN_OBJE_SIZE];
    if (!load_data(clas_data, ADVAN_OBJE_SIZE, clat_path)) return NULL;
    // printf("load_data:|%s|\n", clas_data);
    char *last_str = split_class_objid(clas_obid, clas_data);
    if (!last_str) return NULL;
    //
    return clas_obid;
}

char *find_class_attri(char *clas_attr, char *clat_path) {
    char clas_data[ADVAN_OBJE_SIZE];
    if (!load_data(clas_data, ADVAN_OBJE_SIZE, clat_path)) return NULL;
    // printf("load_data:%s\n", clas_data);
    char *last_str = split_class_attri(clas_attr, clas_data);
    if (!last_str) return NULL;
    //
    return clas_attr;
}

char *find_class_inheri(char *clas_inhe, char *clat_path) {
    char clas_data[ADVAN_OBJE_SIZE];
    if (!load_data(clas_data, ADVAN_OBJE_SIZE, clat_path)) return NULL;
    // printf("load_data:|%s|\n", clas_data);
    char *last_str = split_class_attri(NULL, clas_data);
    if (!last_str) return NULL;
    strcpy(clas_inhe, last_str);
    //
    return clas_inhe;
}

//

char *find_class_defin(char *clas_decl, char *clas_path) {
    char clas_data[ADVAN_OBJE_SIZE];
    if (!load_data(clas_data, ADVAN_OBJE_SIZE, clas_path)) return NULL;
    // printf("load_data:|%s|\n", clas_data);
    split_class_conte(clas_decl, clas_data);
    // printf("clas_decl:|%s|\n", clas_decl);
    return clas_decl;
}

//
