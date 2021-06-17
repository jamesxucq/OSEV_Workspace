
/* 
 * File:   rstat_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.27, PM 1:49
 */

#ifndef RSTAT_BZL_H
#define RSTAT_BZL_H

#include "commo_header.h"
#include "oattri.h"
#include "conve_rstat.h"
#include "recurs_data.h"
#include "stat_utili.h"

#ifdef __cplusplus
extern "C" {
#endif


    //
    //    int rstabzl_create(char *data_directory);
    //    int rstabzl_destroy();
    // 0x00:ok -1:err
    int open_osev_bzl(osv_oid_t *oid, char *osdb, uint32 leve_mask);
    // 0x00:ok -1:err
    int close_osev_bzl(char *osdb);
    // 0x00:ok -1:err
    int open_osdb_bzl(osv_oid_t *oid, uint32 leve_mask);
    // 0x00:ok -1:err
    int close_osdb_bzl(osv_oid_t *oid);
    // 0x00:ok -1:err
#define valid_open_bzl valid_osdb_opened
    //
    int echo_osev_bzl(prod_data *sresp);
    int echo_osdb_bzl(prod_data *sresp, char *osdb);

    //
    int set_oleve_bzl(char *osdb, uint32 leve_mask);
    int set_dleve_bzl(osv_oid_t *oid, uint32 leve_mask);
    
    
#define STATU_SHOW 0x01    
#define STATU_SETLEVE 0x02
#define STATU_PRIVILE 0x03

    //
#define STATI_OSDB 0x01
    int ostati_osdb_bzl(prod_data *sresp);
    int dstati_osdb_bzl(prod_data *sresp, osv_oid_t *oid);
    //
    int opened_osdb_bzl(char *osds_text, char **osds_ope);
#define list_clasn_bzl(CLASS_TXT, CLAS) list_clasn(CLASS_TXT, CLAS, _COMMO_DIRECTORY_)

    //
#define attri_osdb_bzl(obje_oid, osdb) parse_osdb_attri(obje_oid, osdb)
#define rstat_osdb_bzl(rstat, osdb) load_osdb_rstat(rstat, osdb)

    //
#define enab_authen_bzl enab_authen_flag
#define disab_authen_bzl disab_authen_flag
// #define valid_authen_bzl valid_authen_enab

    //
#define build_oid_bzl(sresp, oid) conve_obje_id(sresp, oid)

#ifdef __cplusplus
}
#endif

#endif /* RSTAT_BZL_H */

