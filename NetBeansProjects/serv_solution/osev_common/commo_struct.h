
/* 
 * File:   commo_struct.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 9:47
 */

#ifndef COMMO_STRUCT_H
#define COMMO_STRUCT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

//
    
    typedef struct {
        size_t len;
        char *data;
    } osv_str_t;

#define osv_stri(str)     { sizeof(str) - 0x01, (char *) str }

//
    
#ifdef __cplusplus
}
#endif

#endif /* COMMO_STRUCT_H */

