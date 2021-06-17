
/* 
 * File:   resp_conne.h
 * Author: Administrator
 *
 * Created on 2016.12.28, AM 9:17
 */

#ifndef RESP_CONNE_H
#define RESP_CONNE_H

#include "commo_macro.h"
#include "ostproto.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

    typedef struct {
        STATUS_CODE status;
        uint64 length;
    } resp_tyle_t;
#pragma pack()

    // response

#ifdef __cplusplus
}
#endif

#endif /* RESP_CONNE_H */

