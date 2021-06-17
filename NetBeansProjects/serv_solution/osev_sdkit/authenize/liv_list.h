
/* 
 * File:   liv_list.h
 * Author: Administrator
 *
 * Created on 2018.3.30, AM 10:12
 */

#ifndef LIV_LIST_H
#define LIV_LIST_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    // user<[uid int, uname char[32], salt char[16], password char[32], roleId int[32]] INVISI>;
    // userContain
#define MAX_PRIVI_SIZE   64
#define MAX_ROLE_SIZE  8

    // authen
#pragma pack(1)

    typedef struct {
        osv_oid_t oid;
        uint32 privile_mask; // privilege
    } dist_privi;
#pragma pack()
    extern dist_privi INVA_PRIV_VALU;
    extern dist_privi ZERO_PRIV_VALU;

    // container
#define ROLE_TYPE_OSEV 0x00
#define ROLE_TYPE_OSDB 0x01
#pragma pack(1)

    typedef struct {
        osv_oid_t oid;
        char role_type; // 0x00:osev 0x01:data
        char role_name[USERN_LENGTH];
        dist_privi priv_array[MAX_PRIVI_SIZE];
    } role_privi;
#pragma pack()
    // container
#pragma pack(1)

    typedef struct {
        osv_oid_t oid;
        char user_name[USERN_LENGTH];
        char password[PASWD_LENGTH];
        char salt[SALT_LENGTH];

        union {
            osv_oid_t role_oid[MAX_ROLE_SIZE];
            role_privi *role_poin[MAX_ROLE_SIZE];
        };
    } user_privi;
#pragma pack()
    //

    struct liv_list {
        struct liv_list *next;
        void *liv_data;
    };

    //
    struct liv_list *appe_live_list(struct liv_list **llsth, void *liv_data, int liv_len);
    struct liv_list *addi_live_list(struct liv_list **llsth, int liv_len);
    void dele_live_list(struct liv_list *llist);
#define DELE_LIVE_LIST(LLIST) dele_live_list(LLIST); LLIST = NULL;
    void dele_livlst(struct liv_list **llsth, struct liv_list *llist);
    void dele_livdat(struct liv_list **llsth, void *ldata);
    //

    struct priv_list {
        struct liv_list *role_list;
        struct liv_list *ouse_list;
        struct liv_list *cuse_list;
    };

    //

#ifdef __cplusplus
}
#endif

#endif /* LIV_LIST_H */

