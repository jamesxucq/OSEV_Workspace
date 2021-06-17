
/* 
 * File:   osev_result.h
 * Author: James Xu
 *
 * Created on 2017.4.27, PM3:03
 */

#ifndef REQU_RESP_H
#define REQU_RESP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
#include "commo_macro.h"

    //

    typedef struct {
        uint32 requ_type;
        int requ_len;
        char req_data[REQU_DATA_SIZE];
        FILE *requ_stre;
    } requ_data_t;

    //

    typedef struct {
        uint64 resp_len;
        char res_data[RESP_DATA_SIZE];
        FILE *resp_stre;
    } resp_data_t;




#ifdef __cplusplus
}
#endif

#endif /* REQU_RESP_H */

