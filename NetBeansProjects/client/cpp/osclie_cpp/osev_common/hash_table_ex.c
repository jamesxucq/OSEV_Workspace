
#include <string.h>

#include "hash_table_ex.h"

//

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

//
