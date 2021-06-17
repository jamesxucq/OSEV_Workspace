
#ifndef REQU_CONNE
#define REQU_CONNE

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_macro.h"
#include "oid.h"
#include "ostproto.h"

    //
#pragma pack(1)

    typedef struct {
        OSEV_METHOD method;
        uint64 length;
    } requ_tyle_t;
#pragma pack()

    // request

#define CAT_REQU_STR(REQU, HEAD) \
    (REQU).requ_len = sizeof(requ_tyle_t) + ((requ_tyle_t*)HEAD)->length;

#define CAT_METHO_PTR(HEAD, METHOD, LENG) \
    (HEAD)->requ_head.method = METHOD; \
    (HEAD)->requ_head.length = LENG;

    // AUTHEN

#pragma pack(1)

    struct authe_ine {
        char user_name[USERN_LENGTH];
        char req_valid[PASSWORD_LENGTH];
    };
#pragma pack()
    //
#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        struct authe_ine authe;
        char requ_data[0x00]; // param
    } auth_requ_t;
#pragma pack()

    // KALIVE

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        osv_oid_t oid;
    } kalive_requ_t;
#pragma pack()

    // STATUS

    enum statu_type {
        STAT_ECHO,
        STAT_OPEN, // start create
        STAT_CLOSE, // shutdown
        STAT_STATUS,
        STAT_ADDIU,
        STAT_DELEU,
        STAT_PRIVILE,
    };
    //
#pragma pack(1)

    struct statu_ine {
        osv_oid_t oid; // osev or osdb name
        enum statu_type statyp; // 0x00:create | 0x01:open | 0x02:close | 0x03:delete | 0x04:info
    };
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        struct statu_ine statu;
        char requ_data[0x00]; // param
    } statu_requ_t;
#pragma pack()

    // INVOK METHOD

    enum nspac_type {
        NSPA_TYPE_METHO,
        NSPA_TYPE_CLASS
    };

    enum invok_type {
        INVO_ECHO,
        INVO_CREAT,
        INVO_REPLA,
        INVO_DROP,
        INVO_INTEGRI,
        INVO_RELOAD
    };

#pragma pack(1)

    struct invok_ine {
        osv_oid_t oid;
        enum nspac_type nsptyp;
        enum invok_type invtyp; // 
    };
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        struct invok_ine invok;
        char requ_data[0x00]; // param
    } invok_requ_t;
#pragma pack()

    // CONST METHOD

    enum const_type {
        CONS_ECHO,
        CONS_CREAT,
        CONS_DROP,
        CONS_UPDAT,
        CONS_INSER,
        CONS_FIND,
        CONS_INVOK,
    };
    //
#pragma pack(1)

    struct const_ine {
        osv_oid_t oid;
        enum const_type constyp; // 
    };
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        struct const_ine constr;
        char requ_data[0x00]; // param
    } const_requ_t;

#pragma pack()

    // QUERY METHOD

    enum query_type {
        QUER_ECHO,
        QUER_CREAT,
        QUER_DROP,
        QUER_FIND,
        QUER_INVOK,
        QUER_FACTO
    };
    //
#pragma pack(1)

    struct query_ine {
        osv_oid_t oid;
        enum query_type quertyp; // 
    };
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        struct query_ine query;
        char requ_data[0x00]; // param
    } query_requ_t;

#pragma pack()

    // DONE

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        osv_oid_t oid;
    } done_requ_t;
#pragma pack()

    //

#ifdef __cplusplus
}
#endif

#endif /* REQU_CONNE */

