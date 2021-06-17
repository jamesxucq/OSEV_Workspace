
#include <string.h>
#include "astri_utili.h"

// "osdb:contain"

uint32 split_conta(char *osdb, char *conta, char *osdb_conta) {
    char *toke;
    if ((toke = strchr(osdb_conta, ':'))) {
        toke[0x00] = '\0';
        strcpy(osdb, osdb_conta);
        strcpy(conta, ++toke);
    } else return -1;
    //
    return 0x00;
}