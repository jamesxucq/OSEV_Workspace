
/* 
 * File:   oattri.h
 * Author: James Xu
 *
 * Created on 2017.5.25, PM1:56
 */

#ifndef OATTRI_H
#define OATTRI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define OSDB_ATTRIB        "osdb_attri.sdo"
    
    //
    int creat_osdb_attri(char *oattr_path, char *osdb);
    // CREAT_OSDB_SUBPA(data_path, osdb, OSDB_ATTRIB)
    int parse_osdb_attri(osv_oid_t *obje_oid, char *osdb);


#ifdef __cplusplus
}
#endif

#endif /* OATTRI_H */

