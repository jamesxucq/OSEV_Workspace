 
/* 
 * File:   hand_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.31, AM 8:37
 */

#ifndef HAND_BZL_H
#define HAND_BZL_H

#include "commo_header.h"
// #include "contain.h"
#include "metada.h"
#include "metaob.h"

#ifdef __cplusplus
extern "C" {
#endif

    //    int handbzl_create(char *data_directory);
    //    int handbzl_destroy();

    //
    int hcrea_metho_bzl(prod_data *sresp, hand_data *hando, hand_data *handa, char *clang_txt, char *osdb, char *meth_txt);
    int hcrea_class_bzl(prod_data *sresp, hand_data *handa, char *clang_txt, char *osdb, char *clas_decl);
    int hdrop_metho_bzl();
    int hdrop_class_bzl();
    //
    int hand_load_metho(prod_data *sresp, hand_data *hando, hand_data *handa, char *clang_txt, char *osdb, char *clasn_metn);
    int hand_load_class(prod_data *sresp, hand_data *handa, char *clang_txt, char *osdb, char *clasn);
#define hload_metho_bzl(SRESP, HANDO, HANDA, CLANG_TXT, OSDB, CLASN_METHN)   hand_load_metho(SRESP, HANDO, HANDA, CLANG_TXT, OSDB, CLASN_METHN)
#define hload_class_bzl(SRESP, HANDA, CLANG_TXT, OSDB, CLASN)   hand_load_class(SRESP, HANDA, CLANG_TXT, OSDB, CLASN)
    
    //
    int hload_odata_bzl(struct cono_list *clist);
    int open_odata_bzl(conoda *coval, char *osdb);
    int close_odata_bzl(conoda *coval, char *osdb);
    
    //
#define creat_hattr_bzl(osdb) { \
    creat_oattr(osdb); \
    creat_dattr(osdb); \
}

#ifdef __cplusplus
}
#endif

#endif /* HAND_BZL_H */

