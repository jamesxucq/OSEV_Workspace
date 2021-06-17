
/* 
 * File:   ostp_utili.h
 * Author: James Xu
 *
 * Created on 2016.12.28, PM 1:55
 */

#ifndef OSTP_UTILI_H
#define OSTP_UTILI_H

#include "event.h"

#ifdef __cplusplus
extern "C" {
#endif

    //    
#define ONLY_HEADER_SECTION  0

    //

    //
#define PARSE_AUTHEN_RECV(INVAL, EVDAT, SCTRL) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
    if(EVDAT.blen != INVAL->content_length) { \
        SCTRL->status_code = INTERNAL_SERVER_ERROR; \
        return LOOP_STOP; \
    } \
}

    void build_authen_send(struct evdata *evdat, uchar status_code, inte_value *inval);

    //
#define PARSE_KALIVE_RECV(INVAL, EVDAT, SCTRL) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
    if(EVDAT.blen != INVAL->content_length) { \
        SCTRL->status_code = INTERNAL_SERVER_ERROR; \
        return LOOP_STOP; \
    } \
}

#define BUILD_KALIVE_SEND(EVDAT, SCTRL) { \
    resp_tyle_t kalive; \
    kalive.status = SCTRL->status_code; \
    kalive.length = 0x00; \
    memcpy((char *)EVDAT->type_ptr, &kalive, sizeof(resp_tyle_t)); \
    EVDAT->hlen = sizeof(resp_tyle_t); \
    EVDAT->blen = ONLY_HEADER_SECTION; \
}

    //
#define PARSE_STATU_RECV(INVAL, EVDAT, SCTRL) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
    if(EVDAT.blen != INVAL->content_length) { \
        SCTRL->status_code = INTERNAL_SERVER_ERROR; \
        return LOOP_STOP; \
    } \
}

    void build_status_send(struct evdata *EVDAT, uchar status_code, inte_value *INVAL);

    //
#define PARSE_PRIVI_RECV(INVAL, EVDAT, SCTRL) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
    if(EVDAT.blen != INVAL->content_length) { \
        SCTRL->status_code = INTERNAL_SERVER_ERROR; \
        return LOOP_STOP; \
    } \
}

    void build_privile_send(struct evdata *EVDAT, uchar status_code, inte_value *INVAL);

    //
#define PARSE_INVOK_RECV(INVAL, EVDAT, SCTRL) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
    if(EVDAT.blen != INVAL->content_length) { \
        SCTRL->status_code = INTERNAL_SERVER_ERROR; \
        return LOOP_STOP; \
    } \
}

    void build_invoke_send(struct evdata *evdat, uchar status_code, inte_value *inval);

    //
#define PARSE_COLLE_RECV(INVAL, EVDAT, SCTRL) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
    if(EVDAT.blen != INVAL->content_length) { \
        SCTRL->status_code = INTERNAL_SERVER_ERROR; \
        return LOOP_STOP; \
    } \
}
    
    void build_colle_send(struct evdata *evdat, uchar status_code, inte_value *inval);
    
    //
#define PARSE_CONST_RECV(INVAL, EVDAT) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
}

    void build_const_send(struct evdata *evdat, uchar status_code, inte_value *inval);

    //
#define PARSE_QUERY_RECV(INVAL, EVDAT) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
}

    void build_query_send(struct evdata *evdat, uchar status_code, inte_value *inval);

    //
#define PARSE_DONE_RECV(INVAL, EVDAT, SCTRL) { \
    INVAL->content_length = ((requ_tyle_t *)EVDAT.type_ptr)->length; \
    if(EVDAT.blen != INVAL->content_length) { \
        SCTRL->status_code = INTERNAL_SERVER_ERROR; \
        return LOOP_STOP; \
    } \
}

#define BUILD_DONE_SEND(EVDAT, SCTRL) { \
    resp_tyle_t done; \
    done.status = SCTRL->status_code; \
    done.length = 0x00; \
    memcpy((char *)EVDAT->type_ptr, &done, sizeof(resp_tyle_t)); \
    EVDAT->hlen = sizeof(resp_tyle_t); \
    EVDAT->blen = ONLY_HEADER_SECTION; \
}


#ifdef __cplusplus
}
#endif

#endif /* OSTP_UTILI_H */

