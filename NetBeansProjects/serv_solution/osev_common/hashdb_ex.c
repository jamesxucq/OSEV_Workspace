#include "hashdb_ex.h"


//

uint32_t sax_hash(char *key, int ksiz) {
    uint32_t hav = 0x00;
    while (ksiz--) hav ^= (hav << 5)+(hav >> 2) + (unsigned char) *key++;
    return hav;
}

//

uint32_t sdbm_hash(char *key, int ksiz) {
    uint32_t hav = 0x00;
    while (ksiz--) hav = (unsigned char) *key++ + (hav << 6) + (hav << 16) - hav;
    return hav;
}

//

HASHDB *creat_temp_hadb() {
    char hdbn[HASHDB_NAME_LENGTH] = {"/tmp/hashdb.XXXXXX"};
    //    
    HASHDB *hadb = hashdb_new(HASHDB_DEFAULT_TNUM, HASHDB_DEFAULT_BNUM, HASHDB_DEFAULT_CNUM, sax_hash, sdbm_hash);
    if (!hadb) return NULL;
    if (!mktemp(hdbn)) {
        hashdb_dele(hadb);
        return NULL;
    }
    if (hashdb_open(hadb, hdbn)) {
        hashdb_dele(hadb);
        return NULL;
    }
    hashdb_unlink(hadb);
    //
    return hadb;
}

//

TEXHDB *creat_temp_thdb() {
    char hdbn[TEXHDB_NAME_LENGTH] = {"/tmp/texhdb.XXXXXX"};
    //   
    TEXHDB *thdb = texhdb_new(HASHDB_DEFAULT_TNUM, HASHDB_DEFAULT_BNUM, HASHDB_DEFAULT_CNUM, sax_hash, sdbm_hash);
    if (!thdb) return NULL;
    if (!mktemp(hdbn)) {
        texhdb_dele(thdb);
        return NULL;
    }
    if (texhdb_open(thdb, hdbn)) {
        texhdb_dele(thdb);
        return NULL;
    }
    texhdb_unlink(thdb);
    //
    return thdb;
}

//

OIDHDB *creat_temp_ohdb() {
    char hdbn[OIDHDB_NAME_LENGTH] = {"/tmp/oidhdb.XXXXXX"};
    //   
    OIDHDB *ohdb = oidhdb_new(HASHDB_DEFAULT_TNUM, HASHDB_DEFAULT_BNUM, HASHDB_DEFAULT_CNUM, sax_hash, sdbm_hash);
    if (!ohdb) return NULL;
    if (!mktemp(hdbn)) {
        oidhdb_dele(ohdb);
        return NULL;
    }
    if (oidhdb_open(ohdb, hdbn)) {
        oidhdb_dele(ohdb);
        return NULL;
    }
    oidhdb_unlink(ohdb);
    //
    return ohdb;
}