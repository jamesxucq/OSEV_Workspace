
/* 
 * File:   osev_atomic.h
 * Author: Administrator
 *
 * Created on 2017.2.1, PM 2:18
 */

#ifndef OSV_ATOMIC_H
#define OSV_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile unsigned long osv_atomic_t;
#define osv_atomic_add_fetch(value, add) __sync_add_and_fetch(value, add)

#ifdef __cplusplus
}
#endif

#endif /* OSV_ATOMIC_H */

