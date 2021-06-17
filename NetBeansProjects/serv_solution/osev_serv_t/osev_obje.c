/* osev_obje.c
 * Created on: 2010-3-10
 * Author: Divad
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "server_macro.h"
#include "third_party.h" // test

#include "finalize.h"
#include "osev_obje.h"
#include "comdi_bzl.h"

//

static int hand_cons_memo_recv(struct _event *bev) {
    printf("hand_cons_memo_recv\n");
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) return HAND_FINISH;
    // _LOG_DEBUG("content_length:%d rwrite_tatol:%d", inval->content_length, sctrl->rwrite_tatol);
    // _LOG_DEBUG("blen:%d body_buffer:%d req_data:%d", evdat->blen, evdat->body_buffer, sctrl->req_data);
    memcpy(sctrl->recv_buffer, evdat->value_ptr, evdat->blen);
    //
    sctrl->rwrite_tatol += evdat->blen;
    if (inval->content_length != sctrl->rwrite_tatol)
        return HAND_UNDONE;
    return HAND_FINISH;
}

static int hand_cons_data_recv(struct _event *bev) {
    printf("hand_cons_data_recv\n");
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) return HAND_FINISH;
    // _LOG_DEBUG("content_length:%d rwrite_tatol:%d", inval->content_length, sctrl->rwrite_tatol);
    // _LOG_DEBUG("blen:%d body_buffer:%d req_data:%d", evdat->blen, evdat->body_buffer, sctrl->req_data);
    evdat->blen = fwrite(evdat->value_ptr, 0x01, evdat->blen, sctrl->requ_data);
    //
    sctrl->rwrite_tatol += evdat->blen;
    if (inval->content_length != sctrl->rwrite_tatol)
        return HAND_UNDONE;
    return HAND_FINISH;
}

static int(*recv_const_tab[])(struct _event*) = {
    hand_cons_memo_recv,
    hand_cons_memo_recv,
    hand_cons_memo_recv,
    hand_cons_memo_recv,
    hand_cons_data_recv,
    hand_cons_memo_recv,
    hand_cons_memo_recv,
    hand_cons_memo_recv
};

int hand_const_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    //
    int haval = recv_const_tab[inval->sentry](bev);
    if (!haval) FINAL_CONST_RECV(inval, sctrl, bev->seion->coval);
    return haval;
}

//

static int hand_quer_memo_recv(struct _event *bev) {
    printf("hand_quer_memo_recv\n");
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) return HAND_FINISH;
    // _LOG_DEBUG("content_length:%d rwrite_tatol:%d", inval->content_length, sctrl->rwrite_tatol);
    // _LOG_DEBUG("blen:%d body_buffer:%d req_data:%d", evdat->blen, evdat->body_buffer, sctrl->req_data);
    memcpy(sctrl->recv_buffer, evdat->value_ptr, evdat->blen);
    //
    sctrl->rwrite_tatol += evdat->blen;
    if (inval->content_length != sctrl->rwrite_tatol)
        return HAND_UNDONE;
    return HAND_FINISH;
}

static int hand_quer_data_recv(struct _event *bev) {
    printf("hand_quer_data_recv\n");
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) return HAND_FINISH;
    // _LOG_DEBUG("content_length:%d rwrite_tatol:%d", inval->content_length, sctrl->rwrite_tatol);
    // _LOG_DEBUG("blen:%d body_buffer:%d req_data:%d", evdat->blen, evdat->body_buffer, sctrl->req_data);
    evdat->blen = fwrite(evdat->value_ptr, 0x01, evdat->blen, sctrl->requ_data);
    //
    sctrl->rwrite_tatol += evdat->blen;
    if (inval->content_length != sctrl->rwrite_tatol)
        return HAND_UNDONE;
    return HAND_FINISH;
}

static int(*recv_query_tab[])(struct _event*) = {
    hand_quer_memo_recv,
    hand_quer_memo_recv,
    hand_quer_memo_recv,
    hand_quer_memo_recv,
    hand_quer_data_recv,
    hand_quer_memo_recv,
    hand_quer_memo_recv,
    hand_quer_memo_recv
};

//

int hand_query_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    //
    int haval = recv_query_tab[inval->sentry](bev);
    if (!haval) FINAL_QUERY_RECV(inval, sctrl, bev->seion->coval);
    return haval;
}

//
int(*recv_handler_tab[])(struct _event*) = {
    NULL, NULL, NULL, NULL,
    hand_const_recv,
    hand_query_recv
};

//

static int hand_cons_memo_send(struct _event *bev) {
    printf("hand_cons_memo_send\n");
    int send_valu = HAND_UNDONE;
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
    if (inval->content_length <= (sctrl->rwrite_tatol + evdat->blen)) {
        evdat->blen = inval->content_length - sctrl->rwrite_tatol;
        send_valu = HAND_FINISH;
    }
    // _LOG_DEBUG("send_valu:%d", send_valu);
    // _LOG_DEBUG("content_length:%d rwrite_tatol:%d", inval->content_length, sctrl->rwrite_tatol);
    // _LOG_DEBUG("blen:%d body_buffer:%d send_buffer:%d", evdat->blen, evdat->body_buffer, sctrl->send_buffer);
    memcpy(evdat->value_ptr, sctrl->send_buffer + sctrl->rwrite_tatol, evdat->blen);
    //
    sctrl->rwrite_tatol += evdat->blen;
    return send_valu;
}

static int hand_cons_data_send(struct _event *bev) {
    printf("hand_cons_data_send\n");
    int send_valu = HAND_UNDONE;
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
    if (inval->content_length <= (sctrl->rwrite_tatol + evdat->blen)) {
        evdat->blen = inval->content_length - sctrl->rwrite_tatol;
        send_valu = HAND_FINISH;
    }
    evdat->blen = fread(evdat->value_ptr, 0x01, evdat->blen, sctrl->resp_data);
    if (!evdat->blen) {
        _LOG_WARN("cons file error!");
    }
    // printf("evdat->blen:%llu\n", evdat->blen);
    // log_binary_file(evdat->value_ptr, evdat->blen, "./binary_code.bin_s");
    sctrl->rwrite_tatol += evdat->blen;
    return send_valu;
}

static int(*send_const_tab[])(struct _event*) = {
    hand_cons_memo_send,
    hand_cons_memo_send,
    hand_cons_memo_send,
    hand_cons_memo_send,
    hand_cons_data_send,
    hand_cons_data_send,
    hand_cons_data_send
};

int hand_const_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    //
    int haval = send_const_tab[inval->sentry](bev);
    if (!haval) FINAL_CONST_SEND(inval, &bev->seion->sctrl);
    return haval;
}

//

static int hand_quer_memo_send(struct _event *bev) {
    printf("hand_quer_memo_send\n");
    int send_valu = HAND_UNDONE;
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
// _LOG_DEBUG("evdat->blen:%d", evdat->blen);
    if (inval->content_length <= (sctrl->rwrite_tatol + evdat->blen)) {
        evdat->blen = inval->content_length - sctrl->rwrite_tatol;
        send_valu = HAND_FINISH;
    }
// _LOG_DEBUG("send_valu:%d", send_valu);
// _LOG_DEBUG("content_length:%d rwrite_tatol:%d", inval->content_length, sctrl->rwrite_tatol);
// _LOG_DEBUG("blen:%d body_buffer:%d send_buffer:%d", evdat->blen, evdat->value_ptr, sctrl->send_buffer);
    memcpy(evdat->value_ptr, sctrl->send_buffer + sctrl->rwrite_tatol, evdat->blen);
    //
    sctrl->rwrite_tatol += evdat->blen;
    return send_valu;
}

static int hand_quer_data_send(struct _event *bev) {
    printf("hand_quer_data_send\n");
    int send_valu = HAND_UNDONE;
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    //
    if (!inval->content_length) {
        evdat->blen = 0x00;
        return HAND_FINISH;
    }
    if (inval->content_length <= (sctrl->rwrite_tatol + evdat->blen)) {
        evdat->blen = inval->content_length - sctrl->rwrite_tatol;
        send_valu = HAND_FINISH;
    }
    evdat->blen = fread(evdat->value_ptr, 0x01, evdat->blen, sctrl->resp_data);
    if (!evdat->blen) {
        _LOG_WARN("quer file error!");
    }
    // printf("evdat->blen:%llu\n", evdat->blen);
    // log_binary_file(evdat->value_ptr, evdat->blen, "./binary_code.bin_s");
    sctrl->rwrite_tatol += evdat->blen;
    return send_valu;
}

static int(*send_query_tab[])(struct _event*) = {
    hand_quer_memo_send,
    hand_quer_memo_send,
    hand_quer_memo_send,
    hand_quer_memo_send,
    hand_quer_memo_send,
    hand_quer_data_send,
    hand_quer_data_send,
    hand_quer_data_send
};

int hand_query_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    //
    int haval = send_query_tab[inval->sentry](bev);
    if (!haval) FINAL_QUERY_SEND(inval, &bev->seion->sctrl);
    return haval;
}

//
int (*send_handler_tab[])(struct _event*) = {
    NULL, NULL, NULL, NULL,
    hand_const_send,
    hand_query_send,
};

//
