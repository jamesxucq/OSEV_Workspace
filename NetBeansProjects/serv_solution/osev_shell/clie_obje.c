
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"

#include"connect.h"
#include "clie_obje.h"


//
actionmap *_colle_cache_hm_;
pthread_mutex_t _colle_cache_mutex_;

actionmap *_conta_cache_hm_;
pthread_mutex_t _conta_cache_mutex_;

//
osev_clie *_shell_clie_;
int _conne_type_ = NULL_CONNE;
svod_auth _clie_auth_;

//

void cache_free(void *data) {
    if (data) free(data);
}

//
// osvp://[username:password]@host1[:port1][/[database][?options]]
// osvp://james:123456@10.0.0.103:8848
#define OSVP_HEAD "osvp://"
#define HEAD_LENG 0x07

int get_conne_type(char *conne_str) {
    char *toke = conne_str;
    toke = strstr(toke, OSVP_HEAD);
    if (!toke) return NULL_CONNE;
    //
    toke = strchr(toke + HEAD_LENG, '/');
    if (!toke) return OSEV_CONNE;
    toke++;
    if ('\0' == toke[0x00] || !strcmp(OSEV_DEFAULT_VALUE, toke)) return OSEV_CONNE;
    //
    return OSDB_CONNE;
}

//

char *get_osev_osdb(char *osev_osdb) {
    if (_clie_auth_.osev_osdb[0x00]) strcpy(osev_osdb, _clie_auth_.osev_osdb);
    else strcpy(osev_osdb, OSEV_DEFAULT_VALUE);
    return osev_osdb;
}

//

osev_clie *conne_osdb_noau(osev_clie *clie, char *osdb) {
    svod_auth clus_auth;
    if (clie && !strcmp(clie->osev_osdb, osdb)) return clie;
    //
    memcpy(&clus_auth, &_clie_auth_, sizeof (svod_auth));
    strcpy(clus_auth.osev_osdb, osdb);
    printf("------ noauth connect to %s.\n", osdb);
    // printf("connect to %s ...\n", conne_str);
    return reconne_osev(clie, &clus_auth);
}

//

osev_clie *conne_osdb_auth(osev_clie *clie, char *osdb, char *name, char *paswd) {
    svod_auth clus_auth;
    if (clie && !strcmp(clie->osev_osdb, osdb)) return clie;
    //
    memcpy(&clus_auth.saddr, &_clie_auth_.saddr, sizeof (serv_addr));
    strcpy(clus_auth.osev_osdb, osdb);
    strcpy(clus_auth.auth.user_name, name);
    strcpy(clus_auth.auth.pass_word, paswd);
    printf("------ auth connect to %s.\n", osdb);
    // printf("connect to %s ...\n", conne_str);
    return reconne_osev(clie, &clus_auth);
}

//

osv_oid_t *find_conta(actionmap *cobje_hm, char *conta, osev_clie *clie) {
    // printf("find_conta, start. conta:%s\n", conta);
    osv_oid_t *obje_oid = (osv_oid_t *) action_value(conta, cobje_hm);
    if (obje_oid) return obje_oid;
    //
    char epara[PARAM_LENGTH];
    strcpy(epara, conta);
    char *paras[0x02] = {epara, NULL};
    resp_data_t quer_resp;
    if (!query_conta_echo(&quer_resp, clie, paras)) {
        obje_valu *ovalu = (obje_valu*) malloc(sizeof (obje_valu));
        if (!ovalu) return NULL;
        memcpy(&ovalu->obje_oid, quer_resp.res_data, sizeof (osv_oid_t));
        strcpy(ovalu->obje_iden, conta);
        action_insert(ovalu->obje_iden, ovalu, cobje_hm);
        //
        obje_oid = &ovalu->obje_oid;
    }
    //
    char oid_stri[OID_LINE_LEN];
    if (obje_oid) printf("find_conta, echo %s oid:|%s|\n", conta, oidstr(oid_stri, obje_oid));
    return obje_oid;
}

void erase_conta(actionmap *cobje_hm, char *conta, unsigned int quer_valu) {
    char obje_iden[OBJE_LENGTH];
    if (quer_drop == quer_valu) {
        strcpy(obje_iden, conta);
        quote_decode(obje_iden);
        printf("erase_conta, conta %s obje_iden:%s\n", conta, obje_iden);
        action_remove(obje_iden, cobje_hm);
    }
}

//

osv_oid_t *find_osdb(actionmap *cobje_hm, char *osdb, osev_clie *clie) {
    // printf("find_osdb, start. conta:%s\n", conta);
    osv_oid_t *obje_oid = (osv_oid_t *) action_value(osdb, cobje_hm);
    if (obje_oid) return obje_oid;
    //
    osv_oid_t osdb_oid;
    CREAT_OSDB(&osdb_oid, &clie->oid)
            char epara[PARAM_LENGTH];
    strcpy(epara, osdb);
    char *paras[0x02] = {epara, NULL};
    //
    resp_data_t stat_resp;
    if (!osev_statu_echo(&stat_resp, clie, &osdb_oid, paras)) {
        obje_valu *ovalu = (obje_valu*) malloc(sizeof (obje_valu));
        if (!ovalu) return NULL;
        memcpy(&ovalu->obje_oid, stat_resp.res_data, sizeof (osv_oid_t));
        strcpy(ovalu->obje_iden, osdb);
        action_insert(ovalu->obje_iden, ovalu, cobje_hm);
        //
        obje_oid = &ovalu->obje_oid;
    }
    //
    return obje_oid;
}

//

void erase_osdb(actionmap *cobje_hm, char *osdb, char *obje_iden, unsigned int stat_valu) {
    char osdb_iden[OBJE_LENGTH];
    if ((stat_close == stat_valu) && !strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        strcpy(osdb_iden, osdb);
        quote_decode(osdb_iden);
        printf("erase_conta, osdb %s obje_iden:%s\n", osdb, osdb_iden);
        action_remove(osdb_iden, cobje_hm);
    }
}

//

#define INVO_LIST_OBJID "OBJID"

osv_oid_t *find_colle(actionmap *cobje_hm, char *colle, osev_clie *clie) {
    // printf("find_cinvo, start. conta:%s\n", conta);
    osv_oid_t *obje_oid = (osv_oid_t *) action_value(colle, cobje_hm);
    if (obje_oid) return obje_oid;
    //
    char *paras[0x03] = {NULL, INVO_LIST_OBJID, NULL};
    paras[0x00] = colle;
    resp_data_t invo_resp;
    if (!obje_colle_list(&invo_resp, clie, paras)) {
        obje_valu *ovalu = (obje_valu*) malloc(sizeof (obje_valu));
        if (!ovalu) return NULL;
        stroid(&ovalu->obje_oid, invo_resp.res_data);
        strcpy(ovalu->obje_iden, colle);
        action_insert(ovalu->obje_iden, ovalu, cobje_hm);
        //
        obje_oid = &ovalu->obje_oid;
    }
    //
    char oid_stri[OID_LINE_LEN];
    if (obje_oid) printf("find_cinvo, echo %s oid:|%s|\n", colle, oidstr(oid_stri, obje_oid));
    return obje_oid;
}

void erase_colle(actionmap *cobje_hm, char *colle, unsigned int coll_valu) {
    char obje_iden[OBJE_LENGTH];
    if (coll_drop == coll_valu) {
        strcpy(obje_iden, colle);
        quote_decode(obje_iden);
        printf("erase_cinvo, invok %s obje_iden:%s\n", colle, obje_iden);
        action_remove(obje_iden, cobje_hm);
    }
}

//
obje_valu _leve_defa_obje_;
shel_stat_t _last_shel_stat_;