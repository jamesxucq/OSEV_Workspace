
/* 
 * File:   inte_statu.h
 * Author: James Xu
 *
 * Created on 2016.12.29, PM 1:51
 */

#ifndef INTE_STATU_H
#define INTE_STATU_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern char* (**parse_status_tab[])(char *, char **, char *);
    int valid_status();
    
    //
    extern int (*hand_ostatu_tab[])(prod_data *, char **);
    extern int (*hand_dstatu_tab[])(prod_data *, char **);

#ifdef __cplusplus
}
#endif

#endif /* INTE_STATU_H */

