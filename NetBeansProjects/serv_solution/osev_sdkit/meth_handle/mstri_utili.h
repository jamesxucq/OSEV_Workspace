
/* 
 * File:   mstri_utili.h
 * Author: James Xu
 *
 * Created on 2017.1.8, PM 2:59
 */

#ifndef MSTRI_UTILI_H
#define MSTRI_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

//
#define BUILD_HANDLE_NAME(HANDN, CLASN, MEPAN) { \
    char *last_str = lscpy(HANDN, CLASN); \
    last_str = lccpy(last_str, '_'); \
    lscpy(last_str, MEPAN); }

#define BUILD_OBJECT_NAME(OBJE_NAME, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(OBJE_NAME, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

#ifdef __cplusplus
}
#endif

#endif /* MSTRI_UTILI_H */

