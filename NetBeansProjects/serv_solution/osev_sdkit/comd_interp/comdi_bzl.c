#include "commo_header.h"

//
#include "istri_utili.h"
#include "rstat_bzl.h"
#include "conoda.h"
#include "authen_bzl.h"

#include "comdi_bzl.h"

//

/*
int cmdibzl_create(char *data_directory) {
    strcpy(_cmdi_data_directory_, data_directory);
    return 0x00; //succ
}
 * 
int cmdibzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

//

int inte_authen_bzl(inte_value *inval, struct authe_ine *auth, char *requ_data) {
    char *last_str = inval->data_line;
    lscpy_o(inval->paras[APARA_USER_NAME], auth->user_name, last_str);
    lszcpy_o(inval->paras[APARA_REQU_VALID], auth->req_valid, PASWD_LENGTH, last_str)
    lszcpy_o(inval->paras[APARA_REQU_SALT], auth->salt, SALT_LENGTH, last_str)
    //
    last_str = parse_authen(last_str, inval->paras + APARA_PARAM_POS, requ_data);
    if (!last_str) return -1;
    //
    if (strcmp(OSEV_DEFAULT_VALUE, inval->paras[APARA_OSEV_OSDB])) inval->sentry = AUTH_OSDB;
    else inval->sentry = AUTH_OSEV;
    printf("coin_auth.auth_type:%d\n", inval->sentry);
    char action_key[ACTION_KEY_LENGTH];
    creat_action_key(action_key, auth->user_name, inval->paras[APARA_OSEV_OSDB]);
    lscpy_o(inval->paras[APARA_ACTION_KEY], action_key, last_str);
    //
    return 0x00;
}

//

int inte_kalive_bzl(inte_value *inval) {
    return 0x00;
}

//

int inte_status_bzl(inte_value *inval, statu_ine *statu, char *requ_data) {
    memcpy(&inval->oid, &statu->oid, sizeof (osv_oid_t));
    inval->sentry = OSEV_OSDB_OID(statu->oid);
    inval->svalue = statu->statyp;
    // printf("inval->sentry:%u statu->statyp:%u\n", inval->sentry, statu->statyp);
    parse_status_tab[inval->sentry][statu->statyp](inval->data_line, inval->paras, requ_data);
    //    if (valid_status()) return -1;
    return 0x00;
}

//

int inte_privile_bzl(inte_value *inval, privi_ine *privi, char *requ_data) {
    memcpy(&inval->oid, &privi->oid, sizeof (osv_oid_t));
    inval->sentry = OSEV_OSDB_OID(privi->oid);
    inval->svalue = privi->privtyp;
    //
    parse_privile_tab[inval->sentry][privi->privtyp](inval->data_line, inval->paras, requ_data);
    //    if (valid_privile()) return -1;
    return 0x00;
}

//

int inte_invoke_bzl(inte_value *inval, invok_ine *invok, char *requ_data) {
    memcpy(&inval->oid, &invok->oid, sizeof (osv_oid_t));
    inval->sentry = invok->invotyp;
     // printf("inval->sentry:%d invok->invotyp:%d\n", inval->sentry, invok->invotyp);
    parse_invok_tab[inval->sentry](inval->data_line, inval->paras, requ_data);
    //    if (valid_invoke()) return -1;
    return 0x00;
}

int inte_colle_bzl(inte_value *inval, colle_ine *colle, char *requ_data) {
    memcpy(&inval->oid, &colle->oid, sizeof (osv_oid_t));
    inval->sentry = colle->coletyp;
     // printf("inval->sentry:%d invok->invotyp:%d\n", inval->sentry, invok->invotyp);
    parse_colle_tab[inval->sentry](inval->data_line, inval->paras, requ_data);
    //    if (valid_invoke()) return -1;
    return 0x00;
}

//

int inte_const_bzl(inte_value *inval, const_ine *constr, char *requ_data) {
    memcpy(&inval->oid, &constr->oid, sizeof (osv_oid_t));
    char oid_stri[OID_LINE_LEN];
    printf("inval->oid:|%s|\n", oidstr(oid_stri, &inval->oid));
    // printf("ldata->oid:|%s|\n", oidstr(oid_stri, &ldata->oid));
    inval->sentry = constr->constyp;
    // printf("inval->sentry:%d\n", inval->sentry);
    parse_const_tab[inval->sentry](inval->data_line, inval->paras, requ_data);
    //    if (valid_const()) return -1;
    return 0x00;
}

int inte_query_bzl(inte_value *inval,query_ine *query, char *requ_data) {
    memcpy(&inval->oid, &query->oid, sizeof (osv_oid_t));
    char oid_stri[OID_LINE_LEN];
    printf("inval->oid:|%s|\n", oidstr(oid_stri, &inval->oid));
    // printf("ldata->oid:|%s|\n", oidstr(oid_stri, &ldata->oid));
    inval->sentry = query->quertyp;
    // printf("inval->sentry:%d\n", inval->sentry);
    parse_query_tab[inval->sentry](inval->data_line, inval->paras, requ_data);
    //    if (valid_query()) return -1;
    return 0x00;
}

//

int inte_done_bzl(inte_value *inval) {
    return 0x00;
}