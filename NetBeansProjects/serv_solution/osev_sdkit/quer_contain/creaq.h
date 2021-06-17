
/* 
 * File:   creaq.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:14
 */

#ifndef CREAQ_H
#define CREAQ_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception
    int qcreat_conta_obje(riv_sessi_t *seion, rive_ha *stora_ha, char *osdb, char *cont_name, uint32 conta_type, char *clas_type);


#ifdef __cplusplus
}
#endif

#endif /* CREAQ_H */

