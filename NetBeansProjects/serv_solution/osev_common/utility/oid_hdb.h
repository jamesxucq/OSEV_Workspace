
#ifndef _OID_HDB_H
#define _OID_HDB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "bloom.h"
//
#define OIDHDB_NAME_LENGTH 260

//
#define OIDHDB_KEY_SZ 12
#define OIDHDB_VALUE_SZ 8

//

typedef struct {
    uint8_t cached; /* cached or not */
    char key[OIDHDB_KEY_SZ]; /* key of <key, value> */
    char valu[OIDHDB_VALUE_SZ]; /* value of <key, value> */
    uint32_t hash; /* second hash value */
    uint64_t off; /* offset of the entry */
    uint64_t left; /* offset of the left child */
    uint64_t right; /* offset of the right child */
} OIDH_ENTRY;
#define OIDH_ENTRY_SZ sizeof(OIDH_ENTRY)

//

typedef struct {
    uint64_t off; /* offset of the first entry in the bucket */
} OIDH_BUCKET;
#define OIDH_BUCKET_SZ sizeof(OIDH_BUCKET)

//
#define OIDHDB_MAGIC 19811011

typedef struct {
    uint32_t magi; /* magic number */
    uint32_t cnum; /* number of cache items */
    uint32_t bnum; /* number of hash buckets */
    uint64_t tnum; /* number of total items */
    uint64_t boff; /* offset of bloom filter */
    uint64_t hoff; /* offset of hash buckets */
    uint64_t voff; /* offset of hash values */
} OIDHDB_HDR;
#define OIDHDB_HDR_SZ sizeof(OIDHDB_HDR)

//
typedef uint32_t(*oidhfunc_t)(char *, int);

typedef struct {
    char dbname[OIDHDB_NAME_LENGTH]; /* hashdb filename */
    int fd; /* hashdb fd */
    OIDHDB_HDR header; /* hashdb header */
    BLOOM *bloom; /* bloom filter */
    OIDH_BUCKET *bucket; /* hash buckets */
    OIDH_ENTRY *cache; /* hash item cache */
    oidhfunc_t oidh_func1; /* hash function for hash bucket */
    oidhfunc_t oidh_func2; /* hash function for btree in the hash bucket */
} OIDHDB;

//
OIDHDB *oidhdb_new(uint64_t tnum, uint32_t bnum, uint32_t cnum, oidhfunc_t oidh_func1, oidhfunc_t oidh_func2);
int oidhdb_open(OIDHDB *hdb, const char *path);
int oidhdb_close(OIDHDB *hdb, int flash);
int oidhdb_set(OIDHDB *hdb, char *key, void *valu);
int oidhdb_get(OIDHDB *hdb, char *key, void *valu);
int oidhdb_unlink(OIDHDB *hdb);
#define oidhdb_dele(HDB)     free(HDB)

#ifdef __cplusplus
}
#endif

#endif
