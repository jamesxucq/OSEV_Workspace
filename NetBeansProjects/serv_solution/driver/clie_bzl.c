
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "commo_header.h"
#include "osco_socks.h"
#include "hand_method.h"
#include "osev_clie.h"

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

int clie_status_bzl(resp_data_t *statu_resp, int conne_sock, uchar statyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    statu_requ_t *rstatu = (statu_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rstatu, OSVP_STATUS, sizeof (statu_ine) + pstyl->colen)
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

int clie_privile_bzl(resp_data_t *privi_resp, int conne_sock, uchar privtyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    privi_requ_t *rstatu = (privi_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rstatu, OSVP_PRIVI, sizeof (statu_ine) + pstyl->colen)
    rstatu->privi.privtyp = privtyp;
    memcpy(&rstatu->privi.oid, oid, sizeof (osv_oid_t));
    memcpy(rstatu->requ_data, pstyl->pstyl_str, pstyl->colen);
    CAT_REQU_STR(req_dat, rstatu)
            //
    if (OK != hand_respon(privi_resp, conne_sock, &req_dat)) {
        printf("    osev status error!\n");
        return -1;
    }
    //
    return 0x00;
}

int clie_invok_bzl(resp_data_t *invok_resp, int conne_sock, uchar invotyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    invok_requ_t *rinvok = (invok_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rinvok, OSVP_INVOKEx, sizeof (invok_ine) + pstyl->colen)
    rinvok->invok.invotyp = invotyp;
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

int clie_colle_bzl(resp_data_t *colle_resp, int conne_sock, uchar coletyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    colle_requ_t *rcolle = (colle_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rcolle, OSVP_COLLE, sizeof (colle_ine) + pstyl->colen)
    rcolle->invok.coletyp = coletyp;
    memcpy(&rcolle->invok.oid, oid, sizeof (osv_oid_t));
    memcpy(rcolle->requ_data, pstyl->pstyl_str, pstyl->colen);
    CAT_REQU_STR(req_dat, rcolle)
            //
    if (OK != hand_respon(colle_resp, conne_sock, &req_dat)) {
        printf("    osev colle error!\n");
        return -1;
    }
    //
    return 0x00;
}

int clie_const_bzl(resp_data_t *const_resp, int conne_sock, uchar constyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    const_requ_t *rconst = (const_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rconst, OSVP_CONST, sizeof (const_ine) + pstyl->colen)
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

int clie_query_bzl(resp_data_t *query_resp, int conne_sock, uchar quertyp, osv_oid_t *oid, osv_pstyl_t *pstyl) {
    requ_data_t req_dat;
    //
    query_requ_t *rquery = (query_requ_t *) req_dat.req_data;
    req_dat.requ_type = 0x00;
    CAT_METHO_PTR(rquery, OSVP_QUERY, sizeof (query_ine) + pstyl->colen)
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
