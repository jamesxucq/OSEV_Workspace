
/* 
 * File:   struti.h
 * Author: James Xu
 *
 * Created on 2017.623, PM 1:53
 */

#ifndef STRUTI_H
#define STRUTI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif
    //


    //
    char *space_delim(char *stri);
    char *find_metho_decla(char *nspac, char *clas_data);
    char *find_metho_defin(char *nspac, char *clas_data);

    //
    char *split_class_conte(char *clas_defin, char *clas_data);

    //
    char *pass_class_conte(char *clas_data);
    int class_conte_type(char *clas_data);


#ifdef __cplusplus
}
#endif

#endif /* STRUTI_H */

