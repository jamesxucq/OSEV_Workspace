
/* 
 * File:   inte_invok.h
 * Author: James Xu
 *
 * Created on 2016.12.29, PM 1:51
 */

#ifndef INTE_INVOK_H
#define INTE_INVOK_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    //
    //    char* (**parse_invoke_tab[])(char *, char **, char *);
    extern char* (*parse_invok_tab[])(char *, char **, char *);
    int valid_invoke();

    //
    extern int (*hand_invok_tab[])(prod_data *, hand_data *, hand_data *, char *, char **);


#ifdef __cplusplus
}
#endif

#endif /* INTE_INVOK_H */

