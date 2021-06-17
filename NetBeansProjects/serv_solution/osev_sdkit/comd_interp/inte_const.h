
/* 
 * File:   inte_const.h
 * Author: James Xu
 *
 * Created on 2017.6.17., PM1:43
 */

#ifndef INTE_CONST_H
#define INTE_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern char* (*parse_const_tab[])(char *, char **, char *);
    int valid_const();

    //
    extern int (*hand_const_tab[])(prod_data *, void *, osv_oid_t *, char **);

#ifdef __cplusplus
}
#endif

#endif /* INTE_CONST_H */

