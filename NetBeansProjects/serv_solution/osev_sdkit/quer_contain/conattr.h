
/* 
 * File:   conattr.h
 * Author: James Xu
 *
 * Created on 2017.2.11, AM 8:27
 */

#ifndef CONATTR_H
#define CONATTR_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

//
int creat_cattr(char *osdb);
int addi_cattr(char *cont_name, uint32 stora_type, char *data_type, char *osdb);
int dele_cattr(char *cont_name, char *osdb);
int find_cattr(osv_oid_t *oid, char *data_type, char *cont_name, char *osdb);
int sear_cattr(char *resu, char *osdb, char *cont_name, char *data_type);

//
cont_list *load_cattr_osdb(char *osdb);

#ifdef __cplusplus
}
#endif

#endif /* CONATTR_H */

