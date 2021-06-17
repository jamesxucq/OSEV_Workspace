
/* 
 * File:   oid.h
 * Author: Administrator
 *
 * Created on 2017.9.4, AM10:34
 */

#ifndef OID_H
#define OID_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#pragma pack(1)

    typedef struct {
        unsigned int mach_unique; // machine_unique
        unsigned long long stoid;
    } osv_oid_i;
#pragma pack()

    //

#pragma pack(1)

    typedef struct {
        unsigned int mach_unique; // machine_unique
        unsigned int time_stamp;
        unsigned int counter;
    } osv_oid_t;
#pragma pack()

    //
    osv_oid_t *creat_objeid_obj(osv_oid_t *obje_id);

    //
#define OID_BINARY_LEN      12
#define OID_LINE_LEN        25

    //
    osv_oid_t *stroid(osv_oid_t *obje_id, char *oid_stri);
    char *oidstr(char *oid_stri, osv_oid_t *obje_id);

    //

#ifdef __cplusplus
}
#endif

#endif /* OID_H */

