#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../struti.h"
#include "pcattr.h"

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
<inherit method="method_name">class_name</inherit>
<inherit method="method_name">class_name</inherit>
 */

//
static osv_str_t START_OBJEID_LABEL = osv_stri("<object_id>");
static osv_str_t END_OBJEID_LABEL = osv_stri("</object_id>");
static osv_str_t START_CLASN_LABEL = osv_stri("<clas_name>");
static osv_str_t END_CLASN_LABEL = osv_stri("</clas_name>");
static osv_str_t START_VERSION_LABEL = osv_stri("<version>");
static osv_str_t END_VERSION_LABEL = osv_stri("</version>");
static osv_str_t START_INTEGRITY_LABEL = osv_stri("<integrity>");
static osv_str_t END_INTEGRITY_LABEL = osv_stri("</integrity>");
static osv_str_t END_METADA_LABEL = osv_stri("</class_metada>");

//
#define INTEGRI_TRUE    "true"
#define INTEGRI_FALSE    "false"

char *parse_attrib(osv_oid_t *obje_oid, char *clasn, unsigned long *version, int *integrity, char *clas_data) {
    char element_value[ELEMEN_LENGTH];
    char *parse_toke;
    //
    parse_toke = clas_data;
    GET_ELEMENT_VALUE(element_value, parse_toke, START_OBJEID_LABEL, END_OBJEID_LABEL);
    if (!parse_toke) return NULL;
    stroid(obje_oid, element_value);
    //
    GET_ELEMENT_VALUE(element_value, parse_toke, START_CLASN_LABEL, END_CLASN_LABEL);
    if (!parse_toke) return NULL;
    strcpy(clasn, element_value);
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

//

char *split_class_attri(char *attr_data, char *clas_data) {
    char *tokep = strstr(clas_data, END_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.len;
    if(attr_data) strzcpy(attr_data, clas_data, tokep - clas_data);
    return tokep;
}

//

char *find_class_attri(char *clas_data) {
    char *tokep = strstr(clas_data, END_METADA_LABEL.data);
    if (!tokep) return NULL;
    tokep += END_METADA_LABEL.len;
    return tokep;
}