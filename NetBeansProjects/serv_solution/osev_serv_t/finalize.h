
/* 
 * File:   finalize.h
 * Author: James Xu
 *
 * Created on 2017.4.1, AM8:52
 */

#ifndef FINALIZE_H
#define FINALIZE_H

#include "comdi_bzl.h"
#include "session.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

#define FINAL_CONST_RECV(INVAL, SCTRL, COVAL) { \
    CREATE_SDRESP(INVAL, SCTRL) \
    RESET_CONST_SE(sctrl) \
    if (hand_const_bzl(INVAL->sentry, &sresp, (void *) COVAL, &INVAL->oid, INVAL->paras)) { \
        SCTRL->status_code = BAD_REQUEST; \
        return HAND_FINISH; \
    } \
}

#define FINAL_QUERY_RECV(INVAL, SCTRL, COVAL) { \
    CREATE_SDRESP(INVAL, SCTRL) \
    RESET_QUERY_SE(sctrl) \
    if (hand_query_bzl(INVAL->sentry, &sresp, (void *) COVAL, INVAL->paras)) { \
        SCTRL->status_code = BAD_REQUEST; \
        return HAND_FINISH; \
    } \
}

    //
#define FINAL_CONST_SEND(INVAL, SCTRL) { \
/* _LOG_INFO("xxx 1 inval->sub_entry:%d inval->svalue%d", inval->sub_entry, inval->svalue); */ \
    close_const_se[INVAL->sentry](SCTRL); \
/* _LOG_INFO("xxx 2"); */ \
}

    //
#define FINAL_QUERY_SEND(INVAL, SCTRL) { \
/* _LOG_INFO("xxx 1 inval->sub_entry:%d inval->svalue%d", inval->sub_entry, inval->svalue); */ \
    close_query_se[INVAL->sentry](SCTRL); \
/* _LOG_INFO("xxx 2"); */ \
}

#ifdef __cplusplus
}
#endif

#endif /* FINALIZE_H */

