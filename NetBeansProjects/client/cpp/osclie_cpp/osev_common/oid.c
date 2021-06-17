#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//
#include "commo_macro.h"
#include "osev_atomic.h"
#include "encoding.h"
#include "linux_os.h"

#include "oid.h"

//

//
static osv_atomic_t _object_counter_;

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

//

static unsigned int instance_unique(void) {
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

osv_oid_t *creat_objeid_obj(osv_oid_t *obje_id) {
    obje_id->mach_unique = instance_unique();
    obje_id->time_stamp = 0x00000000FFFFFFFF & time(NULL);
    obje_id->counter = osv_atomic_add_fetch(&_object_counter_, 0x01);
    if (!obje_id->counter) obje_id->counter = osv_atomic_add_fetch(&_object_counter_, 0x01);
    // printf("------- obje_id->counter:%u\n", obje_id->counter);
    return obje_id;
}

//
osv_oid_t *stroid(osv_oid_t *obje_id, char *oid_stri) {
    char *obina = (char *) obje_id;
    char nodchr[0x03];
    //
    nodchr[0x02] = '\0';
    int inde = 0x00;
    for (; inde < OID_BINARY_LEN; inde++) {
        nodchr[0x00] = oid_stri[0x00];
        oid_stri++;
        nodchr[0x01] = oid_stri[0x00];
        oid_stri++;
        obina[0x00] = strtol(nodchr, NULL, 16);
        obina++;
    }
    //
    return obje_id;
}


//

char *oidstr(char *oid_stri, osv_oid_t *obje_id) {
    char *toksp = oid_stri;
    char *obina = (char *) obje_id;
    int inde = 0x00;
    for (; inde < OID_BINARY_LEN; inde++) {
        sprintf(toksp, "%02x", (unsigned char) obina[0x00]);
        toksp += 0x02;
        obina++;
    }
    oid_stri[24] = '\0';
    return oid_stri;
}

char *qoidstr(char *oid_stri, osv_oid_t *obje_id) {
    char *toksp = oid_stri;
    char *obina = (char *) obje_id;
    int inde = 0x00;
    for (; inde < OID_BINARY_LEN; inde++) {
        sprintf(toksp, "%02x", (unsigned char) obina[0x00]);
        toksp += 0x02;
        obina++;
    }
    oid_stri[24] = '\0';
    return oid_stri;
}