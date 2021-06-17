
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>

#include "osev_common/commo_header.h"
#include "osco_socks.h"
#include "hand_method.h"
// #include "osev_clie.h"

#include "clie_bzl.h"
//

int clie_create_bzl(resp_data_t *clie_resp, int conne_sock, struct authe_ine *authe, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    auth_requ_t *rauthe = (auth_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rauthe, OSVP_AUTHEN, sizeof (struct authe_ine) +pstyl->colen)
    memcpy(&rauthe->authe, authe, sizeof (struct authe_ine));
    memcpy(rauthe->requ_data, pstyl->pstyl_str, pstyl->colen);
    CAT_REQU_STR(req_dat, rauthe)
            //
    if (OK != hand_respon(clie_resp, conne_sock, &req_dat)) {
        printf("    osev osauth error!\n");
        return -1;
    }
    //
    return 0x00;
}

//

void clie_destroy_bzl(int conne_sock, osv_oid_t *oid) {
    requ_data_t req_dat;
    //
    done_requ_t *rdone = (done_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rdone, OSVP_DONE, sizeof (osv_oid_t))
    memcpy(&rdone->oid, oid, sizeof (osv_oid_t));
    CAT_REQU_STR(req_dat, rdone)
    if (OK != hand_reques(conne_sock, &req_dat))
        printf("    osev clie destroy error!\n");
    //
    printf("    osev clie destroy ok!\n");
}

int clie_kalive_bzl(int conne_sock, osv_oid_t *oid) {
    requ_data_t req_dat;
    kalive_requ_t *rkalive = (kalive_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rkalive, OSVP_KALIVE, sizeof (osv_oid_t))
    memcpy(&rkalive->oid, oid, sizeof (osv_oid_t));
    CAT_REQU_STR(req_dat, rkalive)
    if (OK != hand_reques(conne_sock, &req_dat))
        return -1;
    //
    return 0x00;
}

int clie_status_bzl(resp_data_t *statu_resp, int conne_sock, enum statu_type statyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    statu_requ_t *rstatu = (statu_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rstatu, OSVP_STATUS, sizeof (struct statu_ine) +pstyl->colen)
    rstatu->statu.statyp = statyp;
    memcpy(&rstatu->statu.oid, oid, sizeof (osv_oid_t));
    memcpy(rstatu->requ_data, pstyl->pstyl_str, pstyl->colen);
    CAT_REQU_STR(req_dat, rstatu)
            //
    if (OK != hand_respon(statu_resp, conne_sock, &req_dat)) {
        printf("    osev status error!\n");
        return -1;
    }
    //
    return 0x00;
}

int clie_invoke_bzl(resp_data_t *invok_resp, int conne_sock, enum nspac_type nsptyp, enum invok_type invtyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    invok_requ_t *rinvok = (invok_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rinvok, OSVP_INVOKE, sizeof (struct invok_ine) +pstyl->colen)
    rinvok->invok.nsptyp = nsptyp;
    rinvok->invok.invtyp = invtyp;
    memcpy(&rinvok->invok.oid, oid, sizeof (osv_oid_t));
    memcpy(rinvok->requ_data, pstyl->pstyl_str, pstyl->colen);
    CAT_REQU_STR(req_dat, rinvok)
            //
    if (OK != hand_respon(invok_resp, conne_sock, &req_dat)) {
        printf("    osev invok error!\n");
        return -1;
    }
    //
    return 0x00;
}

int clie_const_bzl(resp_data_t *const_resp, int conne_sock, enum const_type constyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    const_requ_t *rconst = (const_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rconst, OSVP_CONST, sizeof (struct const_ine) +pstyl->colen)
    rconst->constr.constyp = constyp;
    memcpy(&rconst->constr.oid, oid, sizeof (osv_oid_t));
    memcpy(rconst->requ_data, pstyl->pstyl_str, pstyl->colen);
    CAT_REQU_STR(req_dat, rconst)
            //
    if (OK != hand_respon(const_resp, conne_sock, &req_dat)) {
        printf("    osev const error!\n");
        return -1;
    }
    //
    return 0x00;
}

int clie_query_bzl(resp_data_t *query_resp, int conne_sock, enum query_type quertyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    query_requ_t *rquery = (query_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rquery, OSVP_QUERY, sizeof (struct query_ine) +pstyl->colen)
    rquery->query.quertyp = quertyp;
    memcpy(&rquery->query.oid, oid, sizeof (osv_oid_t));
    memcpy(rquery->requ_data, pstyl->pstyl_str, pstyl->colen);
    CAT_REQU_STR(req_dat, rquery)
            //
    if (OK != hand_respon(query_resp, conne_sock, &req_dat)) {
        printf("    osev query error!\n");
        return -1;
    }
    //
    return 0x00;
}

//

int clie_inital_bzl() {
    pthread_mutex_init(&_cobje_mutex_, NULL);
    //
    pthread_mutex_lock(&_cobje_mutex_);
    _cobje_hm_ = create_action(cona_free, CONTA_BACKET_SIZE);
    pthread_mutex_unlock(&_cobje_mutex_);
    if(!_cobje_hm_) return -1;
            //
    return 0x00; //succ
}

void clie_cleanup_bzl() {
    pthread_mutex_lock(&_cobje_mutex_);
    if (_cobje_hm_) {
        action_dele(_cobje_hm_);
        _cobje_hm_ = NULL;
    }
    pthread_mutex_unlock(&_cobje_mutex_);
    //
    pthread_mutex_destroy(&_cobje_mutex_);
}

//

static int osdb_query_echo(resp_data_t *query_resp, osev_clie_t *clie, char **paras) {
    printf("osdb_query_echo\n");
    osv_pstyl_t pstyl;
    if (-1 == line_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_ECHO, &clie->oid, &pstyl)) {
        printf("    query echo error!\n");
        return -1;
    }
    //
    return 0x00;
}
//

struct obje_valu {
    osv_oid_t obje_id;
    char obje_ident[OBJE_LENGTH];
};

osv_oid_t *find_conta_bzl(char *conta, osv_oid_t *oid, int conne_sock) {
    // printf("find_conta_bzl, start. conta:%s\n", conta);
    pthread_mutex_lock(&_cobje_mutex_);
    osv_oid_t *obje_id = (osv_oid_t *) action_value(conta, _cobje_hm_);
    pthread_mutex_unlock(&_cobje_mutex_);
    if (obje_id) return obje_id;
    //
    char epara[PARAM_LENGTH];
    char *paras[0x02] = {epara, NULL};
    sprintf(epara, "%s", conta);
    osev_clie_t clie;
    clie.conne_sock = conne_sock;
    memcpy(&clie.oid, oid, sizeof (osv_oid_t));
    //
    resp_data_t cona_resp;
    if (!osdb_query_echo(&cona_resp, &clie, paras)) {
        struct obje_valu *ovalu = (struct obje_valu*) malloc(sizeof (struct obje_valu));
        memcpy(&ovalu->obje_id, cona_resp.res_data, sizeof (osv_oid_t));
        strcpy(ovalu->obje_ident, conta);
        //
        pthread_mutex_lock(&_cobje_mutex_);
        action_insert(ovalu->obje_ident, ovalu, _cobje_hm_);
        pthread_mutex_unlock(&_cobje_mutex_);
        //
        obje_id = &ovalu->obje_id;
    }
    //
    char oid_stri[OID_LINE_LEN];
    printf("find_conta_bzl, echo %s oid:%s\n", conta, oidstr(oid_stri, obje_id));
    return obje_id;
}

void erase_conta_bzl(char *conta) {
    char obje_ident[OBJE_LENGTH];
    //
    strcpy(obje_ident, conta);
    quote_decode(obje_ident);
    printf("erase_conta_bzl, conta %s obje_ident:%s\n", conta, obje_ident);
    pthread_mutex_lock(&_cobje_mutex_);
    action_remove(obje_ident, _cobje_hm_);
    pthread_mutex_unlock(&_cobje_mutex_);
}

//