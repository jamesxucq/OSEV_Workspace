/* authen_bzl.c
 * Created on: 2010-3-10
 * Author: Divad
 */

#include "commo_header.h"
#include "rstat_bzl.h"
#include "privile_bzl.h"

#include "priv_utili.h"
#include "conve_autho.h"
#include "privi_ctrl.h"
#include "privi_cache.h"
#include "authen_bzl.h"
#include "privi_obje.h"
#include "osev_struct.h"

//

//

int authbzl_create(int max_connecting) {
    _hashmap_size_ = max_connecting;
    _hashmap_size_ <<= 2;
    _ldata_hm_ = create_action(free_ldata, _hashmap_size_);
    if (!_ldata_hm_) return ERR_FAULT;
    //
    _ouser_hm_ = create_cache(_hashmap_size_);
    if (!_ouser_hm_) return ERR_FAULT;
    _cuser_hm_ = create_cache(_hashmap_size_);
    if (!_cuser_hm_) return ERR_FAULT;
    //
#ifndef NOAUTH
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        _LOG_DEBUG("check admin odb excep!");
        return ERR_EXCEP;
    }
    if (check_priv_data(&coval->conda, _priv_data_)) {
        _LOG_DEBUG("check authen data excep!");
        return ERR_EXCEP;
    }
    if (load_privi_data(_ouser_hm_, _cuser_hm_, &_priv_list_, coval)) return ERR_FAULT;
#endif
    //
    printf("check auth cache ok!\n");
    return ERR_SUCCESS; //succ
}

int authbzl_destroy() {
    dele_privi_data(_ouser_hm_, _cuser_hm_, &_priv_list_);
    if (_cuser_hm_) {
        cache_dele(_cuser_hm_);
        _cuser_hm_ = NULL;
    }
    if (_ouser_hm_) {
        cache_dele(_ouser_hm_);
        _ouser_hm_ = NULL;
    }
    if (_ldata_hm_) {
        action_dele(_ldata_hm_);
        _ldata_hm_ = NULL;
    }
    //
    return ERR_SUCCESS; //succ
}

//

list_data *osev_ldata_bzl(char *action_key, char *user_name) {
    user_privi *user_poin;
    list_data *ldata;
    //
    if ((ldata = (list_data *) action_value(action_key, _ldata_hm_))) ldata->_refer_inde_++;
    else {
        if (!(user_poin = (user_privi *) cache_value(user_name, _ouser_hm_))) return NULL;
        if (!(ldata = new_ldata())) return NULL;
        //
        ldata->use_privi = user_poin;
        build_auth_valid(ldata->auth_valid, ldata->use_privi);
        _LOG_DEBUG("enable osev authen.");
        strcpy(ldata->osev_osdb, OSEV_DEFAULT_VALUE);
        creat_objeid_osev(&ldata->oid);
        strcpy(ldata->_action_key_, action_key);
        ldata->_refer_inde_ = 0x01;
        action_insert(ldata->_action_key_, ldata, _ldata_hm_);
    }
    // _LOG_DEBUG("increase auth cache refer inde:%d", ldata->refer_inde);
    return ldata;
}

list_data *osvn_ldata_bzl(char *action_key) {
    list_data *ldata;
    //
    if ((ldata = (list_data *) action_value(action_key, _ldata_hm_))) ldata->_refer_inde_++;
    else {
        _LOG_DEBUG("disable osev authen.");
        if (!(ldata = new_ldata())) return NULL;
        //
        strcpy(ldata->osev_osdb, OSEV_DEFAULT_VALUE);
        creat_objeid_osev(&ldata->oid);
        strcpy(ldata->_action_key_, action_key);
        ldata->_refer_inde_ = 0x01;
        action_insert(ldata->_action_key_, ldata, _ldata_hm_);
    }
    // _LOG_DEBUG("increase auth cache refer inde:%d", ldata->refer_inde);
    return ldata;
}

//

list_data *osdb_ldata_bzl(char *action_key, char *user_name, osv_oid_t *osdb_oid, char *osdb) {
    user_privi *user_poin;
    list_data *ldata;
    //
    if ((ldata = (list_data *) action_value(action_key, _ldata_hm_))) ldata->_refer_inde_++;
    else {
        if (!(user_poin = (user_privi *) cache_value(user_name, _cuser_hm_))) return NULL;
        if (!(ldata = new_ldata())) return NULL;
        //
        ldata->use_privi = user_poin;
        build_auth_valid(ldata->auth_valid, ldata->use_privi);
        _LOG_DEBUG("enable osdb authen.");
        strcpy(ldata->osev_osdb, osdb);
        memcpy(&ldata->oid, osdb_oid, sizeof (osv_oid_t));
        strcpy(ldata->_action_key_, action_key);
        ldata->_refer_inde_ = 0x01;
        action_insert(ldata->_action_key_, ldata, _ldata_hm_);
    }
    // _LOG_DEBUG("increase auth cache refer inde:%d", ldata->refer_inde);
    return ldata;
}

list_data *odbn_ldata_bzl(char *action_key, osv_oid_t *osdb_oid, char *osdb) {
    list_data *ldata;
    //
    if ((ldata = (list_data *) action_value(action_key, _ldata_hm_))) ldata->_refer_inde_++;
    else {
        _LOG_DEBUG("disable osdb authen.");
        if (!(ldata = new_ldata())) return NULL;
        //
        strcpy(ldata->osev_osdb, osdb);
        memcpy(&ldata->oid, osdb_oid, sizeof (osv_oid_t));
        strcpy(ldata->_action_key_, action_key);
        ldata->_refer_inde_ = 0x01;
        action_insert(ldata->_action_key_, ldata, _ldata_hm_);
    }
    // _LOG_DEBUG("increase auth cache refer inde:%d", ldata->refer_inde);
    return ldata;
}

//

void auth_epoll_exception(char *action_key) {
    list_data *ldata;
    if ((ldata = (list_data *) action_value(action_key, _ldata_hm_))) {
        ldata->_refer_inde_--;
        if (!ldata->_refer_inde_) {
            _LOG_INFO("exception delete ldata refere inde:%d", ldata->_refer_inde_);
            action_remove(action_key, _ldata_hm_);
        }
    }
    // _LOG_INFO("decrease auth cache refere inde:%d", ldata->refer_inde); // disable by james 20120410
}

int erase_auth_cache_end(char *action_key) {
    list_data *ldata;
    if ((ldata = (list_data *) action_value(action_key, _ldata_hm_))) {
        ldata->_refer_inde_--;
        if (!ldata->_refer_inde_) {
            _LOG_INFO("done delete ldata refere inde:%d", ldata->_refer_inde_);
            action_remove(action_key, _ldata_hm_);
        }
    }
    // _LOG_INFO("decrease auth cache refere refer inde:%d", ldata->refer_inde); // disable by james 20120410
    return ERR_SUCCESS;
}

//

int reloa_privi_bzl(prod_data *sresp) {
    // destroy 
    dele_privi_data(_ouser_hm_, _cuser_hm_, &_priv_list_);
    // open        
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_NONE_TAIL(sresp)
        return ERR_FAULT;
    }
    if (check_priv_data(&coval->conda, _priv_data_)) {
        PDAT_NONE_TAIL(sresp)
        return ERR_FAULT;
    }
    if (load_privi_data(_ouser_hm_, _cuser_hm_, &_priv_list_, coval)) return ERR_FAULT;
    //
    return ERR_SUCCESS;
}

//

int olist_role_bzl(prod_data *sresp, char *role_name) {
    _LOG_DEBUG("olist_role_bzl");
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    //
    if (role_name) {
        _LOG_DEBUG("role_name:|%s|", role_name);
        role_privi *role_poin = find_osev_role(_priv_list_.role_list, role_name);
        if (!role_poin) {
            PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
            return ERR_FAULT;
        }
    //
    char oid_stri[OID_LINE_LEN];
    printf("|%s|\n", oidstr(oid_stri, &role_poin->oid));
    //
        if (oconv_role_name(sresp, coval, role_poin)) {
            PDAT_EXCEP_TAIL(sresp, LOAD_ROLE_EXCE)
            return ERR_FAULT;
        }
    } else {
        if (oconv_role_all(sresp, coval, _priv_list_.role_list)) {
            PDAT_EXCEP_TAIL(sresp, LOAD_ROLE_EXCE)
            return ERR_FAULT;
        }
    }
    //
    return ERR_SUCCESS;
}

int olist_user_bzl(prod_data *sresp, char *ouse_name) {
    _LOG_DEBUG("olist_user_bzl");
    if (ouse_name) {
        _LOG_DEBUG("ouse_name:|%s|", ouse_name);
        user_privi *user_poin = find_user_cache(_ouser_hm_, ouse_name);
        if (!user_poin) {
            PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
            return ERR_FAULT;
        }
        conve_user_name(sresp, user_poin);
    } else conve_user_all(sresp, _priv_list_.ouse_list);
    //
    return ERR_SUCCESS;
}

//

int dlist_role_bzl(prod_data *sresp, char *role_name) {
    _LOG_DEBUG("dlist_role_bzl");
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    //
    if (role_name) {
        _LOG_DEBUG("role_name:|%s|", role_name);
        role_privi *role_poin = find_osdb_role(_priv_list_.role_list, role_name);
        if (!role_poin) {
            PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
            return ERR_FAULT;
        }
        if (dconv_role_name(sresp, coval, role_poin)) {
            PDAT_EXCEP_TAIL(sresp, LOAD_ROLE_EXCE)
            return ERR_FAULT;
        }
    } else {
        if (dconv_role_all(sresp, coval, _priv_list_.role_list)) {
            PDAT_EXCEP_TAIL(sresp, LOAD_ROLE_EXCE)
            return ERR_FAULT;
        }
    }
    //
    return ERR_SUCCESS;
}

int dlist_user_bzl(prod_data *sresp, char *cuse_name) {
    _LOG_DEBUG("dlist_user_bzl");
    if (cuse_name) {
        _LOG_DEBUG("cuse_name:|%s|", cuse_name);
        user_privi *user_poin = find_user_cache(_cuser_hm_, cuse_name);
        if (!user_poin) {
            PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
            return ERR_FAULT;
        }
        conve_user_name(sresp, user_poin);
    } else conve_user_all(sresp, _priv_list_.cuse_list);
    //
    return ERR_SUCCESS;
}

//

int oadd_role_bzl(prod_data *sresp, char *role_name) {
    printf("oadd_role_bzl, role_name: %s\n", role_name);
    if (!role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    if (find_osev_role(_priv_list_.role_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    if (!oadd_role_data(coval, &_priv_list_.role_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, ADDI_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int odel_role_bzl(prod_data *sresp, char *role_name) {
    printf("odel_role_bzl\n");
    if (!role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    if (osev_role_used(_priv_list_.ouse_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, ROLE_USED_EXCE)
        return ERR_FAULT;
    }
    if (odel_role_data(coval, &_priv_list_.role_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, DELE_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

// destination

int ogran_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask) {
    printf("ogran_priv_bzl\n");
    if (!role_name || !dist_name || !priv_mask) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    uint32 leve_mask = INVA_PRIV;
    dist_privi priv_dist;
    if (opriv_dist_leoid(&priv_dist.oid, &leve_mask, dist_name, priv_mask)) {
        PDAT_EXCEP_TAIL(sresp, DIST_OID_EXCE)
        return ERR_FAULT;
    }
    priv_dist.privile_mask = priv_mask;
    //
    role_privi *role_poin = find_osev_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    if (osev_priv_bzl(AUTH_ROLES_CONT, &role_poin->oid, &priv_dist)) {
        PDAT_EXCEP_TAIL(sresp, ROLE_PRIV_EXIS)
        return ERR_FAULT;
    }
    if (ogran_priv_data(coval, role_poin, &priv_dist, leve_mask)) {
        PDAT_EXCEP_TAIL(sresp, GRAN_PRIV_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int orevk_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask) {
    printf("orevk_priv_bzl\n");
    if (!role_name || !dist_name || !priv_mask) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    uint32 leve_mask = INVA_PRIV;
    dist_privi priv_dist;
    if (opriv_dist_leoid(&priv_dist.oid, &leve_mask, dist_name, priv_mask)) {
        PDAT_EXCEP_TAIL(sresp, DIST_OID_EXCE)
        return ERR_FAULT;
    }
    priv_dist.privile_mask = priv_mask;
    //
    role_privi *role_poin = find_osev_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    if (orevk_priv_data(coval, role_poin, &priv_dist, leve_mask)) {
        PDAT_EXCEP_TAIL(sresp, REVK_PRIV_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

//

int dadd_role_bzl(prod_data *sresp, char *role_name) {
    printf("dadd_role_bzl\n");
    if (!role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    if (find_osdb_role(_priv_list_.role_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    if (!dadd_role_data(coval, &_priv_list_.role_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, ADDI_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int ddel_role_bzl(prod_data *sresp, char *role_name) {
    printf("ddel_role_bzl\n");
    if (!role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    if (osdb_role_used(_priv_list_.cuse_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, ROLE_USED_EXCE)
        return ERR_FAULT;
    }
    if (ddel_role_data(coval, &_priv_list_.role_list, role_name)) {
        PDAT_EXCEP_TAIL(sresp, DELE_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int dgran_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask) {
    printf("dgran_priv_bzl\n");
    if (!role_name || !dist_name || !priv_mask) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    uint32 leve_mask = INVA_PRIV;
    dist_privi priv_dist;
    if (dpriv_dist_leoid(&priv_dist.oid, &leve_mask, dist_name, priv_mask)) {
        PDAT_EXCEP_TAIL(sresp, DIST_OID_EXCE)
        return ERR_FAULT;
    }
    priv_dist.privile_mask = priv_mask;
    //
    role_privi *role_poin = find_osdb_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    if (osdb_priv_bzl(AUTH_ROLES_CONT, &role_poin->oid, &priv_dist)) {
        PDAT_EXCEP_TAIL(sresp, ROLE_PRIV_EXIS)
        return ERR_FAULT;
    }
    if (dgran_priv_data(coval, role_poin, &priv_dist, leve_mask)) {
        PDAT_EXCEP_TAIL(sresp, GRAN_PRIV_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int drevk_priv_bzl(prod_data *sresp, char *role_name, char *dist_name, uint32 priv_mask) {
    printf("drevk_priv_bzl\n");
    if (!role_name || !dist_name || !priv_mask) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check roles data error!");
    uint32 leve_mask = INVA_PRIV;
    dist_privi priv_dist;
    if (dpriv_dist_leoid(&priv_dist.oid, &leve_mask, dist_name, priv_mask)) {
        PDAT_EXCEP_TAIL(sresp, DIST_OID_EXCE)
        return ERR_FAULT;
    }
    priv_dist.privile_mask = priv_mask;
    //
    role_privi *role_poin = find_osdb_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    if (drevk_priv_data(coval, role_poin, &priv_dist, leve_mask)) {
        PDAT_EXCEP_TAIL(sresp, REVK_PRIV_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

//

int oadd_user_bzl(prod_data *sresp, char *ouse_name, char *salt_paswd) {
    printf("oadd_user_bzl\n");
    if (!ouse_name || !salt_paswd) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check ouser data error!");
    if (find_user_cache(_ouser_hm_, ouse_name)) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    user_privi *user_poin = addi_ouser_data(coval, &_priv_list_.ouse_list, ouse_name, salt_paswd);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, ADDI_USER_EXCE)
        return ERR_FAULT;
    }
    addi_user_cache(_ouser_hm_, user_poin);
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int odel_user_bzl(prod_data *sresp, char *ouse_name) {
    printf("odel_user_bzl\n");
    if (!ouse_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check ouser data error!");
    user_privi *user_poin = find_user_cache(_ouser_hm_, ouse_name);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    dele_user_cache(_ouser_hm_, user_poin);
    if (dele_ouser_data(coval, &_priv_list_.ouse_list, user_poin)) {
        PDAT_EXCEP_TAIL(sresp, DELE_USER_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int ogran_role_bzl(prod_data *sresp, char *ouse_name, char *role_name) {
    printf("ogran_role_bzl\n");
    if (!ouse_name || !role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check ouser data error!");
    role_privi *role_poin = find_osev_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    user_privi *user_poin = find_user_privi(_priv_list_.ouse_list, ouse_name);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    //
    if (osev_role_bzl(user_poin, role_poin)) {
        PDAT_EXCEP_TAIL(sresp, USER_ROLE_EXIS)
        return ERR_FAULT;
    }
    if (ogran_role_data(coval, user_poin, role_poin)) {
        PDAT_EXCEP_TAIL(sresp, GRAN_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int orevk_role_bzl(prod_data *sresp, char *ouse_name, char *role_name) {
    printf("orevk_role_bzl\n");
    if (!ouse_name || !role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check ouser data error!");
    role_privi *role_poin = find_osev_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    user_privi *user_poin = find_user_privi(_priv_list_.ouse_list, ouse_name);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    if (orevk_role_data(coval, user_poin, role_poin)) {
        PDAT_EXCEP_TAIL(sresp, REVK_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

//

int dadd_user_bzl(prod_data *sresp, char *cuse_name, char *salt_paswd) {
    printf("dadd_user_bzl\n");
    if (!cuse_name || !salt_paswd) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check users data error!");
    if (find_user_cache(_cuser_hm_, cuse_name)) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    user_privi *user_poin = addi_cuser_data(coval, &_priv_list_.cuse_list, cuse_name, salt_paswd);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, ADDI_USER_EXCE)
        return ERR_FAULT;
    }
    addi_user_cache(_cuser_hm_, user_poin);
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int ddel_user_bzl(prod_data *sresp, char *cuse_name) {
    printf("ddel_user_bzl\n");
    if (!cuse_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check users data error!");
    user_privi *user_poin = find_user_cache(_cuser_hm_, cuse_name);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    dele_user_cache(_cuser_hm_, user_poin);
    if (dele_cuser_data(coval, &_priv_list_.cuse_list, user_poin)) {
        PDAT_EXCEP_TAIL(sresp, DELE_USER_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int dgran_role_bzl(prod_data *sresp, char *cuse_name, char *role_name) {
    printf("dgran_role_bzl\n");
    if (!cuse_name || !role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check users data error!");
    role_privi *role_poin = find_osdb_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    user_privi *user_poin = find_user_privi(_priv_list_.cuse_list, cuse_name);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    //
    if (osdb_role_bzl(user_poin, role_poin)) {
        PDAT_EXCEP_TAIL(sresp, USER_ROLE_EXIS)
        return ERR_FAULT;
    }
    if (dgran_role_data(coval, user_poin, role_poin)) {
        PDAT_EXCEP_TAIL(sresp, GRAN_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

int drevk_role_bzl(prod_data *sresp, char *cuse_name, char *role_name) {
    printf("drevk_role_bzl\n");
    if (!cuse_name || !role_name) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return ERR_FAULT;
    }
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) {
        PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
        return ERR_FAULT;
    }
    // _LOG_DEBUG("check users data error!");
    role_privi *role_poin = find_osdb_role(_priv_list_.role_list, role_name);
    if (!role_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    user_privi *user_poin = find_user_privi(_priv_list_.cuse_list, cuse_name);
    if (!user_poin) {
        PDAT_EXCEP_TAIL(sresp, FIND_USER_EXCE)
        return ERR_FAULT;
    }
    if (drevk_role_data(coval, user_poin, role_poin)) {
        PDAT_EXCEP_TAIL(sresp, REVK_ROLE_EXCE)
        return ERR_FAULT;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return ERR_SUCCESS;
}

//

int check_reque_bzl(char *valid, char *req_valid, char *req_salt) {
    printf("[DEBUG] valid:|%s| req_salt:|%s|\n", valid, req_salt);
    if (!valid[0x00]) return ERR_SUCCESS; // no authen
    //
    char hash_valid[VALID_TEXT_LENGTH];
    salt_auth_chks(hash_valid, valid, req_salt);
    //
    char temp[33];
    strzcpy(temp, hash_valid, 32);
    printf("[DEBUG] odb ldata->req_valid:|%s|\n", temp);
    //
    return strcmp(hash_valid, req_valid);
}

//

uint32 reset_privile_bzl(osv_oid_t *oid, uint32 leve_mask) {
    if (OSDB_LEVE_OTTF == leve_mask) return 0x00;
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) return -1;
    //
    role_privi role_dat;
    struct liv_list *rlist = _priv_list_.role_list;
    for (; rlist; rlist = rlist->next) {
        if (check_privi_oid((role_privi *) rlist->liv_data, oid)) {
            if (live_load(&role_dat, coval, AUTH_ROLES_CONT, &((role_privi *) rlist->liv_data)->oid))return -1;
            if (reset_privile_mask(&role_dat, oid, leve_mask))
                return -1;
            memcpy(rlist->liv_data, &role_dat, sizeof (role_privi));
        }
    }
    //
    return 0x00;
}

uint32 reset_privalu_bzl(osv_oid_t *oid, char *osdb) {
    struct osdb_stat rstat;
    if (rstat_osdb_bzl(&rstat, osdb))return INVA_PRIV;
    if (OSDB_LEVE_OTTF == rstat.leve_valu) return OSDB_LEVE_OTTF;
    conoda *coval = find_conto_bzl(OSEV_ADMIN_VALUE);
    if (!coval) return -1;
    //
    role_privi role_dat;
    struct liv_list *rlist = _priv_list_.role_list;
    for (; rlist; rlist = rlist->next) {
        if (check_privi_oid((role_privi *) rlist->liv_data, oid)) {
            if (live_load(&role_dat, coval, AUTH_ROLES_CONT, &((role_privi *) rlist->liv_data)->oid))return INVA_PRIV;
            if (reset_privile_mask(&role_dat, oid, rstat.leve_valu))
                return INVA_PRIV;
            memcpy(rlist->liv_data, &role_dat, sizeof (role_privi));
        }
    }
    //
    return rstat.leve_valu;
}
