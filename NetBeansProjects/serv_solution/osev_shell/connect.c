
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"connect.h"
//{
// osev_init();
// osev_clie_create();
//}

//{
// collection = osev_clie_get_collection(client, dabe_name, USER_COLLECTION_NAME);
// cursor = osev_collection_find(collection, MONGOC_QUERY_NONE,
// 0, 0, 0, query, NULL, NULL);
// osev_cursor_destroy(cursor);
// osev_collection_destroy(collection);
//}

//{
// osev_clie_destroy();
// osev_cleanup();
//}


// 0:ok -1:err

osev_clie *conne_osev(svod_auth *clie_auth) {
    osev_clie *clie = osev_clie_create(clie_auth->auth.user_name, clie_auth->auth.pass_word, clie_auth->saddr.sin_addr, clie_auth->saddr.sin_port, clie_auth->osev_osdb);
    if (!clie) return NULL;
    return clie;
}

//

osev_clie *reconne_osev(osev_clie *clie, svod_auth *clie_auth) {
    osev_clie_destroy(clie);
    clie = osev_clie_create(clie_auth->auth.user_name, clie_auth->auth.pass_word, clie_auth->saddr.sin_addr, clie_auth->saddr.sin_port, clie_auth->osev_osdb);
    if (!clie) return NULL;
    return clie;
}

//

osev_clie *quit_osev(osev_clie *clie) {
    if (clie) osev_clie_destroy(clie);
    return NULL;
}

//

int osev_leve_stat(resp_data_t *osev_resp, unsigned int stat_valu, osev_clie *clie, osv_oid_t *oid, char **paras) {
    int osev_valu = 0x00;
    //
    switch (stat_valu) {
        case stat_echo:
            quote_decode(paras[0x00]);
            osev_valu = osev_statu_echo(osev_resp, clie, oid, paras);
            break;
        case stat_open:
            quote_decode(paras[0x00]);
            osev_valu = osev_statu_open(osev_resp, clie, oid, paras);
            break;
        case stat_close:
            quote_decode(paras[0x00]);
            osev_valu = osev_statu_close(osev_resp, clie, oid, paras);
            break;
        case stat_status:
            quote_decode(paras[0x00]);
            osev_valu = osev_statu_status(osev_resp, clie, oid, paras);
            break;
        case stat_stati:
            osev_valu = osev_statu_stati(osev_resp, clie, oid, paras);
            break;
        default:
            break;
    }
    //
    return osev_valu;
}

//

int osev_leve_priv(resp_data_t *osev_resp, unsigned int stat_valu, osev_clie *clie, osv_oid_t *oid, char **paras) {
    int osev_valu = 0x00;
    //
    switch (stat_valu) {
        case priv_list:
            kill_quote(paras + 0x01)
            osev_valu = osev_privi_list(osev_resp, clie, oid, paras);
            break;
        case priv_role:
            kill_quote(paras + 0x01)
            osev_valu = osev_privi_role(osev_resp, clie, oid, paras);
            break;
        case priv_user:
            kill_quote(paras + 0x01)
            osev_valu = osev_privi_user(osev_resp, clie, oid, paras);
            break;
        default:
            break;
    }
    //
    return osev_valu;
}

//

osev_clie *quit_osdb(osev_clie *clie, svod_auth *clie_auth) {
    if (clie) osev_clie_destroy(clie);
    clie = osev_clie_create(clie_auth->auth.user_name, clie_auth->auth.pass_word, clie_auth->saddr.sin_addr, clie_auth->saddr.sin_port, clie_auth->osev_osdb);
    if (!clie) return NULL;
    return clie;
}

osev_clie *_quit_osev_(osev_clie *clie) {
    if (clie) osev_clie_destroy(clie);
    return NULL;
}

//

int osdb_leve_one(resp_data_t *one_resp, unsigned int invo_valu, osev_clie *clie, osv_oid_t *oid, char **paras) {
    int onel_valu = 0x00;
    //
    switch (invo_valu) {
        case invo_list:
            quote_decode(paras[0x00]);
            onel_valu = obje_invok_list(one_resp, clie, oid, paras);
            break;
        case invo_creat:
            quote_decode(paras[0x00]);
            onel_valu = obje_invok_creat(one_resp, clie, oid, paras);
            break;
        case invo_repla:
            quote_decode(paras[0x00]);
            onel_valu = obje_invok_repla(one_resp, clie, oid, paras);
            break;
        case invo_drop:
            quote_decode(paras[0x00]);
            onel_valu = obje_invok_drop(one_resp, clie, oid, paras);
            break;
        case invo_integri:
            quote_decode(paras[0x00]);
            onel_valu = obje_invok_integri(one_resp, clie, oid, paras);
            break;
        case invo_reload:
            quote_decode(paras[0x00]);
            onel_valu = obje_invok_reload(one_resp, clie, oid, paras);
            break;
        default:
            break;
    }
    //
    return onel_valu;
}

int osdb_leve_twop(resp_data_t *twop_resp, unsigned int coll_valu, osev_clie *clie, char **paras) {
    int twopl = 0x00;
    //
    switch (coll_valu) {
        case coll_list:
            quote_decode(paras[0x00]);
            twopl = obje_colle_list(twop_resp, clie, paras);
            break;
        case coll_creat:
            quote_decode(paras[0x00]);
            twopl = obje_colle_creat(twop_resp, clie, paras);
            break;
        case coll_repla:
            quote_decode(paras[0x00]);
            twopl = obje_colle_repla(twop_resp, clie, paras);
            break;
        case coll_drop:
            quote_decode(paras[0x00]);
            twopl = obje_colle_drop(twop_resp, clie, paras);
            break;
        case coll_integri:
            quote_decode(paras[0x00]);
            twopl = obje_colle_integri(twop_resp, clie, paras);
            break;
        case coll_reload:
            quote_decode(paras[0x00]);
            twopl = obje_colle_reload(twop_resp, clie, paras);
            break;
        default:
            break;
    }
    //
    return twopl;
}

//

int osdb_leve_thre(resp_data_t *thre_resp, unsigned int quer_valu, osev_clie *clie, osv_oid_t *oid, char **paras) {
    int threl = 0x00;
    //
    switch (quer_valu) {
        case cons_echo:
            quote_decode(paras[0x00]);
            threl = const_entry_echo(thre_resp, clie, oid, paras);
            break;
        case cons_creat:
            threl = const_entry_creat(thre_resp, clie, oid, paras);
            break;
        case cons_drop:
            quote_decode(paras[0x00]);
            threl = const_entry_drop(thre_resp, clie, oid, paras);
            break;
        case cons_updat:
            threl = const_entry_updat(thre_resp, clie, oid, paras);
            break;
        case cons_inser:
            threl = const_entry_inser(thre_resp, clie, oid, paras);
            break;
        case cons_find:
            quote_decode(paras[0x00]);
            threl = const_entry_find(thre_resp, clie, oid, paras);
            break;
        case cons_invok:
            kill_quote(paras)
            threl = const_entry_invok(thre_resp, clie, oid, paras);
            break;
        default:
            break;
    }
    //
    return threl;
}

//

int osdb_leve_foup(resp_data_t *foup_resp, unsigned int quer_valu, osev_clie *clie, char **paras) {
    int foupl = 0x00;
    //
    switch (quer_valu) {
        case quer_echo:
            quote_decode(paras[0x00]);
            foupl = query_conta_echo(foup_resp, clie, paras);
            break;
        case quer_creat:
            quote_decode(paras[0x00]);
            quote_decode(paras[0x02]);
            foupl = query_conta_creat(foup_resp, clie, paras);
            break;
        case quer_drop:
            quote_decode(paras[0x00]);
            foupl = query_conta_drop(foup_resp, clie, paras);
            break;
        case quer_find:
            foupl = query_conta_find(foup_resp, clie, paras);
            break;
        case quer_invok:
            kill_quote(paras)
            foupl = query_conta_invok(foup_resp, clie, paras);
            break;
        case quer_facto:
            quote_decode(paras[0x00]);
            foupl = query_conta_facto(foup_resp, clie, paras);
            break;
        default:
            break;
    }
    //
    return foupl;
}


