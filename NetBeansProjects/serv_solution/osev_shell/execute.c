#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "shel_macro.h"
#include "commo_header.h"
#include "clie_obje.h"
#include "connect.h"
#include "prepa_prompt.h"
#include "execute.h"

//
// 0:ok -1:err

static int hand_clie_conne(shel_resu *resu, char *conne_str) {
    if (URISTR_ILLEGAL == parse_conne_uristr(&_clie_auth_, conne_str))
        return -1;
    _conne_type_ = get_conne_type(conne_str);
    // printf("[debug] hand_clie_conne conne_type:%d conne_str:%s\n", conne_type, conne_str);
    switch (_conne_type_) {
        case OSEV_CONNE:
            printf("------ shell connect to %s osev.\n", conne_str);
            _shell_clie_ = conne_osev(&_clie_auth_);
            if (!_shell_clie_) return -1;
            printf("------ shell connect OK.\n");
            break;
        case OSDB_CONNE:
            printf("------ shell connect to %s osdb.\n", conne_str);
            _shell_clie_ = conne_osev(&_clie_auth_);
            if (!_shell_clie_) return -1;
            printf("------ shell connect OK.\n");
            break;
        case NULL_CONNE:
        default:
            return -1;
            break;
    }
    //
    return 0x00;
}

//

static int clie_execu(shel_resu *resu, osev_command *oscmd) {
    int exec_valu = 0x00;
    switch (oscmd->comd_valu) {
        case comd_conne:
            quote_decode(oscmd->paras[0x00]);
            exec_valu = hand_clie_conne(resu, oscmd->paras[0x00]);
            break;
        case comd_exit:
        case comd_bye:
            break;
        case comd_clie:
            break;
        default:
            break;
    }
    //
    return exec_valu;
}

//

// 0:ok -1:err

static int hand_osev_use(shel_resu *resu, char **paras) {
    printf("hand osev use. osdb:%s\n", paras[0x00]);
    printf("------ shell disconne.\n");
    //
    kill_quote(paras)
    if (paras[0x01]) _shell_clie_ = conne_osdb_auth(_shell_clie_, paras[0x00], paras[0x01], paras[0x02]);
    else _shell_clie_ = conne_osdb_noau(_shell_clie_, paras[0x00]);
    if (!_shell_clie_) return -1;
    //
    return 0x00;
}

//

static int hand_osev_stat(shel_resu *resu, unsigned int stat_valu, char *obje_iden, char **paras) {
    printf("hand osev leve stat. obje_iden:%s\n", obje_iden);
    osv_oid_t obje_oid;
    if (strcmp(OSEV_DEFAULT_VALUE, obje_iden)) CREAT_OSDB(&obje_oid, &_shell_clie_->oid)
    else memcpy(&obje_oid, &_shell_clie_->oid, sizeof (osv_oid_t));
    //
    resp_data_t osev_resp;
    int osev_valu = osev_leve_stat(&osev_resp, stat_valu, _shell_clie_, &obje_oid, paras);
    memcpy(resu->resu_data, osev_resp.res_data, osev_resp.resp_len);
    resu->res_len = osev_resp.resp_len;
    resu->resu_type = 0x00;
    // printf("none response:\n%s\n", none_str);
    pthread_mutex_lock(&_conta_cache_mutex_);
    erase_osdb(_conta_cache_hm_, paras[0x00], obje_iden, stat_valu);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    return osev_valu;
}

//

static int hand_osev_priv(shel_resu *resu, unsigned int privi_valu, char *obje_iden, char **paras) {
    printf("hand osev leve priv. obje_iden:%s\n", obje_iden);
    resp_data_t osev_resp;
    int osev_valu = -1;
    if (!strcmp(OSEV_PRIVILE_VALUE, obje_iden)) {
        osev_valu = osev_leve_priv(&osev_resp, privi_valu, _shell_clie_, &_shell_clie_->oid, paras);
    } else if (!strcmp(OSDB_PRIVILE_VALUE, obje_iden)) {
        osv_oid_t oid;
        CREAT_OSDB(&oid, &_shell_clie_->oid);
        osev_valu = osev_leve_priv(&osev_resp, privi_valu, _shell_clie_, &oid, paras);
    }
    memcpy(resu->resu_data, osev_resp.res_data, osev_resp.resp_len);
    resu->res_len = osev_resp.resp_len;
    resu->resu_type = 0x00;
    // printf("none response:\n%s\n", none_str);
    return osev_valu;
}

static int hand_osev_quit() {
    printf("hand osev quit.\n");
    pthread_mutex_lock(&_colle_cache_mutex_);
    reset_cache(_colle_cache_hm_);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    //
    printf("------ clear client cache.\n");
    pthread_mutex_lock(&_conta_cache_mutex_);
    reset_cache(_conta_cache_hm_);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    printf("------ shell disconne.\n");
    _shell_clie_ = quit_osev(_shell_clie_);
    return 0x00;
}

//

static int osev_execu(shel_resu *resu, osev_command *oscmd) {
    int exec_valu = 0x00;
    switch (oscmd->comd_valu) {
        case comd_exit:
            exec_valu = hand_osev_quit();
            break;
        case comd_use:
            exec_valu = hand_osev_use(resu, oscmd->paras);
            break;
        case comd_stat:
            exec_valu = hand_osev_stat(resu, oscmd->meth_valu, oscmd->obje_iden, oscmd->paras);
            break;
        case comd_priv:
            exec_valu = hand_osev_priv(resu, oscmd->meth_valu, oscmd->obje_iden, oscmd->paras);
            break;
        case comd_quit:
            exec_valu = hand_osev_quit();
            break;
        default:
            break;
    }
    //
    return exec_valu;
}

//
// 0:ok -1:err

static int hand_osdb_quit() {
    pthread_mutex_lock(&_colle_cache_mutex_);
    reset_cache(_colle_cache_hm_);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    //
    printf("------ clear client cache.\n");
    pthread_mutex_lock(&_conta_cache_mutex_);
    reset_cache(_conta_cache_hm_);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    //
    if (OSEV_CONNE == _conne_type_) {
        printf("------ shell connect to %s.\n", _clie_auth_.osev_osdb);
        _shell_clie_ = quit_osdb(_shell_clie_, &_clie_auth_);
        if (!_shell_clie_) return -1;
    } else if (OSDB_CONNE == _conne_type_) {
        printf("------ shell disconne.\n");
        _shell_clie_ = _quit_osev_(_shell_clie_);
    }
    //
    return 0x00;
}

//

static int hand_onel_syst(shel_resu *resu, unsigned int invo_valu, char *obje_iden, char **paras) {
    printf("hand odb onel system.\n");
    osv_oid_t *obje_oid;
    if (strcmp(OSDB_DEFAULT_VALUE, obje_iden)) {
        pthread_mutex_lock(&_colle_cache_mutex_);
        obje_oid = find_colle(_colle_cache_hm_, obje_iden, _shell_clie_);
        pthread_mutex_unlock(&_colle_cache_mutex_);
    } else obje_oid = &_shell_clie_->oid;
    if (!obje_oid) {
        printf("not find the conta.\n");
        return -1;
    }
    //
    int onel_valu = 0x00;
    resp_data_t onel_resp;
    onel_valu = osdb_leve_one(&onel_resp, invo_valu, _shell_clie_, obje_oid, paras);
    memcpy(resu->resu_data, onel_resp.res_data, onel_resp.resp_len);
    resu->res_len = onel_resp.resp_len;
    resu->resu_type = 0x00;
    // printf("onel response:\n%s\n", onel_str);
    return onel_valu;
}

static int leve_one_execu(shel_resu *resu, osev_command *oscmd) {
    int exec_valu = 0x00;
    switch (oscmd->comd_valu) {
        case comd_level:
            break;
        case comd_quit:
            exec_valu = hand_osdb_quit();
            break;
        case comd_leve:
            exec_valu = hand_onel_syst(resu, oscmd->meth_valu, oscmd->obje_iden, oscmd->paras);
            break;
        default:
            break;
    }
    //
    return exec_valu;
}

//

static int hand_twol_syst(shel_resu *resu, unsigned int coll_valu, char **paras) {
    printf("hand odb twol system.\n");
    int twol_valu = 0x00;
    //
    resp_data_t twol_resp;
    twol_valu = osdb_leve_twop(&twol_resp, coll_valu, _shell_clie_, paras);
    memcpy(resu->resu_data, twol_resp.res_data, twol_resp.resp_len);
    resu->res_len = twol_resp.resp_len;
    resu->resu_type = 0x00;
    // printf("twol response:\n%s\n", twol_str);
    pthread_mutex_lock(&_colle_cache_mutex_);
    erase_colle(_colle_cache_hm_, paras[0x00], coll_valu);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    return twol_valu;
}

static int leve_twop_execu(shel_resu *resu, osev_command *oscmd) {
    int exec_valu = 0x00;
    switch (oscmd->comd_valu) {
        case comd_level:
            break;
        case comd_quit:
            exec_valu = hand_osdb_quit();
            break;
        case comd_leve:
            exec_valu = hand_twol_syst(resu, oscmd->meth_valu, oscmd->paras);
            break;
        default:
            break;
    }
    //
    return exec_valu;
}

//

static int hand_thrl_syst(shel_resu *resu, unsigned int quer_valu, char *obje_iden, char **paras) {
    printf("hand odb thrl system.\n");
    osv_oid_t *obje_oid;
    if (strcmp(OSDB_DEFAULT_VALUE, obje_iden)) {
        pthread_mutex_lock(&_conta_cache_mutex_);
        obje_oid = find_conta(_conta_cache_hm_, obje_iden, _shell_clie_);
        pthread_mutex_unlock(&_conta_cache_mutex_);
    } else obje_oid = &_leve_defa_obje_.obje_oid;
    if (!obje_oid) {
        printf("not find the conta.\n");
        return -1;
    }
    //
    int thrl_valu = 0x00;
    resp_data_t thrl_resp;
    thrl_valu = osdb_leve_thre(&thrl_resp, quer_valu, _shell_clie_, obje_oid, paras);
    memcpy(resu->resu_data, thrl_resp.res_data, thrl_resp.resp_len);
    resu->res_len = thrl_resp.resp_len;
    resu->resu_type = 0x00;
    // printf("resu->res_len:%llu\n", resu->res_len);
    // log_binary_file((unsigned char *)thrl_resp.res_data, thrl_resp.resp_len, "./binary_code.bin_c");
    // printf("thrl response:\n%s\n", thrl_str);
    return thrl_valu;
}

static int leve_three_execu(shel_resu *resu, osev_command *oscmd) {
    int exec_valu = 0x00;
    switch (oscmd->comd_valu) {
        case comd_level:
            break;
        case comd_quit:
            exec_valu = hand_osdb_quit();
            break;
        case comd_leve:
            exec_valu = hand_thrl_syst(resu, oscmd->meth_valu, oscmd->obje_iden, oscmd->paras);
            break;
        default:
            break;
    }
    //
    return exec_valu;
}

//

static int hand_foul_syst(shel_resu *resu, unsigned int quer_valu, char **paras) {
    printf("hand odb foul system.\n");
    int foul_valu = 0x00;
    resp_data_t foul_resp;
    foul_valu = osdb_leve_foup(&foul_resp, quer_valu, _shell_clie_, paras);
    memcpy(resu->resu_data, foul_resp.res_data, foul_resp.resp_len);
    resu->res_len = foul_resp.resp_len;
    resu->resu_type = 0x00;
    // log_binary_file((unsigned char *)foul_resp.res_data, foul_resp.resp_len, "./binary_code.bin_c");
    // printf("foul response:\n%s\n", foul_str)
    pthread_mutex_lock(&_conta_cache_mutex_);
    erase_conta(_conta_cache_hm_, paras[0x00], quer_valu);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    return foul_valu;
}

static int leve_foup_execu(shel_resu *resu, osev_command *oscmd) {
    int exec_valu = 0x00;
    switch (oscmd->comd_valu) {
        case comd_level:
            break;
        case comd_quit:
            exec_valu = hand_osdb_quit();
            break;
        case comd_leve:
            exec_valu = hand_foul_syst(resu, oscmd->meth_valu, oscmd->paras);
            break;
        default:
            break;
    }
    //
    return exec_valu;
}

//

int method_execute(shel_resu *resu, shel_stat_t *shel_stat, osev_command *oscmd) {
    int exec_valu = 0x00;
    switch (shel_stat->shell_mode) {
        case SHTP_CLIE:
            exec_valu = clie_execu(resu, oscmd);
            break;
        case SHTP_OSEV:
            exec_valu = osev_execu(resu, oscmd);
            break;
        case SHTP_LEVE:
            switch (ONLY_LEVEL_VALUE(shel_stat->run_level)) {
                case LEVE_ONE:
                    exec_valu = leve_one_execu(resu, oscmd);
                    break;
                case LEVE_TWOP:
                    exec_valu = leve_twop_execu(resu, oscmd);
                    break;
                case LEVE_THRE:
                    exec_valu = leve_three_execu(resu, oscmd);
                    break;
                case LEVE_FOUP:
                    exec_valu = leve_foup_execu(resu, oscmd);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    //
    return exec_valu;
}
