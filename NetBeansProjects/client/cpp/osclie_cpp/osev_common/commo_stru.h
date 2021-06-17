
/* 
 * File:   commo_macro.h
 * Author: Administrator
 *
 * Created on 2017.6.22, PM 2:09
 */

#ifndef COMMO_STRU_H
#define COMMO_STRU_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        size_t len;
        char *data;
    } osv_str_t;

#define osv_stri(str)     { sizeof(str) - 0x01, (char *) str }


#ifdef __cplusplus
}
#endif

#endif /* COMMO_STRU_H */

