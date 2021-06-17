#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "commo_macro.h"
#include "osev_macro.h"
#include "linux_os.h"
#include "osev_atomic.h"
#include "encoding.h"
#include "oid.h"

//
static osv_atomic_t _object_counter_;

//
osv_oid_t INVA_OID_VALU = {
    INVA_UINT_VALU, INVA_UINT_VALU, INVA_UINT_VALU
};

//
// seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

void hash_combine(size_t *inst_seed, char *stri) {
    size_t seed;
    int slen = strlen(stri);
    unsigned int valu;
    int inde;
    for (inde = 0; inde < slen; inde += sizeof (unsigned int)) {
        memcpy(&valu, stri + inde, sizeof (unsigned int));
        seed ^= valu + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    *inst_seed = seed;
}

// instan_unique
unsigned int instan_unique(void) {
    static unsigned int gen_machine;
    if (gen_machine) return gen_machine;
    //
    char netw_info[TEXT_LENGTH];
    MKZERO(netw_info);
    if (network_info(netw_info)) random_salt(netw_info);
    size_t machine_piece;
    hash_combine(&machine_piece, netw_info);
    //
    pid_t process_piece = getpid();
    gen_machine = machine_piece | process_piece;
    if (!gen_machine) gen_machine = 0x9e3779b9;
    //
    return gen_machine;
}

//


//

osv_oid_t *creat_objeid_osev(osv_oid_t *osev_oid) {
    osev_oid->osev_unique = instan_unique();
    ((osv_oid_i *) osev_oid)->stoid = 0x00;
    return osev_oid;
}

//

osv_oid_t *creat_objeid_osdb(osv_oid_t *osdb_oid) {
    osdb_oid->osev_unique = instan_unique();
    ((osv_oid_i *) osdb_oid)->stoid = 0xFFFFFFFFFFFFFFFF;
    return osdb_oid;
}

//

osv_oid_t *creat_objeid_cla(osv_oid_t *clas_oid) {
    clas_oid->osev_unique = instan_unique();
    clas_oid->time_stamp = 0x00000000FFFFFFFF & time(NULL);
    clas_oid->counter = 0x00;
    return clas_oid;
}

osv_oid_t *creat_objeid_obj(osv_oid_t *obje_oid) {
    obje_oid->osev_unique = instan_unique();
    obje_oid->time_stamp = 0x00000000FFFFFFFF & time(NULL);
    obje_oid->counter = osv_atomic_add_fetch(&_object_counter_, 0x01);
    if (!obje_oid->counter) obje_oid->counter = osv_atomic_add_fetch(&_object_counter_, 0x01);
    // printf("------- obje_oid->counter:%u\n", obje_oid->counter);
    return obje_oid;
}

//

osv_oid_t *stroid(osv_oid_t *obje_oid, char *oid_stri) {
    char *tokst = (char *) obje_oid;
    char nodchr[0x03];
    //
    nodchr[0x02] = '\0';
    int inde = 0x00;
    for (; inde < OID_BINARY_LEN; inde++) {
        nodchr[0x00] = oid_stri[0x00];
        oid_stri++;
        nodchr[0x01] = oid_stri[0x00];
        oid_stri++;
        tokst[0x00] = strtol(nodchr, NULL, 16);
        tokst++;
    }
    //
    return obje_oid;
}


//

char *oidstr(char *oid_stri, osv_oid_t *obje_oid) {
    char *toksp = oid_stri;
    char *tokst = (char *) obje_oid;
    int inde = 0x00;
    for (; inde < OID_BINARY_LEN; inde++) {
        sprintf(toksp, "%02x", (unsigned char) tokst[0x00]);
        toksp += 0x02;
        tokst++;
    }
    oid_stri[24] = '\0';
    return oid_stri;
}

//

osv_oid_t *strsid_oid(osv_oid_t *obje_oid, char *sid_stri) {
    char *tokst = (char *) &((osv_oid_i *) obje_oid)->stoid;
    char nodchr[0x03];
    //
    ((osv_oid_i *) obje_oid)->osev_unique = instan_unique();
    //
    nodchr[0x02] = '\0';
    int inde = 0x00;
    for (; inde < SID_BINARY_LEN; inde++) {
        nodchr[0x00] = sid_stri[0x00];
        sid_stri++;
        nodchr[0x01] = sid_stri[0x00];
        sid_stri++;
        tokst[0x00] = strtol(nodchr, NULL, 16);
        tokst++;
    }
    //
    return obje_oid;
}

char *oid_sidstr(char *sid_stri, osv_oid_t *obje_oid) {
    char *toksp = sid_stri;
    char *tokst = (char *) &((osv_oid_i *) obje_oid)->stoid;
    int inde = 0x00;
    for (; inde < SID_BINARY_LEN; inde++) {
        sprintf(toksp, "%02x", (unsigned char) tokst[0x00]);
        toksp += 0x02;
        tokst++;
    }
    sid_stri[16] = '\0';
    return sid_stri;
    //
}

