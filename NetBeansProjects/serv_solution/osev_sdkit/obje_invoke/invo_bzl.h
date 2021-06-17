
/* 
 * File:   invo_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 2:16
 */

#ifndef INVO_BZL_H
#define INVO_BZL_H

#include "commo_header.h"
#include "conve.h"
#include "clas_save.h"

#ifdef __cplusplus
extern "C" {
#endif

    // int compbzl_create(char *data_directory);
    // int compbzl_destroy();

    //
    int list_metho_bzl(prod_data *sresp, char *osdb, char *metho);
    int list_class_bzl(prod_data *sresp, char *osdb, char *clasn, uint32 etype);
    int list_clasd_bzl(char *clas_decl, char *osdb, char *clasn);

    // int comp_advance_txt(char *line_txt);
    int comp_metho_bzl(char *clang_txt, char *osdb, char *meth_txt);
    int robk_metho_bzl(char *osdb, char *meth_txt);
    int comp_class_bzl(char *clang_txt, char *osdb, char *clas_decl);
    int robk_class_bzl(char *osdb, char *clas_decl);
    int comp_imeth_bzl(char *clang_txt, char *osdb, char *meth_txt);
    int robk_imeth_bzl(char *osdb, char *clasn, char *metnm, char *parat, char *iclas);
    
    //
    int repla_metho_bzl(char *clang_txt, char *osdb, char *meth_txt);
    int repla_class_bzl(char *clang_txt, char *osdb, char *clas_decl);
    
    //
    int load_metho_bzl(char *clang_txt, char *osdb, char *meth_txt);
    int load_class_bzl(char *clang_txt, char *osdb, char *clasn);

    //
    int dele_metho_bzl(char *osdb, char *methd);
    int dele_class_bzl(char *osdb, char *clasn);

    //
    int class_integri_bzl(char *osdb, char *clasn);
    int parse_cdata_bzl(char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *osdb, char *clasn);
    
    //
#define build_handle_bzl(handn, mepan, meth_txt) conve_handle_name(handn, mepan, meth_txt)
#define build_sobje_bzl(sobjn, clasn) build_sobje_txt(sobjn, clasn)

    //
    int creat_imeth_bzl(char *advan_txt, char *osdb, char *clasn, char *metnm, char *parat, char *iclas);
    int drop_imeth_bzl(char *osdb, char *clasn, char *metnm, char *parat, char *iclas);
    
    //
    int build_imeth_bzl(char *crea_clas, char *inhe_line, char *iclas[METH_NUMB], char *imeth[METH_NUMB], char *parat[PARAM_NUMB], char *clas_decl);
    
#ifdef __cplusplus
}
#endif

#endif /* INVO_BZL_H */

