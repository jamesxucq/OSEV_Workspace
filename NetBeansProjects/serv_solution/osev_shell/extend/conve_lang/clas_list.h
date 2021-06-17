
/* 
 * File:   clas_list.h
 * Author: James Xu
 *
 * Created on 2017.6.23, AM 9:34
 */

#ifndef CLAS_LIST_H
#define CLAS_LIST_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct method_t {
        char meth_name[METH_LENGTH];
        char param_type[PARA_TYPE_LEN];
        char meth_txt[LARGE_TEXT_SIZE];
        struct method_t *next;
    } method;

    typedef struct {
        osv_oid_t obje_oid;
        char clasn[CLASS_LENGTH];
        unsigned int conte_type;
        unsigned long version; // 0x00:disable >0x00:is version
        int integrity; // 0x01:true 0x00:false
        char clas_decl[LARGE_TEXT_SIZE];
        method *meth_list;
    } class_meta;

    //
    method *appe_mlist_new(method **mlsth);
    inline void mlist_dele(method *mlist);

    //
#define CLAM_STRU_DELE(CLASM) \
    mlist_dele(CLASM.meth_list);

#ifdef __cplusplus
}
#endif

#endif /* CLAS_LIST_H */

