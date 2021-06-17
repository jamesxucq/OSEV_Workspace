
/* 
 * File:   clas_list.h
 * Author: James Xu
 *
 * Created on 2016.12.18, AM 10:18
 */

#ifndef CLAS_LIST_H
#define CLAS_LIST_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct inherit_t {
        char iclas[CLASS_LENGTH];
        char method[METH_LENGTH];
        char parat[PARA_TYPE_LEN];
        struct inherit_t *next;
    } inherit;

    typedef struct metho_t {
        char meth_name[METH_LENGTH];
        char param_type[PARA_TYPE_LEN];
        char meth_txt[LARGE_TEXT_SIZE];
        struct metho_t *next;
    } metho;

    typedef struct {
        osv_oid_t obje_oid;
        char clasn[CLASS_LENGTH];
        unsigned long version; // 0x00:disable >0x00:is version
        int integrity; // 0x01:true 0x00:false
        inherit *inhe_list;
    } clas_attr;

    typedef struct {
        char clas_decl[LARGE_TEXT_SIZE];
        metho *meth_list;
    } clas_meta;

    //
    inherit *appe_ilist_new(inherit **ilsth);
    inline void ilist_dele(inherit *ilist);
    inherit *addi_imeth(inherit **ilsth, char *metnm, char *parat, char *iclas);
    inherit *dele_imeth(inherit **ilsth, char *metnm, char *parat, char *iclas);
#define IMETH_DELE(ILIST) free(ILIST);

    //
    metho *appe_mlist_new(metho **mlsth);
    metho *appe_mlist_txt(metho **mlsth, char *meth_txt);
    int modi_metho(metho *mlist, char *metnm, char *meth_txt);
#define METH_DELE(MLIST) free(MLIST);
    inline void mlist_dele(metho *mlist);
    metho *find_metho(metho *mlist, char *metnm);
    metho *find_metho_ex(metho *mlist, char *metnm, char *decla);
    metho *dele_metho(metho **mlsth, char *metnm, char *paras);
    metho *dele_metho_ex(metho **mlsth, char *metnm, char *decla);

    //

#define CLAM_STRU_DELE(CLASM) \
    mlist_dele(CLASM.meth_list);

#define CLAA_STRU_DELE(CLASM) \
    ilist_dele(CLASM.inhe_list);


    //

#ifdef __cplusplus
}
#endif

#endif /* CLAS_LIST_H */

