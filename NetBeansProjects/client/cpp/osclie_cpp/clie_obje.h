
/* 
 * File:   clie_obje.h
 * Author: Administrator
 *
 * Created on 2017.9.7
 */

#ifndef CLIE_OBJE_H
#define CLIE_OBJE_H

#ifdef __cplusplus
extern "C" {
#endif

//
#define CONTA_BACKET_SIZE      512
    extern actionmap *_cobje_hm_;
    extern pthread_mutex_t _cobje_mutex_;
    void cona_free(void *conta);

#ifdef __cplusplus
}
#endif

#endif /* CLIE_OBJE_H */

