
/* 
 * File:   clie_bzl.h
 * Author: Administrator
 *
 * Created on 2017.5.17, PM4:45
 */

#ifndef CLIE_BZL_H
#define CLIE_BZL_H

//
#include "osev_common/commo_header.h"
#include "clie_macro.h"
#include "requ_resp.h"
#include "stri_utili.h"

#include "clie_obje.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    typedef struct {
        // char uri_stri[URI_LENGTH];
        char osev_osdb[OSEV_LENGTH];
        osv_oid_t oid;
        int conne_sock;
    } osev_clie_t;

    int clie_inital_bzl();
    void clie_cleanup_bzl();
    //
    int clie_create_bzl(resp_data_t *clie_resp, int conne_sock, struct authe_ine *authe, osv_pstyl_t *pstyl);
    void clie_destroy_bzl(int conne_sock, osv_oid_t *oid);
    int clie_kalive_bzl(int conne_sock, osv_oid_t *oid);
    int clie_status_bzl(resp_data_t *statu_resp, int conne_sock, enum statu_type statyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_invoke_bzl(resp_data_t *invok_resp, int conne_sock, enum nspac_type nsptyp, enum invok_type invtyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_const_bzl(resp_data_t *const_resp, int conne_sock, enum const_type constyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_query_bzl(resp_data_t *query_resp, int conne_sock, enum query_type quertyp, osv_oid_t *oid, osv_pstyl_t *pstyl);

    // osev_clie_get_collection(clie, dabe_name, USER_COLLECTION_NAME);
    // osco_collection_find(collection, MONGOC_QUERY_NONE,  // 0, 0, 0, query, NULL, NULL);
    // osco_cursor_destroy(cursor);
    // osco_collection_destroy(collection);
    // void reset_conta_bzl(actionmap *cobje_hm);
#define reset_conta_bzl() \
    pthread_mutex_lock(&_cobje_mutex_); \
    action_clear(_cobje_hm_); \
    pthread_mutex_unlock(&_cobje_mutex_);

    osv_oid_t *find_conta_bzl(char *conta, osv_oid_t *oid, int conne_sock);
    void erase_conta_bzl(char *conta);

#ifdef __cplusplus
}
#endif

#endif /* CLIE_BZL_H */

