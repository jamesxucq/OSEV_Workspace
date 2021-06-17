
#ifndef REQU_CONNE
#define REQU_CONNE

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_macro.h"
#include "osev_macro.h"
#include "oid.h"
#include "ostproto.h"

    //
#pragma pack(1)

    typedef struct {
        uchar method; // OSEV_METHOD
        uint32 length;
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
        char req_valid[PASWD_LENGTH];
        char salt[SALT_LENGTH];
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
    // statu_type
#define STAT_ECHO       0x00
#define STAT_OPEN       0x01 // start create
#define STAT_CLOSE      0x02 // shutdown
#define STAT_STATUS     0x03
#define STAT_STATI      0x04
    //
#pragma pack(1)

    typedef struct {
        osv_oid_t oid; // osev or osdb name
        uchar statyp; // statu_type 0x00:create | 0x01:open | 0x02:close | 0x03:delete | 0x04:info
    } statu_ine;
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        statu_ine statu;
        char requ_data[0x00]; // param
    } statu_requ_t;
#pragma pack()

    // PRIVILE
    // privile_type
#define PRIV_ECHO       0x00
#define PRIV_ROLE       0x01
#define PRIV_USER       0x02
    //
#pragma pack(1)

    typedef struct {
        osv_oid_t oid; // osev or osdb name
        uchar privtyp; // privile_type 0x00:create | 0x01:open | 0x02:close | 0x03:delete | 0x04:info
    } privi_ine;
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        privi_ine privi;
        char requ_data[0x00]; // param
    } privi_requ_t;
#pragma pack()

    // INVOK METHOD
    // invok_type
#define INVO_LIST       0x00
#define INVO_CREAT      0x01
#define INVO_REPLA      0x02
#define INVO_DROP       0x03
#define INVO_INTEGRI    0x04
#define INVO_RELOAD     0x05

#pragma pack(1)

    typedef struct {
        osv_oid_t oid;
        uchar invotyp; // invok_type
    } invok_ine;
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        invok_ine invok;
        char requ_data[0x00]; // param
    } invok_requ_t;
#pragma pack()

    // COLLE METHOD
    // colle_type
#define COLE_LIST       0x00
#define COLE_CREAT      0x01
#define COLE_REPLA      0x02
#define COLE_DROP       0x03
#define COLE_INTEGRI    0x04
#define COLE_RELOAD     0x05

#pragma pack(1)

    typedef struct {
        osv_oid_t oid;
        uchar coletyp; // colle_type
    } colle_ine;
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        colle_ine invok;
        char requ_data[0x00]; // param
    } colle_requ_t;
#pragma pack()
    
    // CONST METHOD
    // const_type
#define CONS_ECHO   0x00
#define CONS_CREAT  0x01
#define CONS_DROP   0x02
#define CONS_UPDAT  0x03
#define CONS_INSER  0x04
#define CONS_FIND   0x05
#define CONS_INVOK  0x06
    //
#pragma pack(1)

    typedef struct {
        osv_oid_t oid;
        uchar constyp; // const_type
    } const_ine;
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        const_ine constr;
        char requ_data[0x00]; // param
    } const_requ_t;

#pragma pack()

    // QUERY METHOD
    // query_type
#define QUER_ECHO   0x00
#define QUER_CREAT  0x01
#define QUER_DROP   0x02
#define QUER_UPDAT  0x03
#define QUER_INSER  0x04
#define QUER_FIND   0x05
#define QUER_INVOK  0x06
#define QUER_FACTO  0x07
    //
#pragma pack(1)

    typedef struct {
        osv_oid_t oid;
        uchar quertyp; // query_type
    } query_ine;
#pragma pack()

#pragma pack(1)

    typedef struct {
        requ_tyle_t requ_head;
        query_ine query;
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

