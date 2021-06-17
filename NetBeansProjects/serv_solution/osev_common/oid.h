
/* 
 * File:   oid.h
 * Author: James Xu
 *
 * Created on 2017.2.1, PM 3:40
 */

#ifndef OID_H
#define OID_H

#include "commo_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#pragma pack(1)

    typedef struct {
        unsigned int osev_unique; // machine_unique
        unsigned long long stoid;
    } osv_oid_i;
#pragma pack()

#pragma pack(1)

    typedef struct {
        unsigned int osev_unique; // machine_unique
        unsigned int time_stamp;
        unsigned int counter;
    } osv_oid_t;
#pragma pack()

    //
    extern osv_oid_t INVA_OID_VALU;

    //
    unsigned int instan_unique(void);
#define mapid_unique(OBJE_OID) ((OBJE_OID)->osev_unique = instan_unique())
#define mapid_invalid(OBJE_OID) ((OBJE_OID)->osev_unique = (unsigned int) - 1)

    //
#define OSEV_OSDB_OID(oid) (oid.time_stamp || oid.counter)
    osv_oid_t *creat_objeid_osev(osv_oid_t *osev_oid);
    osv_oid_t *creat_objeid_osdb(osv_oid_t *osdb_oid);
    osv_oid_t *creat_objeid_cla(osv_oid_t *clas_oid);
    osv_oid_t *creat_objeid_obj(osv_oid_t *obje_oid);

    //
#define OID_BINARY_LEN      12
#define OID_LINE_LEN        25

    //
    osv_oid_t *stroid(osv_oid_t *obje_oid, char *oid_stri);
    char *oidstr(char *oid_stri, osv_oid_t *obje_oid);

    //
#define SID_BINARY_LEN      8
#define SID_LINE_LEN        17

    //
    osv_oid_t *strsid_oid(osv_oid_t *obje_oid, char *sid_stri);
    char *oid_sidstr(char *sid_stri, osv_oid_t *obje_oid);

    //
#define oidcmp(OID1, OID2) (((osv_oid_i *)OID1)->stoid == ((osv_oid_i *)OID2)->stoid \
    && ((osv_oid_i *)OID1)->osev_unique == ((osv_oid_i *)OID2)->osev_unique)

#define sidcmp(OID1, OID2) (((osv_oid_i *)OID1)->stoid == ((osv_oid_i *)OID2)->stoid)
    
    //
#define IS_INVA_OID(OID_T) \
    ((INVA_UINT_VALU == (OID_T).time_stamp) && (INVA_UINT_VALU == (OID_T).osev_unique) && (INVA_UINT_VALU == (OID_T).counter))

    //
#define IS_ZERO_OID(OID_T) \
    (!(OID_T).time_stamp && !(OID_T).osev_unique && !(OID_T).counter)

#define CMPOID_OSDB(OBJE_OID) (0xFFFFFFFFFFFFFFFF == ((osv_oid_i *)OBJE_OID)->stoid \
    && ((osv_oid_i *)OBJE_OID)->osev_unique == instan_unique())

#define CREAT_OSDB(OSDB_OID, OSEV_OID) { \
    (OSDB_OID)->osev_unique = (OSEV_OID)->osev_unique; \
    ((osv_oid_i *) (OSDB_OID))->stoid = 0xFFFFFFFFFFFFFFFF; \
}

#ifdef __cplusplus
}
#endif

#endif /* OID_H */

