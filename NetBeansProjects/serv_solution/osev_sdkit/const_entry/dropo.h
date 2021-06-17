
/* 
 * File:   dropo.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:01
 */

#ifndef DROPO_H
#define DROPO_H

#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

//
    // -1:error 0x00:ok 0x01:exception
int drop_entity_obje(rive_conne *rvcon, contain *conta, hand_data *handa, char **paras);


#ifdef __cplusplus
}
#endif

#endif /* DROPO_H */

