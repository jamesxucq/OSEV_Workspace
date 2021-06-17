
/* 
 * File:   conoda_bzl.h
 * Author: James Xu
 *
 * Created on 2017.1.11, PM 2:25
 */

#ifndef CONODA_BZL_H
#define CONODA_BZL_H

#include "conoda.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    //
    int conbzl_create();
    int conbzl_destroy();

    //
    struct cono_list *open_clist_bzl(char *osdb, uint32 leval);
#define find_clstn_bzl(osdb)    find_clstn(_conta_list_, osdb)
#define find_clsto_bzl(oid)    find_clsto(_conta_list_, oid)
#define close_clist_bzl(clist)   close_clist(&_conta_list_, clist) 
    //
#define find_conto_bzl(osdb)    find_conto_osdb(_conta_list_, osdb)
    //


    //

#ifdef __cplusplus
}
#endif

#endif /* CONODA_BZL_H */

