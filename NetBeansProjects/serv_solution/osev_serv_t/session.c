
#include "authen_bzl.h"
#include "privile_bzl.h"
#include "comdi_bzl.h"
#include "rstat_bzl.h"

#include "session.h"
#include "conoda.h"

//

int open_authen_se(session *seion, seion_ctrl *sctrl, inte_value *inval) {
    _LOG_TRACE("open authe session.");
    printf("[DEBUG] osev_osdb:|%s| user_name:|%s|\n", inval->paras[APARA_OSEV_OSDB], inval->paras[APARA_USER_NAME]);
    char temp[33];
    strzcpy(temp, inval->paras[APARA_REQU_VALID], 32);
    printf("[DEBUG] inval->req_valid:|%s|\n", temp);
    //
    CREATE_SDRESP(inval, sctrl)
#ifdef NOAUTH
            if (hand_noauth_bzl(&sresp, seion, sctrl, inval)) {
        sctrl->status_code = BAD_REQUEST;
        return ERR_FAULT;
    }
#else
            if (hand_authen_bzl(&sresp, seion, sctrl, inval)) {
        sctrl->status_code = BAD_REQUEST;
        return ERR_FAULT;
    }
#endif
    //
    return ERR_SUCCESS;
}

void open_kalive_se(seion_ctrl *sctrl) {
    _LOG_TRACE("open kalive session.");
}

//
#ifdef NOAUTH
#define CHECK_OSEV_PRIVILE(SCTRL, LDATA, PRIVI)
#else
#define CHECK_OSEV_PRIVILE(SCTRL, LDATA, PRIVI) { \
    if (osev_privile_bzl(LDATA->use_privi, PRIVI)) { \
        SCTRL->status_code = FORBIDDEN; \
        return ERR_FAULT; \
    } \
}
#endif

int open_status_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval) {
    _LOG_TRACE("open status session.");
    //
    CREATE_SDRESP(inval, sctrl)
    if (inval->sentry) {
        CHECK_OSEV_PRIVILE(sctrl, ldata, DPRIV_STATU)
        if (hand_dstatu_bzl(inval->svalue, &sresp, inval->paras)) {
            sctrl->status_code = BAD_REQUEST;
            return ERR_FAULT;
        }
    } else {
        CHECK_OSEV_PRIVILE(sctrl, ldata, OPRIV_STATU)
        if (hand_ostatu_bzl(inval->svalue, &sresp, inval->paras)) {
            sctrl->status_code = BAD_REQUEST;
            return ERR_FAULT;
        }
    }
    //
    return ERR_SUCCESS;
}

int open_privile_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval) {
    _LOG_TRACE("open privile session.");
    //
    CREATE_SDRESP(inval, sctrl)
    if (inval->sentry) {
        CHECK_OSEV_PRIVILE(sctrl, ldata, DPRIV_PRIVI)
        if (hand_dprivi_bzl(inval->svalue, &sresp, inval->paras)) {
            sctrl->status_code = BAD_REQUEST;
            return ERR_FAULT;
        }
    } else {
        CHECK_OSEV_PRIVILE(sctrl, ldata, OPRIV_PRIVI)
        if (hand_oprivi_bzl(inval->svalue, &sresp, inval->paras)) {
            sctrl->status_code = BAD_REQUEST;
            return ERR_FAULT;
        }
    }
    //
    return ERR_SUCCESS;
}

// destination
#ifdef NOAUTH
#define CHECK_LEVIN_PRIVILE(SCTRL, LDATA, DESTI, PRIVI)
#else
#define CHECK_LEVIN_PRIVILE(SCTRL, LDATA, DESTI, PRIVI) { \
    if (levin_privile_bzl(LDATA->use_privi, DESTI, PRIVI)) { \
        SCTRL->status_code = FORBIDDEN; \
        return ERR_FAULT; \
    } \
}
#endif

int open_invoke_se(seion_ctrl *sctrl, list_data *ldata, conoda *coval, inte_value *inval) {
    _LOG_TRACE("open invoke session.");
    //
    CREATE_SDRESP(inval, sctrl) // 
    CHECK_LEVIN_PRIVILE(sctrl, ldata, &ldata->oid, MPRIV_INVOK(inval->sentry))
    if (hand_invok_bzl(inval->sentry, &sresp, &coval->hando, &coval->handa, ldata->osev_osdb, inval->paras)) {
        sctrl->status_code = BAD_REQUEST;
        return ERR_FAULT;
    }
    //
    return ERR_SUCCESS;
}

int open_colle_se(seion_ctrl *sctrl, list_data *ldata, conoda *coval, inte_value *inval) {
    _LOG_TRACE("open colle session.");
    //
    CREATE_SDRESP(inval, sctrl) // 
    CHECK_LEVIN_PRIVILE(sctrl, ldata, &ldata->oid, CPRIV_INVOK(inval->sentry))
    if (hand_colle_bzl(inval->sentry, &sresp, &coval->hando, &coval->handa, ldata->osev_osdb, inval->paras)) {
        sctrl->status_code = BAD_REQUEST;
        return ERR_FAULT;
    }
    //
    return ERR_SUCCESS;
}

//

#ifdef NOAUTH
#define CHECK_LEVCQ_PRIVILE(SCTRL, LDATA, OLEVE, DESTI, PRIVI)
#else
#define CHECK_LEVCQ_PRIVILE(SCTRL, LDATA, OLEVE, DESTI, PRIVI) { \
    if (levcq_privile_bzl(LDATA->use_privi, OLEVE, DESTI, PRIVI)) { \
        SCTRL->status_code = FORBIDDEN; \
        return ERR_FAULT; \
    } \
}
#endif

//

static int open_cons_memo(seion_ctrl *sctrl) {
    _LOG_DEBUG("open_cons_memo. OK!");
    return ERR_SUCCESS;
}

static int open_cons_resp(seion_ctrl *sctrl) {
    if (!(sctrl->resp_data = tmpfile64())) return ERR_FAULT;
    _LOG_DEBUG("open_cons_resp. OK!");
    return ERR_SUCCESS;
}

static int open_cons_qusp(seion_ctrl *sctrl) {
    if (!(sctrl->requ_data = tmpfile64())) return ERR_FAULT;
    if (!(sctrl->resp_data = tmpfile64())) return ERR_FAULT;
    _LOG_DEBUG("open_cons_qusp. OK!");
    return ERR_SUCCESS;
}

static int (*open_const_tab[])(seion_ctrl*) = {
    open_cons_memo,
    open_cons_memo,
    open_cons_memo,
    open_cons_memo,
    open_cons_qusp,
    open_cons_resp,
    open_cons_resp,
};

//

int open_const_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval) {
    _LOG_TRACE("open query session.");
    // check privileges
    CHECK_LEVCQ_PRIVILE(sctrl, ldata, &ldata->oid, &inval->oid, &PRIVI_CONST(inval->svalue))
    open_const_tab[inval->sentry](sctrl);
    //
    return ERR_SUCCESS;
}

//

static int open_quer_memo(seion_ctrl *sctrl) {
    _LOG_DEBUG("open_quer_memo. OK!");
    return ERR_SUCCESS;
}

static int open_quer_resp(seion_ctrl *sctrl) {
    if (!(sctrl->resp_data = tmpfile64())) return ERR_FAULT;
    _LOG_DEBUG("open_quer_resp. OK!");
    return ERR_SUCCESS;
}

static int (*open_query_tab[])(seion_ctrl*) = {
    open_quer_memo,
    open_quer_memo,
    open_quer_memo,
    open_quer_memo,
    open_quer_memo,
    open_quer_resp,
    open_quer_resp,
    open_quer_resp,
};

//

int open_query_se(seion_ctrl *sctrl, list_data *ldata, inte_value *inval) {
    _LOG_TRACE("open query session.");
    // check privileges
    CHECK_LEVCQ_PRIVILE(sctrl, ldata, &ldata->oid, &inval->oid, &PRIVI_QUERY(inval->svalue))
    open_query_tab[inval->sentry](sctrl);
    //
    return ERR_SUCCESS;
}

//

static void close_cons_memo(seion_ctrl * sctrl) {
    _LOG_TRACE("close query session.");
    // _LOG_TRACE("close glist invalid session");
    BZERO_SCTRL(sctrl)
}

static void close_cons_data(seion_ctrl * sctrl) {
    _LOG_TRACE("close query session.");
    // _LOG_TRACE("close get list session. get list send file count:%d", sctrl->rwrite_tatol);
    FCLOSE_SAFETY(sctrl->resp_data);
    BZERO_SCTRL(sctrl)
}

static void close_cons_qusp(seion_ctrl * sctrl) {
    _LOG_TRACE("close query session.");
    // _LOG_TRACE("close get list session. get list send file count:%d", sctrl->rwrite_tatol);
    FCLOSE_SAFETY(sctrl->resp_data);
    FCLOSE_SAFETY(sctrl->requ_data);
    BZERO_SCTRL(sctrl)
}

void (*close_const_se[]) (seion_ctrl *) = {
    close_cons_memo,
    close_cons_memo,
    close_cons_memo,
    close_cons_memo,
    close_cons_qusp,
    close_cons_data,
    close_cons_data,
};

//

static void close_query_memo(seion_ctrl * sctrl) {
    _LOG_TRACE("close query session.");
    // _LOG_TRACE("close glist invalid session");
    BZERO_SCTRL(sctrl)
}

static void close_query_data(seion_ctrl * sctrl) {
    _LOG_TRACE("close query session.");
    // _LOG_TRACE("close get list session. get list send file count:%d", sctrl->rwrite_tatol);
    FCLOSE_SAFETY(sctrl->resp_data);
    BZERO_SCTRL(sctrl)
}

void (*close_query_se[]) (seion_ctrl *) = {
    close_query_memo,
    close_query_memo,
    close_query_memo,
    close_query_memo,
    close_query_memo,
    close_query_data,
    close_query_data,
    close_query_data
};

//

void open_done_se(seion_ctrl *sctrl, list_data *ldata) {
    _LOG_TRACE("open done session.");
    if (erase_auth_cache_end(ldata->_action_key_))
        sctrl->status_code = INTERNAL_SERVER_ERROR;
}