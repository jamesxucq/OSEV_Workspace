#include "commo_macro.h"
#include "checksum.h"
#include "stri_utili.h"
#include "hash_table_ex.h"

//
unsigned int none_hash(void *src) {
    return 0;
}

int equal_md5(void *k1, void *k2) {
    return (0 == strncmp((char *) k1, (char *) k2, MD5_DIGEST_LEN));
}

unsigned int lh_strhash(void *src) {
    int i, l;
    unsigned long ret = 0;
    unsigned short *s;
    char *str = (char *) src;
    if (NULL == str) return (0);
    l = (strlen(str) + 1) / 2;
    s = (unsigned short *) str;

    for (i = 0; i < l; i++)
        ret ^= s[i] << (i & 0x0f);
    //
    return (ret);
}

int equal_str(void *k1, void *k2) {
    return (0 == strcmp((char *) k1, (char *) k2));
}

unsigned int lh_oidhash(void *oid) {
    int i, l;
    unsigned long ret = 0;
    unsigned short *s;
    char *str = (char *) oid;
    if (NULL == str) return (0);
    l = (sizeof(osv_oid_t) + 1) / 2;
    s = (unsigned short *) str;

    for (i = 0; i < l; i++)
        ret ^= s[i] << (i & 0x0f);
    //
    return (ret);
}

int equal_oid(void *k1, void *k2) {
    return (0 == strncmp((char *) k1, (char *) k2, sizeof(osv_oid_t)));
}

//

char *creat_action_key(char *action_key, char *user_name, char *osev_osdb) {
    char *last_str = lscpy(action_key, user_name);
    last_str = lccpy(last_str, ':');
    lscpy(last_str, osev_osdb);
    //
    return action_key;
}