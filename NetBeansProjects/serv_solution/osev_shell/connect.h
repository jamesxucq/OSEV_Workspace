
#ifndef CONNECT_H
#define CONNECT_H

#include "commo_header.h"
#include"osev_clie.h"
#include "parse_command.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0:ok -1:err
    osev_clie *conne_osev(svod_auth *clie_auth);
    osev_clie *reconne_osev(osev_clie *clie, svod_auth *clie_auth);
    osev_clie *quit_osev(osev_clie *clie);

    // resp_data *statu_resp
    int osev_leve_stat(resp_data_t *osev_resp, unsigned int stat_valu, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osev_leve_priv(resp_data_t *osev_resp, unsigned int stat_valu, osev_clie *clie, osv_oid_t *oid, char **paras);
    //
    osev_clie *quit_osdb(osev_clie *clie, svod_auth *clie_auth);
    osev_clie *_quit_osev_(osev_clie *clie);
    int osdb_leve_one(resp_data_t *one_resp, unsigned int invo_valu, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osdb_leve_twop(resp_data_t *twop_resp, unsigned int coll_valu, osev_clie *clie, char **paras);
    int osdb_leve_thre(resp_data_t *thre_resp, unsigned int quer_valu, osev_clie *clie, osv_oid_t *oid, char **paras);
    int osdb_leve_foup(resp_data_t *foup_resp, unsigned int quer_valu, osev_clie *clie, char **paras);


#ifdef __cplusplus
}
#endif

#endif /* CONNECT_H */

