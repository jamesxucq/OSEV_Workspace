
#include "osev_serv.h"
#include "osev_bzl.h"

#include "hand_epoll.h"
#include "commo_header.h"
#include "ostp_utili.h"
#include "comdi_bzl.h"
#include "session.h"
#include "osev_struct.h"


#define EXCEP_EXIT(SCTRL, STATUS) { \
    SCTRL->status_code = STATUS; \
    return LOOP_STOP; \
}
//
#define INIT_STATUS_OKAY(ctrl) ctrl->status_code = OK;

//epoll serv handle recv and create send

static int authen_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_AUTHEN_RECV(inval, bev->evdat, sctrl);
    if (inte_authen_bzl(inval, (struct authe_ine *) bev->evdat.value_ptr, (char *) (bev->evdat.value_ptr + sizeof (struct authe_ine))))
        EXCEP_EXIT(sctrl, BAD_REQUEST)
        open_authen_se(bev->seion, sctrl, inval);
    //
    return LOOP_STOP;
}

static int kalive_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_KALIVE_RECV(inval, bev->evdat, sctrl);
    if (inte_kalive_bzl(inval)) EXCEP_EXIT(sctrl, BAD_REQUEST)
        open_kalive_se(sctrl);
    //
    return LOOP_STOP;
}

static int status_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_STATU_RECV(inval, bev->evdat, sctrl);
    if (inte_status_bzl(inval, (statu_ine *) bev->evdat.value_ptr, (char *) (bev->evdat.value_ptr + sizeof (statu_ine))))
        EXCEP_EXIT(sctrl, BAD_REQUEST)
        open_status_se(sctrl, bev->seion->ldata, inval);
    //
    return LOOP_STOP;
}

static int privi_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_PRIVI_RECV(inval, bev->evdat, sctrl);
    if (inte_privile_bzl(inval, (privi_ine *) bev->evdat.value_ptr, (char *) (bev->evdat.value_ptr + sizeof (statu_ine))))
        EXCEP_EXIT(sctrl, BAD_REQUEST)
        open_privile_se(sctrl, bev->seion->ldata, inval);
    //
    return LOOP_STOP;
}

static int invoke_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_INVOK_RECV(inval, bev->evdat, sctrl);
    if (inte_invoke_bzl(inval, (invok_ine *) bev->evdat.value_ptr, (char *) (bev->evdat.value_ptr + sizeof (invok_ine))))
        EXCEP_EXIT(sctrl, BAD_REQUEST)
        open_invoke_se(sctrl, bev->seion->ldata, bev->seion->coval, inval);
    //
    return LOOP_STOP;
}

static int colle_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_COLLE_RECV(inval, bev->evdat, sctrl);
    if (inte_colle_bzl(inval, (colle_ine *) bev->evdat.value_ptr, (char *) (bev->evdat.value_ptr + sizeof (colle_ine))))
        EXCEP_EXIT(sctrl, BAD_REQUEST)
        open_colle_se(sctrl, bev->seion->ldata, bev->seion->coval, inval);
    //
    return LOOP_STOP;
}

static int const_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_CONST_RECV(inval, bev->evdat);
    if (inte_const_bzl(inval, (const_ine *) bev->evdat.value_ptr, (char *) (bev->evdat.value_ptr + sizeof (query_ine))))
        EXCEP_EXIT(sctrl, BAD_REQUEST)
        if (open_const_se(sctrl, bev->seion->ldata, inval)) return LOOP_STOP;
    if (hand_const_recv(bev)) return LOOP_CONTINUE;
    //
    return LOOP_STOP;
}

static int query_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_QUERY_RECV(inval, bev->evdat);
    if (inte_query_bzl(inval, (query_ine *) bev->evdat.value_ptr, (char *) (bev->evdat.value_ptr + sizeof (query_ine))))
        EXCEP_EXIT(sctrl, BAD_REQUEST)
        if (open_query_se(sctrl, bev->seion->ldata, inval)) return LOOP_STOP;
    if (hand_query_recv(bev)) return LOOP_CONTINUE;
    //
    return LOOP_STOP;
}

static int done_recv(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    INIT_STATUS_OKAY(sctrl)
    //
    PARSE_DONE_RECV(inval, bev->evdat, sctrl);
    if (inte_done_bzl(inval)) EXCEP_EXIT(sctrl, BAD_REQUEST)
        open_done_se(sctrl, bev->seion->ldata);
    //
    return LOOP_STOP;
}

//
int (*recv_initialize_tab[])(struct _event*) = {
    authen_recv,
    kalive_recv,
    status_recv,
    privi_recv,
    invoke_recv,
    colle_recv,
    const_recv,
    query_recv,
    done_recv
};

//

static int authen_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    build_authen_send(&bev->evdat, sctrl->status_code, inval);
    _LOG_DEBUG("hand authen send!");
    HAND_AUTHEN_SEND(bev->evdat, sctrl, inval)
    //
    CLOSE_AUTHEN_SE(sctrl);
    return LOOP_STOP;
}

static int kalive_send(struct _event *bev) {
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    BUILD_KALIVE_SEND(evdat, sctrl)
    //
    CLOSE_KALIVE_SE(sctrl);
    return LOOP_STOP;
}

static int status_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    build_status_send(&bev->evdat, sctrl->status_code, inval);
    _LOG_DEBUG("hand status send!");
    HAND_STATUS_SEND(bev->evdat, sctrl, inval)
    //
    CLOSE_STATUS_SE(sctrl)
    return LOOP_STOP;
}

static int privi_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    build_privile_send(&bev->evdat, sctrl->status_code, inval);
    _LOG_DEBUG("hand privile send!");
    HAND_PRIVILE_SEND(bev->evdat, sctrl, inval)
    //
    CLOSE_PRIVILE_SE(sctrl)
    return LOOP_STOP;
}

static int invoke_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    //
    build_invoke_send(&bev->evdat, sctrl->status_code, inval);
    _LOG_DEBUG("hand invoke send!");
    HAND_INVOKE_SEND(bev->evdat, sctrl, inval)
    //
    CLOSE_INVOKE_SE(sctrl)
    return LOOP_STOP;
}

static int colle_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    //
    build_colle_send(&bev->evdat, sctrl->status_code, inval);
    _LOG_DEBUG("hand colle send!");
    HAND_COLLE_SEND(bev->evdat, sctrl, inval)
    //
    CLOSE_COLLE_SE(sctrl)
    return LOOP_STOP;
}

static int const_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    //
    build_const_send(&bev->evdat, sctrl->status_code, inval);
    _LOG_DEBUG("hand const send!");
    if (hand_const_send(bev)) return LOOP_CONTINUE;
    //
    return LOOP_STOP;
}

static int query_send(struct _event *bev) {
    inte_value *inval = &bev->seion->inval;
    seion_ctrl *sctrl = &bev->seion->sctrl;
    //
    build_query_send(&bev->evdat, sctrl->status_code, inval);
    _LOG_DEBUG("hand query send!");
    if (hand_query_send(bev)) return LOOP_CONTINUE;
    //
    return LOOP_STOP;
}

static int done_send(struct _event *bev) {
    seion_ctrl *sctrl = &bev->seion->sctrl;
    struct evdata *evdat = &bev->evdat;
    BUILD_DONE_SEND(evdat, sctrl)
    //
    CLOSE_DONE_SE(sctrl)
    return LOOP_STOP;
}

int (*send_initialize_tab[])(struct _event*) = {
    authen_send,
    kalive_send,
    status_send,
    privi_send,
    invoke_send,
    colle_send,
    const_send,
    query_send,
    done_send
};
