
/* 
 * File:   string_utility.h
 * Author: Administrator
 *
 * Created on 2017.9.5
 */

#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_macro.h"

    //

    typedef struct {
        char sin_addr[SERVN_LENGTH];
        int sin_port;
    } serv_addr;

    //
    char *lscpy(char * dest, const char * src);
    char *lccpy(char * dest, const char src);

    //    
    char *strzcpy(char *dest, const char *source, size_t count);

    //
    char *kill_blank(char *stri);
    
    //
#define lmcpy_s(dest, src, len, last) { \
    dest = last; \
    memcpy(last, src, len); \
    last += len; \
}
    
#define lscpy_s(dest, src, last) { \
    dest = last; \
    last = lscpy(last, src); \
    last++; \
}
    
    //
char *quote_decode(char *quostr);
    
    //

#ifdef __cplusplus
}
#endif

#endif /* STRING_UTILITY_H */

