
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "method.h"
#include "clie_obje.h"
#include "shel_macro.h"
#include "prepa_prompt.h"
#include "builtin_command.h"
#include "parse_command.h"

//

uint32 builtin_command(osev_command *oscmd, uint32 shell_mode) {
    uint32 clie_valu = shell_mode;
    //
    if (SHTP_LEVE == shell_mode) {
        if (comd_quit == oscmd->comd_valu) {
            if (OSEV_CONNE == _conne_type_) clie_valu = SHTP_OSEV;
            else if (OSDB_CONNE == _conne_type_) clie_valu = SHTP_CLIE;
        }
    } else if (SHTP_OSEV == shell_mode) {
        if (comd_use == oscmd->comd_valu) clie_valu = SHTP_LEVE;
        else if (comd_quit == oscmd->comd_valu) clie_valu = SHTP_CLIE;
        else if (comd_exit == oscmd->comd_valu) clie_valu = SHEL_TYPE_EXIT;
    } else if (SHTP_CLIE == shell_mode) {
        if (comd_conne == oscmd->comd_valu) {
            printf("builtin_command conne_type:%d\n", _conne_type_);
            if (OSEV_CONNE == _conne_type_) clie_valu = SHTP_OSEV;
            else if (OSDB_CONNE == _conne_type_) clie_valu = SHTP_LEVE;
        } else if (comd_exit == oscmd->comd_valu || comd_bye == oscmd->comd_valu)
            clie_valu = SHEL_TYPE_EXIT;
    }
    //
    return clie_valu;
}

//

struct value_node {
    const char *stri;
    const char *alph;
    int value;
};

static const struct value_node level_value_table[] = {
    {"1", "1", LEVE_ONE},
    {"2p", "2+", LEVE_TWOP},
    {"3", "3", LEVE_THRE},
    {"4p", "4+", LEVE_FOUP},
    {NULL, NULL, 0xFFFFFFFF}
};

#define TEXT_VALUE(VALUE, TABLE, TEXT) { \
    struct value_node *item; \
    for(item = (struct value_node *)TABLE; item->stri; ++item) \
        if(!strcasecmp(item->stri, TEXT) || !strcasecmp(item->alph, TEXT)) break; \
    VALUE = item->value; \
}

//

static int check_level_colle(char *coll_valu) {
    // printf("check_level_colle, coll_valu:|%s|\n", coll_valu);
    osv_oid_t *obje_oid;
    //
    pthread_mutex_lock(&_colle_cache_mutex_);
    obje_oid = find_colle(_colle_cache_hm_, coll_valu, _shell_clie_);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    if (!obje_oid) return 0x00;
    //
    strcpy(_leve_defa_obje_.obje_iden, coll_valu);
    memcpy(&_leve_defa_obje_.obje_oid, obje_oid, sizeof (osv_oid_t));
    _leve_defa_obje_.changed = 0x01;
    // printf("check_level_conta, obje_iden:|%s|\n", _leve_defa_obje_.obje_iden);
    return 0x01;
}

static int check_level_conta(char *cont_valu) {
    // printf("check_level_conta, cont_valu:|%s|\n", cont_valu);
    osv_oid_t *obje_oid;
    //
    pthread_mutex_lock(&_conta_cache_mutex_);
    obje_oid = find_conta(_conta_cache_hm_, cont_valu, _shell_clie_);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    if (!obje_oid) return 0x00;
    //
    strcpy(_leve_defa_obje_.obje_iden, cont_valu);
    memcpy(&_leve_defa_obje_.obje_oid, obje_oid, sizeof (osv_oid_t));
    _leve_defa_obje_.changed = 0x01;
    // printf("check_level_conta, obje_iden:|%s|\n", _leve_defa_obje_.obje_iden);
    return 0x01;
}

static uint32 run_level_exte(uint32 last_leve, char *clie_valu) {
    // printf("run_level_exte, last_leve:%08X clie_valu:|%s|\n", last_leve, clie_valu);
    uint32 run_level = last_leve;
    //
    switch (ONLY_LEVEL_VALUE(last_leve)) {
        case LEVE_ONE:
        case LEVE_TWOP:
            if (check_level_colle(clie_valu)) {
                run_level = LEVE_ONE;
                SET_EXTEND_SPACE(run_level);
            }
            break;
        case LEVE_THRE:
        case LEVE_FOUP:
            if (check_level_conta(clie_valu)) {
                run_level = LEVE_THRE;
                SET_EXTEND_SPACE(run_level);
            }
            break;
    }
    // printf("run_level_exte, run_level:%08X\n", run_level);
    return run_level;
}

uint32 clie_run_level(osev_command *oscmd, uint32 last_leve) {
    uint32 leve_valu = last_leve;
    // printf("[debug] oscmd->comd_valu:%d\n", oscmd->comd_valu);
    switch (oscmd->comd_valu) {
        case comd_conne:
        case comd_use:
            leve_valu = LEVE_FOUP;
            break;
        case comd_leve:
            leve_valu = last_leve;
            break;
        case comd_level:
            quote_decode(oscmd->paras[0x00]);
            TEXT_VALUE(leve_valu, level_value_table, oscmd->paras[0x00])
            if (0xFFFFFFFF == leve_valu) leve_valu = run_level_exte(last_leve, oscmd->paras[0x00]);
            break;
        default:
            break;
    }
    // printf("[debug]clie_run_level leve_valu:%d paras:%s\n", leve_valu, oscmd->paras[0x00]);
    return leve_valu;
}