
/* 
 * File:   inte_privi.h
 * Author: James Xu
 *
 * Created on 2018.2.14, PM 2:03
 */

#ifndef INTE_PRIVI_H
#define INTE_PRIVI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern char* (**parse_privile_tab[])(char *, char **, char *);
    int valid_privile();
    
    //
    
    extern int (*hand_oprivi_tab[])(prod_data *, char **);
    extern int (*hand_dprivi_tab[])(prod_data *, char **);


#ifdef __cplusplus
}
#endif

#endif /* INTE_PRIVI_H */

