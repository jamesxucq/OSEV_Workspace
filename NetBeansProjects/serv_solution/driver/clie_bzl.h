
/* 
 * File:   clie_bzl.h
 * Author: James Xu
 *
 * Created on 2017.5.17, PM4:45
 */

#ifndef CLIE_BZL_H
#define CLIE_BZL_H

//

#include "clie_macro.h"
#include "requ_resp.h"
#include "requ_conne.h"
#include "dstr_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //


    // osco_init();
    // osco_cleanup();
    //
    int clie_create_bzl(resp_data_t *clie_resp, int conne_sock, struct authe_ine *authe, osv_pstyl_t *pstyl);
    void clie_destroy_bzl(int conne_sock, osv_oid_t *oid);
    int clie_kalive_bzl(int conne_sock, osv_oid_t *oid);
    int clie_status_bzl(resp_data_t *statu_resp, int conne_sock, uchar statyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_privile_bzl(resp_data_t *privi_resp, int conne_sock, uchar privtyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_invok_bzl(resp_data_t *invok_resp, int conne_sock, uchar invotyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_colle_bzl(resp_data_t *colle_resp, int conne_sock, uchar coletyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_const_bzl(resp_data_t *const_resp, int conne_sock, uchar constyp, osv_oid_t *oid, osv_pstyl_t *pstyl);
    int clie_query_bzl(resp_data_t *query_resp, int conne_sock, uchar quertyp, osv_oid_t *oid, osv_pstyl_t *pstyl);

    // osev_clie_get_collection(clie, dabe_name, USER_COLLECTION_NAME);
    // osco_collection_find(collection, MONGOC_QUERY_NONE,  // 0, 0, 0, query, NULL, NULL);
    // osco_cursor_destroy(cursor);
    // osco_collection_destroy(collection);


#ifdef __cplusplus
}
#endif

#endif /* CLIE_BZL_H */

