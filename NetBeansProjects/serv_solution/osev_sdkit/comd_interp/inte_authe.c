#include "commo_header.h"
#include "istri_utili.h"

#include "rstat_bzl.h"
#include "authen_bzl.h"
#include "conoda_bzl.h"
#include "inte_authe.h"

//

char *parse_authen(char *data_line, char **paras, char *requ_data) {
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_stri(data_line, paras + 0x00, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

//

int hand_authen(prod_data *sresp, session *seion, seion_ctrl *sctrl, inte_value *inval) {
    // _LOG_INFO("osev enable authen mode.");
    list_data *ldata;
    //
    if (inval->sentry) {
        if (valid_open_bzl(inval->paras[APARA_OSEV_OSDB])) {
            PDAT_EXCEP_TAIL(sresp, OPEN_ODB_EXCE)
            return -1;
        } else {
            seion->coval = find_conto_bzl(inval->paras[APARA_OSEV_OSDB]);
            if ((ldata = osdb_ldata_bzl(inval->paras[APARA_ACTION_KEY], inval->paras[APARA_USER_NAME], &seion->coval->oid, inval->paras[APARA_OSEV_OSDB]))) {
                seion->ldata = ldata;
                if (check_reque_bzl(ldata->auth_valid, inval->paras[APARA_REQU_VALID], inval->paras[APARA_REQU_SALT])) {
                    // _LOG_INFO("sctrl->seion_id:%s, inval->seion_id:%s", sctrl->seion_id, inval->seion_id); // delete by james 20130409
                    erase_auth_cache_end(ldata->_action_key_);
                    sctrl->status_code = UNAUTHORIZED;
                    PDAT_NONE_TAIL(sresp)
                } else {
                    memcpy(sresp->sebuf, &ldata->oid, sizeof (osv_oid_t));
                    (sresp->colen)[0x00] = sizeof (osv_oid_t);
                }
            } else {
                sctrl->status_code = UNAUTHORIZED;
                PDAT_NONE_TAIL(sresp)
            }
        }
    } else {
        if ((ldata = osev_ldata_bzl(inval->paras[APARA_ACTION_KEY], inval->paras[APARA_USER_NAME]))) {
            seion->ldata = ldata;
            if (check_reque_bzl(ldata->auth_valid, inval->paras[APARA_REQU_VALID], inval->paras[APARA_REQU_SALT])) {
                // _LOG_INFO("sctrl->seion_id:%s, inval->seion_id:%s", sctrl->seion_id, inval->seion_id); // delete by james 20130409
                erase_auth_cache_end(ldata->_action_key_);
                sctrl->status_code = UNAUTHORIZED;
                PDAT_NONE_TAIL(sresp)
            } else {
                memcpy(sresp->sebuf, &ldata->oid, sizeof (osv_oid_t));
                (sresp->colen)[0x00] = sizeof (osv_oid_t);
            }
        } else {
            sctrl->status_code = UNAUTHORIZED;
            PDAT_NONE_TAIL(sresp)
        }
    }
    //
    return 0x00;
}

//

int hand_noauth(prod_data *sresp, session *seion, seion_ctrl *sctrl, inte_value *inval) {
    // _LOG_INFO("osev disable authen mode.");
    list_data *ldata;
    //
    if (inval->sentry) {
        if (valid_open_bzl(inval->paras[APARA_OSEV_OSDB])) {
            PDAT_EXCEP_TAIL(sresp, OPEN_ODB_EXCE)
            return -1;
        } else {
            seion->coval = find_conto_bzl(inval->paras[APARA_OSEV_OSDB]);
            if ((ldata = odbn_ldata_bzl(inval->paras[APARA_ACTION_KEY], &seion->coval->oid, inval->paras[APARA_OSEV_OSDB]))) {
                seion->ldata = ldata;
                memcpy(sresp->sebuf, &ldata->oid, sizeof (osv_oid_t));
                (sresp->colen)[0x00] = sizeof (osv_oid_t);
            } else {
                sctrl->status_code = INTERNAL_SERVER_ERROR;
                PDAT_NONE_TAIL(sresp)
            }
        }
    } else {
        if ((ldata = osvn_ldata_bzl(inval->paras[APARA_ACTION_KEY]))) {
            seion->ldata = ldata;
            memcpy(sresp->sebuf, &ldata->oid, sizeof (osv_oid_t));
            (sresp->colen)[0x00] = sizeof (osv_oid_t);
        } else {
            sctrl->status_code = INTERNAL_SERVER_ERROR;
            PDAT_NONE_TAIL(sresp)
        }
    }
    //
    return 0x00;
}
