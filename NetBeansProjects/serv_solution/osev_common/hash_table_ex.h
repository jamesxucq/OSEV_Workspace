#ifndef HASH_TABLE_EXT_H
#define HASH_TABLE_EXT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "utility/hash_table.h"
#include "utility/hash_map.h"
#include "utility/cache_hmap.h"
#include "utility/action_hmap.h"
#include "oid.h"

#define MATCH_BACKET_SIZE     0x80000  // 512K
    
#define create_lh_ht(BACKET_SIZE)                      hash_create(lh_strhash, equal_str, BACKET_SIZE)
#define create_none_ht(BACKET_SIZE)                    hash_create(none_hash, equal_md5, BACKET_SIZE)
#define create_hashmap(FREE_FUNC, BACKET_SIZE)         hashm_create(FREE_FUNC, BACKET_SIZE)
#define create_cache(BACKET_SIZE)                      cache_create(lh_strhash, equal_str, BACKET_SIZE)
#define creat_oid_hm(BACKET_SIZE)                      cache_create(lh_oidhash, equal_oid, BACKET_SIZE)
#define create_action(FREE_FUNC, BACKET_SIZE)          action_create(lh_strhash, equal_str, FREE_FUNC, BACKET_SIZE)

inline unsigned int none_hash(void *src);
int equal_md5(void *k1, void *k2);
unsigned int lh_strhash(void *src);
int equal_str(void *k1, void *k2);
unsigned int lh_oidhash(void *oid);
int equal_oid(void *k1, void *k2);

//
char *creat_action_key(char *action_key, char *user_name, char *osev_osdb);

#ifdef	__cplusplus
}
#endif

#endif /* HASH_TABLE_EXT_H */