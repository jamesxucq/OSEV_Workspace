#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "commo_header.h"
#include "dstr_utili.h"
#include "osev_clie.h"


//

osev_clie *osev_clie_create(char *usern, char *paswd, char *addr, int port, char *osev_osdb) {
    printf("osev_clie_create\n");
    printf("addr:|%s| port:%d\n", addr, port);
    printf("osev_osdb:|%s| usern:|%s| paswd:|%s|\n", osev_osdb, usern, paswd);
    serv_addr saddr;
    struct authe_ine authe;
    char *paras[0x02] = {osev_osdb, NULL};
    //
    creat_authe_ine(&authe, usern, paswd);
    strcpy(saddr.sin_addr, addr);
    saddr.sin_port = port;
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return NULL;
    //
    osev_clie *clie = NULL;
    clie = (osev_clie *) malloc(sizeof (osev_clie));
    if (!clie) return NULL;
    //
    strcpy(clie->osev_osdb, osev_osdb);
    clie->conne_sock = osco_connect(&saddr);
    if (-1 == clie->conne_sock) {
        osco_close(clie->conne_sock);
        free(clie);
        printf("    osev connect error!\n");
        return NULL;
    }
    //
    resp_data_t clie_resp;
    if (clie_create_bzl(&clie_resp, clie->conne_sock, &authe, &pstyl)) {
        osco_close(clie->conne_sock);
        free(clie);
        printf("    osev osauth error!\n");
        return NULL;
    }
    memcpy(&clie->oid, clie_resp.res_data, sizeof (osv_oid_t));
    // printf("[DEBUG] osev_osdb:%s user_name:%s\n", authen->auth.osev_osdb, authen->auth.user_name);
    char temp[33];
    printf("[DEBUG] clie->oid:|%s|\n", oidstr(temp, &clie->oid));
    printf("    osev clie create ok!\n");
    return clie;
}

//

void osev_clie_destroy(osev_clie *clie) {
    printf("osev_clie_destroy\n");
    if (clie) {
        clie_destroy_bzl(clie->conne_sock, &clie->oid);
        osco_close(clie->conne_sock);
        free(clie);
    }
}

//
// status

int osev_statu_echo(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_statu_echo\n");
    printf("paras, [0]:|%s| [1]:|%s|\n", paras[0x00], paras[0x01]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_status_bzl(statu_resp, clie->conne_sock, STAT_ECHO, oid, &pstyl)) {
        printf("    osev echo error!\n");
        return -1;
    }
    //
    return 0x00;
}

int osev_statu_open(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_statu_open:|%s|\n", paras[0x00]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_status_bzl(statu_resp, clie->conne_sock, STAT_OPEN, oid, &pstyl)) {
        printf("    osev open error!\n");
        return -1;
    }
    //
    return 0x00;
}

int osev_statu_close(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_statu_close\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_status_bzl(statu_resp, clie->conne_sock, STAT_CLOSE, oid, &pstyl)) {
        printf("    osev close error!\n");
        return -1;
    }
    //
    return 0x00;
}

int osev_statu_status(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_statu_status\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_status_bzl(statu_resp, clie->conne_sock, STAT_STATUS, oid, &pstyl)) {
        printf("    osev status error!\n");
        return -1;
    }
    //
    return 0x00;
}

//

int osev_statu_stati(resp_data_t *statu_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_statu_stati\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_status_bzl(statu_resp, clie->conne_sock, STAT_STATI, oid, &pstyl)) {
        printf("    osev privi error!\n");
        return -1;
    }
    //
    return 0x00;
}

// privilege

int osev_privi_list(resp_data_t *privi_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_privi_list\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_privile_bzl(privi_resp, clie->conne_sock, PRIV_ECHO, oid, &pstyl)) {
        printf("    osev echo error!\n");
        return -1;
    }
    //
    return 0x00;
}

int osev_privi_role(resp_data_t *privi_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_privi_role\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_privile_bzl(privi_resp, clie->conne_sock, PRIV_ROLE, oid, &pstyl)) {
        printf("    osev delete user error!\n");
        return -1;
    }
    //
    return 0x00;
}

int osev_privi_user(resp_data_t *privi_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("osev_privi_user\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_privile_bzl(privi_resp, clie->conne_sock, PRIV_USER, oid, &pstyl)) {
        printf("    osev addi user error!\n");
        return -1;
    }
    //
    return 0x00;
}

// method invoke

int obje_invok_list(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("obje_invok_list\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == invok_list_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_invok_bzl(invok_resp, clie->conne_sock, INVO_LIST, oid, &pstyl)) {
        printf("    invok echo error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_invok_creat(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("obje_invok_creat\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_invok_bzl(invok_resp, clie->conne_sock, INVO_CREAT, oid, &pstyl)) {
        printf("    invok creat error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_invok_repla(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("obje_invok_repla\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_invok_bzl(invok_resp, clie->conne_sock, INVO_REPLA, oid, &pstyl)) {
        printf("    invok repla error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_invok_drop(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("obje_invok_drop\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_invok_bzl(invok_resp, clie->conne_sock, INVO_DROP, oid, &pstyl)) {
        printf("    invok drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_invok_integri(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("obje_invok_integri\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_invok_bzl(invok_resp, clie->conne_sock, INVO_INTEGRI, oid, &pstyl)) {
        printf("    invok integri error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_invok_reload(resp_data_t *invok_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("obje_invok_reload\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_invok_bzl(invok_resp, clie->conne_sock, INVO_RELOAD, oid, &pstyl)) {
        printf("    invok reload error!\n");
        return -1;
    }
    //
    return 0x00;
}

// class invoke

int obje_colle_list(resp_data_t *colle_resp, osev_clie *clie, char **paras) {
    printf("obje_colle_list\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s|\n", paras[0x00], paras[0x01], paras[0x02]);
    osv_pstyl_t pstyl;
    if (-1 == colle_list_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_colle_bzl(colle_resp, clie->conne_sock, COLE_LIST, &clie->oid, &pstyl)) {
        printf("    colle echo error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_colle_creat(resp_data_t *colle_resp, osev_clie *clie, char **paras) {
    printf("obje_colle_creat\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_colle_bzl(colle_resp, clie->conne_sock, COLE_CREAT, &clie->oid, &pstyl)) {
        printf("    colle creat error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_colle_repla(resp_data_t *colle_resp, osev_clie *clie, char **paras) {
    printf("obje_colle_repla\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_colle_bzl(colle_resp, clie->conne_sock, COLE_REPLA, &clie->oid, &pstyl)) {
        printf("    colle repla error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_colle_drop(resp_data_t *colle_resp, osev_clie *clie, char **paras) {
    printf("obje_colle_drop\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_colle_bzl(colle_resp, clie->conne_sock, COLE_DROP, &clie->oid, &pstyl)) {
        printf("    colle drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_colle_integri(resp_data_t *colle_resp, osev_clie *clie, char **paras) {
    printf("obje_colle_integri\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_colle_bzl(colle_resp, clie->conne_sock, COLE_INTEGRI, &clie->oid, &pstyl)) {
        printf("    colle integri error!\n");
        return -1;
    }
    //
    return 0x00;
}

int obje_colle_reload(resp_data_t *colle_resp, osev_clie *clie, char **paras) {
    printf("obje_colle_reload\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_colle_bzl(colle_resp, clie->conne_sock, COLE_RELOAD, &clie->oid, &pstyl)) {
        printf("    colle reload error!\n");
        return -1;
    }
    //
    return 0x00;
}

// construct

int const_entry_echo(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("const_entry_echo\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    printf("clie_const_bzl\n");
    if (clie_const_bzl(const_resp, clie->conne_sock, CONS_ECHO, oid, &pstyl)) {
        printf("    query echo error!\n");
        return -1;
    }
    //
    return 0x00;
}

int const_entry_creat(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("const_entry_creat\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_const_bzl(const_resp, clie->conne_sock, CONS_CREAT, oid, &pstyl)) {
        printf("    query creat error!\n");
        return -1;
    }
    //
    return 0x00;
}

int const_entry_drop(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("const_entry_drop\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_const_bzl(const_resp, clie->conne_sock, CONS_DROP, oid, &pstyl)) {
        printf("    query drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

int const_entry_updat(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("const_entry_updat\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_const_bzl(const_resp, clie->conne_sock, CONS_UPDAT, oid, &pstyl)) {
        printf("    query updat error!\n");
        return -1;
    }
    //
    return 0x00;
}

int const_entry_inser(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("const_entry_inser\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_const_bzl(const_resp, clie->conne_sock, CONS_INSER, oid, &pstyl)) {
        printf("    query inser error!\n");
        return -1;
    }
    //
    return 0x00;
}

int const_entry_find(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("const_entry_find\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_const_bzl(const_resp, clie->conne_sock, CONS_FIND, oid, &pstyl)) {
        printf("    const find error!\n");
        return -1;
    }
    //
    return 0x00;
}

int const_entry_invok(resp_data_t *const_resp, osev_clie *clie, osv_oid_t *oid, char **paras) {
    printf("const_entry_invok\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == const_invok_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_const_bzl(const_resp, clie->conne_sock, CONS_INVOK, oid, &pstyl)) {
        printf("    query invok error!\n");
        return -1;
    }
    //
    return 0x00;
}

//

int query_conta_echo(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_echo\n");
    printf("paras, [0]:|%s| [1]:|%s|\n", paras[0x00], paras[0x01]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_ECHO, &clie->oid, &pstyl)) {
        printf("    query echo error!\n");
        return -1;
    }
    //
    return 0x00;
}

int query_conta_creat(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_creat\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == dist_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_CREAT, &clie->oid, &pstyl)) {
        printf("    query creat error!\n");
        return -1;
    }
    //
    return 0x00;
}

int query_conta_drop(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_drop\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_DROP, &clie->oid, &pstyl)) {
        printf("    query drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

int query_conta_updat(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_updat\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_UPDAT, &clie->oid, &pstyl)) {
        printf("    query drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

int query_conta_inser(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_inser\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_INSER, &clie->oid, &pstyl)) {
        printf("    query drop error!\n");
        return -1;
    }
    //
    return 0x00;
}

int query_conta_find(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_find\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_FIND, &clie->oid, &pstyl)) {
        printf("    query find error!\n");
        return -1;
    }
    //
    return 0x00;
}

int query_conta_invok(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_invok\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_INVOK, &clie->oid, &pstyl)) {
        printf("    query invok error!\n");
        return -1;
    }
    //
    return 0x00;
}

int query_conta_facto(resp_data_t *query_resp, osev_clie *clie, char **paras) {
    printf("query_conta_facto\n");
    printf("paras, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", paras[0x00], paras[0x01], paras[0x02], paras[0x03]);
    osv_pstyl_t pstyl;
    if (-1 == ston_pstyl(&pstyl, paras)) return -1;
    //
    if (clie_query_bzl(query_resp, clie->conne_sock, QUER_FACTO, &clie->oid, &pstyl)) {
        printf("    query facto error!\n");
        return -1;
    }
    //
    return 0x00;
}

// query

