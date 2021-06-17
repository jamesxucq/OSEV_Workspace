#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "oattri.h"

//


//
/*
 <?xml version="1.0" encoding="UTF-8"?>
<osdb_metada>
    <object_id>13646121<object_id>
    <osdb_name>test<osdb_name>
</osdb_metada>
 */

//
static osv_str_t START_OBJEID_LABEL = osv_stri("<object_id>");
static osv_str_t END_OBJEID_LABEL = osv_stri("</object_id>");
static osv_str_t START_OBJEN_LABEL = osv_stri("<osdb_name>");
static osv_str_t END_OBJEN_LABEL = osv_stri("</osdb_name>");

//

static char *parse_attrib(osv_oid_t *obje_oid, char *osdb, char *attri_data) {
    char element_value[ELEMEN_LENGTH];
    char *parse_toke;
    //
    parse_toke = attri_data;
    GET_ELEMENT_VALUE(element_value, parse_toke, START_OBJEID_LABEL, END_OBJEID_LABEL);
    if (!parse_toke) return NULL;
    strsid_oid(obje_oid, element_value); // fix me
    //
    GET_ELEMENT_VALUE(element_value, parse_toke, START_OBJEN_LABEL, END_OBJEN_LABEL);
    if (!parse_toke) return NULL;
    strcpy(osdb, element_value);
    //
    return attri_data;
}

//

static int save_attrib(char *clas_path, osv_oid_t *obje_oid, char *osdb) {
    char attrib_txt[LARGE_TEXT_SIZE];
    MKZERO(attrib_txt);
    char *last_str = attrib_txt;
    //
    last_str = lscpy(last_str, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    char sid_stri[SID_LINE_LEN];
    last_str = lsprif(last_str, "<osdb_metada><object_id>%s</object_id>", oid_sidstr(sid_stri, obje_oid));
    last_str = lsprif(last_str, "<osdb_name>%s</osdb_name></osdb_metada>\n", osdb);
    printf("save_attrib attrib_txt:\n|%s|\n", attrib_txt);
    if (save_data(clas_path, attrib_txt, 0x00)) return -1;
    //
    return 0x00;
}

//

int creat_osdb_attri(char *oattr_path, char *osdb) {
    osv_oid_t obje_oid;
    creat_objeid_obj(&obje_oid);
    if (save_attrib(oattr_path, &obje_oid, osdb))return -1;
    //
    return 0x00;
}

//

int parse_osdb_attri(osv_oid_t *obje_oid, char *osdb) {
    char data_path[MAX_PATH * 3];
    char attr_data[LARGE_TEXT_SIZE];
    CREAT_OSDB_SUBPA(data_path, osdb, OSDB_ATTRIB)
    if (!load_data(attr_data, LARGE_TEXT_SIZE, data_path)) return -1;
    printf("load_data:%s\n", attr_data);
    //
    char _osdb_[OSDB_LENGTH];
    if (!parse_attrib(obje_oid, _osdb_, attr_data)) return -1;
    if (strcmp(osdb, _osdb_)) return -1;
    mapid_unique(obje_oid);
    //
    return 0x00;
}

