
/* 
 * File:   inte_query.h
 * Author: James Xu
 *
 * Created on 2016.12.29, PM 1:51
 */

#ifndef INTE_QUERY_H
#define INTE_QUERY_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // contain
    //
    extern char* (*parse_query_tab[])(char *, char **, char *);
    int valid_query();

    //
    extern int (*hand_query_tab[])(prod_data *, void *, char **);
    
    //

#ifdef __cplusplus
}
#endif

#endif /* INTE_QUERY_H */

