
#include "osev_common/commo_header.h"

#include "clie_obje.h"

//
actionmap *_cobje_hm_;
pthread_mutex_t _cobje_mutex_;

void cona_free(void *conta) {
    if (conta) free(conta);
}

//
