
#ifndef CLIE_OBJE_H
#define CLIE_OBJE_H

#include"osev_clie.h"
#include "stri_utili.h"
#include"clie_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern osev_clie *_shell_clie_;
    extern int _conne_type_;
    extern svod_auth _clie_auth_;

    //
#define NULL_CONNE -1
#define OSEV_CONNE 0x00
#define OSDB_CONNE 0x01
    int get_conne_type(char *conne_str);
    //
    char *get_osev_osdb(char *osev_osdb);

    //
    osev_clie *conne_osdb_noau(osev_clie *clie, char *osdb);
    osev_clie *conne_osdb_auth(osev_clie *clie, char *osdb, char *name, char *paswd);

    //
#define CACHE_BACKET_SIZE      512
    extern actionmap *_colle_cache_hm_;
    extern pthread_mutex_t _colle_cache_mutex_;

    extern actionmap *_conta_cache_hm_;
    extern pthread_mutex_t _conta_cache_mutex_;
    void cache_free(void *data);
    // 
#define reset_cache(cache_hm) action_clear(cache_hm)
    osv_oid_t *find_conta(actionmap *cobje_hm, char *conta, osev_clie *clie);
    void erase_conta(actionmap *cobje_hm, char *conta, unsigned int quer_valu);
    //
    osv_oid_t *find_osdb(actionmap *cobje_hm, char *osdb, osev_clie *clie);
    void erase_osdb(actionmap *cobje_hm, char *osdb, char *obje_iden, unsigned int stat_valu);

    //
    osv_oid_t *find_colle(actionmap *cobje_hm, char *colle, osev_clie *clie);
    void erase_colle(actionmap *cobje_hm, char *colle, unsigned int coll_valu);

    //

    typedef struct {
        osv_oid_t obje_oid;
        char obje_iden[OBJE_LENGTH];
        int changed; // 0x00: not change, 0x01: changed 
    } obje_valu;

    //
    extern obje_valu _leve_defa_obje_;
    extern shel_stat_t _last_shel_stat_;

#ifdef __cplusplus
}
#endif

#endif /* CLIE_OBJE_H */

