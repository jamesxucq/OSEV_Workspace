
#ifndef OSEV_CLIE_H
#define OSEV_CLIE_H

#include "excep_msg.h"
#include "clie_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    typedef struct {
        // char uri_stri[URI_LENGTH];
        char osev_osdb[OSEV_LENGTH];
        osv_oid_t oid;
        int conne_sock;
    } osev_clie;

    //
    osev_clie *osev_clie_create(char *usern, char *paswd, char *addr, int port, char *osev_osdb);
    void osev_clie_destroy(osev_clie *clie);
#define osev_clie_kalive(CLIE) clie_kalive_bzl((CLIE)->conne_sock, &(CLIE)->oid)

    // osev status
    int osev_statu_echo(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osev_statu_open(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osev_statu_close(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osev_statu_status(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osev_statu_stati(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras);

    // osev privile
    int osev_privi_list(resp_data_t *privi_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osev_privi_role(resp_data_t *privi_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osev_privi_user(resp_data_t *privi_resp, osev_clie *clie, osv_oid_t *oid, char **paras);

    // method invoke
    // para[0x00]:name space para[0x01]:echo type
    int obje_invok_list(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int obje_invok_creat(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int obje_invok_repla(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int obje_invok_drop(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int obje_invok_integri(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int obje_invok_reload(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras);

    // class colle
    // para[0x00]:name space para[0x01]:echo type
    int obje_colle_list(resp_data_t *colle_resp, osev_clie *clie, char **paras);
    int obje_colle_creat(resp_data_t *colle_resp, osev_clie *clie, char **paras);
    int obje_colle_repla(resp_data_t *colle_resp, osev_clie *clie, char **paras);
    int obje_colle_drop(resp_data_t *colle_resp, osev_clie *clie, char **paras);
    int obje_colle_integri(resp_data_t *colle_resp, osev_clie *clie, char **paras);
    int obje_colle_reload(resp_data_t *colle_resp, osev_clie *clie, char **paras);

    // construct

    int const_entry_echo(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int const_entry_creat(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int const_entry_drop(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int const_entry_updat(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int const_entry_inser(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int const_entry_find(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras);
    int const_entry_invok(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras);

    // query

    int query_conta_echo(resp_data_t *query_resp, osev_clie *clie, char **paras);
    int query_conta_creat(resp_data_t *query_resp, osev_clie *clie, char **paras);
    int query_conta_drop(resp_data_t *query_resp, osev_clie *clie, char **paras);
    int query_conta_updat(resp_data_t *query_resp, osev_clie *clie, char **paras);
    int query_conta_inser(resp_data_t *query_resp, osev_clie *clie, char **paras);
    int query_conta_find(resp_data_t *query_resp, osev_clie *clie, char **paras);
    int query_conta_invok(resp_data_t *query_resp, osev_clie *clie, char **paras);
    int query_conta_facto(resp_data_t *query_resp, osev_clie *clie, char **paras);


    //


#ifdef __cplusplus
}
#endif

#endif /* OSEV_CLIE_H */

