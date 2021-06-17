
/* 
 * File:   cona_list.h
 * Author: James Xu
 *
 * Created on 2017.1.16, PM 2:35
 */

#ifndef CONA_LIST_H
#define CONA_LIST_H

#include "commo_macro.h"
#include "osev_macro.h"
#include "oid.h"
#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        osv_oid_t oid;
        char osdb_name[OSDB_LENGTH];
        char data_type[CLASS_LENGTH];
        char cont_name[CONTA_LENGTH];
        //
        rive_ha *stora_ha;
    } contain;

    typedef struct cont_list_t{
        contain *conta;
        struct cont_list_t *next;
    }cont_list;

    //
    contain *appe_conta(cont_list **colsth);

    void dele_colst(cont_list *colist);
    void cona_free(void *conta);


#ifdef __cplusplus
}
#endif

#endif /* CONA_LIST_H */

