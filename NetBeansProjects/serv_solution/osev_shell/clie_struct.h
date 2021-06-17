
/* 
 * File:   shell_stru.h
 * Author: James Xu
 *
 * Created on 2017.1.17, PM 3:19
 */

#ifndef CLIE_STRUCT_H
#define CLIE_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "osev_clie.h"
#include "stri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    typedef struct {
        uint32 shell_mode;
        uint32 run_level;
    } shel_stat_t;

    typedef struct {
        int resu_type; // 0x00:memory 0x01:stre
        char resu_data[RESP_DATA_SIZE];
        uint64 res_len;
        int res_fde;
    } shel_resu;

    int resu_initial(shel_resu *resu);
    void reset_result(shel_resu *resu);
    void final_result(shel_resu *resu);

    //

#pragma pack(1)

    typedef struct {
        unsigned int osev_unique;
        unsigned int time_stamp;
        unsigned int counter;
    } she_oid_t;
#pragma pack()

#ifdef __cplusplus
}
#endif

#endif /* CLIE_STRUCT_H */

