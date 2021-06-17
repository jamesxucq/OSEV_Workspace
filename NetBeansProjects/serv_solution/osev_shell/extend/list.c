#include <pthread.h>

#include "commo_header.h"

#include "struti.h"
#include "../clie_obje.h"
#include "./parse_echo/epcla.h"
#include "struti.h"
#include "list.h"

//
#define INVO_LIST_OBJID "OBJID"
#define INVO_LIST_ATTRIB "ATTRIB"
#define INVO_LIST_CONTEN "CONTENT"

//

static int list_meth_conte(char *meth_conte, osv_oid_t *oid, char *metnm) {
    char *paras[0x03] = {NULL, INVO_LIST_CONTEN, NULL};
    paras[0x00] = metnm;
    resp_data_t onel_resp;
    // printf("list_meth_conte\n");
    if (-1 == obje_invok_list(&onel_resp, _shell_clie_, oid, paras)) return -1; // disable by james 20210413
    memcpy(meth_conte, onel_resp.res_data, onel_resp.resp_len);
    meth_conte[onel_resp.resp_len] = '\0';
    //
    return onel_resp.resp_len;
}

static int list_clas_attri(char *clas_conte, char *clasn) {
    char *paras[0x03] = {NULL, INVO_LIST_ATTRIB, NULL};
    paras[0x00] = clasn;
    resp_data_t twol_valu;
    //
    if (-1 == obje_colle_list(&twol_valu, _shell_clie_, paras)) return -1;
    memcpy(clas_conte, twol_valu.res_data, twol_valu.resp_len);
    clas_conte[twol_valu.resp_len] = '\0';
    //
    return twol_valu.resp_len;
}

static int list_clas_conte(char *clas_conte, char *clasn) {
    char *paras[0x03] = {NULL, INVO_LIST_CONTEN, NULL};
    paras[0x00] = clasn;
    resp_data_t twol_valu;
    //
    if (-1 == obje_colle_list(&twol_valu, _shell_clie_, paras)) return -1;
    memcpy(clas_conte, twol_valu.res_data, twol_valu.resp_len);
    clas_conte[twol_valu.resp_len] = '\0';
    //
    return twol_valu.resp_len;
}

//

static int parse_class_conte(char *clas_defin, char *meth_line, char *metnm[METH_NUMB], char *clas_conte) {
    // printf("clas_conte:|%s|\n", clas_conte);
    char *last_str = split_class_conte(clas_defin, clas_conte);
    if (!last_str) return -1;
    lccat(clas_defin, '\n');
    // printf("clas_defin:|%s|\n", clas_defin);
    // printf("last_str:|%s|\n", last_str);
    parse_method(meth_line, metnm, last_str);
    return 0x00;
}

static osv_oid_t *get_colle_oid(char *clasn) {
    pthread_mutex_lock(&_colle_cache_mutex_);
    osv_oid_t *obje_oid = find_colle(_colle_cache_hm_, clasn, _shell_clie_);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    //
    return obje_oid;
}

// 0x00:OK -1:error

int hand_list(char **parae, shel_resu *resu) {
    uint64 colen = 0x00;
    ssize_t wlen;
    //
    unsigned int itype = invo_list_type(parae[0x01]);
    if (LIST_CLAS_ATTRIB & itype) {
        char clas_attri[TEXT_LENGTH];
        //
        quote_decode(parae[0x00]);
        if (-1 == list_clas_attri(clas_attri, parae[0x00])) return -1;
        if (-1 == (wlen = APPEND_DATAD(resu->res_fde, clas_attri, strlen(clas_attri)))) return -1;
        colen += wlen;
        // printf("clas_attri:|%s|\n", clas_attri);
    }
    //
    if (LIST_CLAS_CONTEN & itype) {
        char clas_decla[LARGE_TEXT_SIZE];
        char meth_line[LARGE_TEXT_SIZE];
        char *metnm[METH_NUMB];
        //
        quote_decode(parae[0x00]);
        if (-1 == list_clas_conte(clas_decla, parae[0x00])) return -1;
        printf("clas_decla:|%s|\n", clas_decla);
        char clas_defin[LARGE_TEXT_SIZE];
        if (parse_class_conte(clas_defin, meth_line, metnm, clas_decla)) return -1;
        if (-1 == (wlen = APPEND_DATAD(resu->res_fde, clas_defin, strlen(clas_defin)))) return -1;
        colen += wlen;
        printf("clas_defin:|%s|\n", clas_defin);
        osv_oid_t *coid = get_colle_oid(parae[0x00]);
        int inde = 0x00;
        char meth_conte[LARGE_TEXT_SIZE];
        for (; metnm[inde]; inde++) {
            printf("metnm[%d]:|%s|\n", inde, metnm[inde]);
            if (-1 == (wlen = list_meth_conte(meth_conte, coid, metnm[inde]))) return -1;
            if (-1 == (wlen = APPEND_DATAD(resu->res_fde, meth_conte, wlen))) return -1;
            colen += wlen;
            printf("meth_conte:|%s|\n", meth_conte);
        }
    }
    //
    resu->res_len = colen;
    resu->resu_type = 0x01;
    printf("hand_list, resu->res_len:%llu\n", resu->res_len);
    return 0x00;
}
