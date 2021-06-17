
/* 
 * File:   opera_utili.h
 * Author: James Xu
 *
 * Created on 2017.4.13, AM10:29
 */

#ifndef OPERA_UTILI_H
#define OPERA_UTILI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int merge_data_oid(FILE *filed, FILE *file1, FILE *file2);
    int cartesi_product_data(FILE *filed, FILE *file1, FILE *file2);
    int shared_data_oid(FILE *filed, FILE *file1, FILE *file2);

#ifdef __cplusplus
}
#endif

#endif /* OPERA_UTILI_H */

