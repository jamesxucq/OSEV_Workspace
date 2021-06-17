
/* 
 * File:   valtok.h
 * Author: James
 *
 * Created on 2019.3.22, 10:19
 */

#ifndef VALTOK_H
#define VALTOK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "exptoke.h"

#define STACK_SIZE 256

#define MAX_TOKE_SIZE 512

    /*
     * && AND || OR ! NOT ( ) < > == != >= <= BETWEEN IN
     */

    /*
     * () (l-r)
     * ! NOT (r-l)
     * < > >= <= (l-r)
     * == != (l-r)
     * BETWEEN IN (l-r)
     * && AND (l-r)
     * || OR (l-r)
     */

    //

    typedef struct valu_toke_t {
        unsigned int vtok_kind;
        long long lolo_valu;
        double doub_valu;
        char stri_valu[MAX_TOKE_SIZE];
    } valu_toke;

    //

#ifdef __cplusplus
}
#endif

#endif /* VALTOK_H */

