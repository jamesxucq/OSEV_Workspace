/*
 * File:   event.h
 * Author: James Xu
 *
 * Created on 2012
 */

#ifndef EVENT_H
#define EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "session.h"

    //

    struct evdata {
        BYTE *type_ptr;
        size_t hlen;
        BYTE *value_ptr;
        size_t blen;
    };

    struct _event {
        session *seion;
        int loop_continue; // 1:continue read or write , 0 change read or write
        struct evdata evdat;
        uint32 method;
        int (*handle[5])(struct _event *);
    };
    typedef void (*excep)(session *);
    typedef int (*event)(struct _event *);
    //
#define CREATE_EVENT(BEV) \
    BEV = (struct _event *) malloc(sizeof (struct _event)); \
    if(!BEV) return ERR_FAULT; \
    memset(BEV, '\0', sizeof (struct _event)); \
    BEV->seion = (session *) malloc(sizeof (session)); \
    if(!BEV->seion) { \
        free(BEV); \
        return ERR_FAULT; \
    } \
    memset(BEV->seion, '\0', sizeof (session));

#define DESTROY_EVENT(BEV) \
    if(BEV->seion) free(BEV->seion); \
    BEV->seion = NULL; \
    if(BEV) return free(BEV); \
    BEV = NULL;

#define INITIAL_EVENT(BEV) \
    memset(BEV->seion, '\0', sizeof (session));

    //
#include "osev_obje.h"

#define INITIAL_EVENT_HANDLE(handle, method) \
    handle[0x00] = recv_initialize_tab[method]; \
    handle[0x01] = recv_handler_tab[method]; \
    handle[0x02] = send_initialize_tab[method]; \
    handle[0x03] = send_handler_tab[method]; \
    handle[0x04] = (event)exception_tab[method];

#ifdef __cplusplus
}
#endif

#endif /* EVENT_H */

