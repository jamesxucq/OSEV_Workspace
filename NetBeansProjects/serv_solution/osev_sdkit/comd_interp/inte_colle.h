
/* 
 * File:   inte_colle.h
 * Author: james
 *
 * Created on 2021.5.8, AM 10:42
 */

#ifndef INTE_COLLE_H
#define INTE_COLLE_H

#ifdef __cplusplus
extern "C" {
#endif

    extern char* (*parse_colle_tab[])(char *, char **, char *);
    extern int (*hand_colle_tab[])(prod_data *, hand_data *, hand_data *, char *, char **);


#ifdef __cplusplus
}
#endif

#endif /* INTE_COLLE_H */

