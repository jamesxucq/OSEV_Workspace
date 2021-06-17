#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ostri_utili.h"
#include "clas_save.h"

//

static int save_attrib(char *clas_path, osv_oid_t *obje_oid, char *clasn, unsigned long version, int integri) {
    char attrib_txt[LARGE_TEXT_SIZE];
    MKZERO(attrib_txt);
    //
    char *last_str = lscpy(attrib_txt, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    char oid_stri[OID_LINE_LEN];
    last_str = lsprif(last_str, "<class_metada><object_id>%s</object_id>", oidstr(oid_stri, obje_oid));
    last_str = lsprif(last_str, "<clas_name>%s</clas_name>", clasn);
    last_str = lscpy(last_str, "<clas_attr>");
    last_str = lsprif(last_str, "<version>%lu</version>", version);
    if (integri) last_str = lscpy(last_str, "<integrity>true</integrity>");
    else last_str = lscpy(last_str, "<integrity>false</integrity>");
    last_str = lscpy(last_str, "</clas_attr></class_metada>\n");
    //
    printf("save_attrib attrib_txt:\n|%s|\n", attrib_txt);
    if (save_data(clas_path, attrib_txt, TRANSA_FILE)) return -1;
    return 0x00;
}

static int save_inherit(char *clas_path, inherit *inhe_list) {
    char attrib_txt[LARGE_TEXT_SIZE];
    MKZERO(attrib_txt);
    char *last_str = attrib_txt;
    //
    inherit *ilist;
    for (ilist = inhe_list; ilist; ilist = ilist->next) {
        last_str = lsprif(last_str, "<inherit method=\"%s\" param_type=\"%s\">%s</inherit>", ilist->method, ilist->parat, ilist->iclas);
    }
    //
    printf("save_inherit attrib_txt:\n|%s|\n", attrib_txt);
    if (save_data(clas_path, attrib_txt, FILE_APPEND)) return -1;
    return 0x00;
}

static int save_class(char *clas_path, char *clas_decl) {
    char class_conte[LARGE_TEXT_SIZE];
    char *last_str = lscpy(class_conte, clas_decl);
    lccpy(last_str, '\n');
    if (save_data(clas_path, class_conte, TRANSA_FILE)) return -1;
    return 0x00;
}

static int save_method(char *clas_path, metho *meth_list) {
    char meth_txt[LARGE_TEXT_SIZE];
    MKZERO(meth_txt);
    char *last_str = meth_txt;
    //    
    metho *mlist;
    for (mlist = meth_list; mlist; mlist = mlist->next) {
        last_str = lscpy(last_str, mlist->meth_txt);
        last_str = lccpy(last_str, '\n');
    }
    //
    if (save_data(clas_path, meth_txt, FILE_APPEND))return -1;
    return 0x00;
}

int save_class_conte(char *clat_path, clas_attr *clasa, char *clas_path, clas_meta *clasm) {
    printf("save_class_conte\n");
    if (save_attrib(clat_path, &clasa->obje_oid, clasa->clasn, clasa->version, clasa->integrity)) return -1;
    if (save_inherit(clat_path, clasa->inhe_list)) return -1;
    if (save_class(clas_path, clasm->clas_decl)) return -1;
    if (save_method(clas_path, clasm->meth_list)) return -1;
    return 0x00;
}

int save_class_attri(char *clat_path, clas_attr *clasa) {
    printf("save_class_attri\n");
    if (save_attrib(clat_path, &clasa->obje_oid, clasa->clasn, clasa->version, clasa->integrity)) return -1;
    if (save_inherit(clat_path, clasa->inhe_list)) return -1;
    return 0x00;
}

//

#define CLASS_INIT_VERSION  0x01 // 0x00:disable >0x00:is version
#define CLASS_INIT_INTEGRI  0x01 // 0x01:true 0x00:false

int creat_class_conte(char *clat_path, char *clas_path, char *clasn, char *clas_decl) {
    osv_oid_t obje_oid;
    creat_objeid_cla(&obje_oid);
    if (save_attrib(clat_path, &obje_oid, clasn, CLASS_INIT_VERSION, CLASS_INIT_INTEGRI)) return -1;
    if (save_class(clas_path, clas_decl)) return -1;
    //
    return 0x00;
}

int class_dele_conte(char *clat_path, char *clas_path) {
    if (unlink(clat_path) < 0x00) return -1;
    if (unlink(clas_path) < 0x00) return -1;
    return 0x00;
}