
/* 
 * File:   rive_bzl.h
 * Author: James Xu
 *
 * Created on 2017.2.7, PM 2:29
 */

#ifndef RIVE_BZL_H
#define RIVE_BZL_H

#include "sess_list.h"
#include "rive_stru.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int rivbzl_create(char *data_directory);
    int rivbzl_destroy();
    int open_rive_bzl(rive_conne *rvcon, char *osdb);
    int close_rive_bzl(rive_conne *rvcon);

    //
#define activ_seion_bzl(slsth, stora_ha, conne)     activ_seion(slsth, stora_ha, conne)
#define quiet_seion_bzl(slsth, slist)   quiet_seion(slsth, slist)
#define destroy_seion_bzl(slist, stora_ha)   destroy_seion(slist, stora_ha)

    //
#define ENGINE_COUNT 0x01

    //
#define SHAPE_ENAME "shape" // only object server    
#define IMEMO_ENAME "imemo"
#define LEAP_ENAME "leap"
#define WTIGER_ENAME "wiredtiger" // wiredtiger

    //
    //#define ENGINE_IMEMO 0x00
    //#define ENGINE_LEAP 0x01
    //#define ENGINE_WTIGER 0x02
#define ENGINE_WTIGER 0x00

    extern rive_ha *_storage_ha_[];

    //

#ifdef __cplusplus
}
#endif

#endif /* RIVE_BZL_H */

