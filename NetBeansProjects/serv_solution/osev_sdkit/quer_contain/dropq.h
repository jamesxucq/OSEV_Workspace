
/* 
 * File:   dropq.h
 * Author: James Xu
 *
  * Created on 2017.4.11, AM10:14
 */

#ifndef DROPQ_H
#define DROPQ_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception
    int drop_conta_obje(riv_sessi_t *seion, rive_ha *stora_ha, char *osdb_name, char *table);


#ifdef __cplusplus
}
#endif

#endif /* DROPQ_H */

