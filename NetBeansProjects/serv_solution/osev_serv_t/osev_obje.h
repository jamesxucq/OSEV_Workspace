/* osev_obje.c
 * Created on: 2010-3-10
 * Author: Divad
 */
#ifndef OSEV_OBJE_H
#define OSEV_OBJE_H

//

#include "commo_header.h"
#include "parse_conf.h"
#include "event.h"
#include "options.h"

#ifdef __cplusplus
extern "C" {
#endif

    /* handle recv  */

    //
    int hand_const_recv(struct _event *bev);
    int hand_query_recv(struct _event *bev);

    extern int(*recv_handler_tab[])(struct _event*);

    /* creat send */
#define HAND_AUTHEN_SEND(EVDAT, SCTRL, INVAL) \
    memcpy((char *) EVDAT.value_ptr, SCTRL->send_buffer, INVAL->content_length); \
    EVDAT.blen = INVAL->content_length;

#define HAND_STATUS_SEND(EVDAT, SCTRL, INVAL) \
    memcpy((char *) EVDAT.value_ptr, SCTRL->send_buffer, INVAL->content_length); \
    EVDAT.blen = INVAL->content_length;
    
#define HAND_PRIVILE_SEND(EVDAT, SCTRL, INVAL) \
    memcpy((char *) EVDAT.value_ptr, SCTRL->send_buffer, INVAL->content_length); \
    EVDAT.blen = INVAL->content_length;

#define HAND_INVOKE_SEND(EVDAT, SCTRL, INVAL) \
    memcpy((char *) EVDAT.value_ptr, SCTRL->send_buffer, INVAL->content_length); \
    EVDAT.blen = INVAL->content_length;
    
#define HAND_COLLE_SEND(EVDAT, SCTRL, INVAL) \
    memcpy((char *) EVDAT.value_ptr, SCTRL->send_buffer, INVAL->content_length); \
    EVDAT.blen = INVAL->content_length;

    //
    int hand_const_send(struct _event *bev);
    int hand_query_send(struct _event *bev);

    extern int(*send_handler_tab[])(struct _event*);

    //

#ifdef __cplusplus
}
#endif

#endif /* OSEV_OBJE_H */

