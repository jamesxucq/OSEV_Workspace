
/* 
 * File:   osev_struct.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 3:14
 */

#ifndef OSEV_STRUCT_H
#define OSEV_STRUCT_H

#include "hash_table_ex.h"
#include "commo_macro.h"
#include "osev_macro.h"
#include "rive_bzl.h"
#include "oid.h"
#include "ostproto.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    typedef struct {
        char osev_osdb[OSEV_LENGTH];
        osv_oid_t oid;
        //
        char auth_valid[PLAIN_VALID_LENGTH];
        void *use_privi; // NULL:no auth privile
        char _action_key_[ACTION_KEY_LENGTH];
        unsigned int _refer_inde_; // reference
    } list_data;

    //

    typedef struct {
        uint64 content_length;
        osv_oid_t oid;
        char data_line[LARGE_TEXT_SIZE];
        char *paras[PARAM_NUMB];
        //
        unsigned int sentry;
        unsigned int svalue;
    } inte_value;

    //

    typedef struct {
        uchar status_code; // STATUS_CODE 
        FILE *requ_data;
        FILE *resp_data;
        uint64 rwrite_tatol;
        // must end in struct, see BZERO_SCTRL
        BYTE recv_buffer[RSBUF_LENGTH];
        BYTE send_buffer[RSBUF_LENGTH];
    } seion_ctrl;

    //

    typedef struct {
        struct dyli_hand *dyha_list;
        actionmap *ocuse_hm;
    } hand_data;

    typedef struct {
        actionmap *contn_hm; // container name map
        cachemap *conto_hm; // container object id map
    } cont_data;

    typedef struct {
        char osdb_name[OSDB_LENGTH]; // odb name
        osv_oid_t oid; // odb object id
        uint32 leve_mask; // running level
        rive_conne rvcon[ENGINE_COUNT]; // storage handle
        hand_data handa; // object data
        hand_data hando; // object method
        cont_data conda; // container
    } conoda;

    //

    typedef struct {
        list_data *ldata;
        conoda *coval;
        inte_value inval;
        seion_ctrl sctrl;
    } session;

    //

    typedef struct {
        uint64 *colen;
        FILE *sedat;
        BYTE *sebuf;
    } prod_data;

    //
#define PDAT_NONE_TAIL(prod) \
        (prod->colen)[0x00] = 0x00;

#define PDAT_EXCEP_TAIL(prod, execep_code) \
        ((unsigned int *) prod->sebuf)[0x00] = execep_code; \
        (prod->colen)[0x00] = EXCEP_LENG;

#define FDAT_EXCEP_TAIL(prod, execep_code) \
        ((unsigned int *) prod->sebuf)[0x00] = execep_code; \
        fwrite(prod->sebuf, EXCEP_LENG, 0x01, prod->sedat); \
        rewind(sresp->sedat); \
        (prod->colen)[0x00] = EXCEP_LENG;

#define PDAT_EXCEP_HEAD(prod, execep_code) \
        inser_head((char *)prod->sebuf, (int)prod->colen[0x00] + 0x01, EXCEP_LENG); \
        ((unsigned int *) prod->sebuf)[0x00] = execep_code; \
        (prod->colen)[0x00] += EXCEP_LENG;

    //

#ifdef __cplusplus
}
#endif

#endif /* OSEV_STRUCT_H */

