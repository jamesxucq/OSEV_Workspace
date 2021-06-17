
/* 
 * File:   conv_utili.h
 * Author: James Xu
 *
 * Created on 2017.6.23, PM 3:23
 */

#ifndef CONV_UTILI_H
#define CONV_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int conv_ointe_data(char ointe_data[PARAM_NUMB][PARAM_LENGTH], char *meth_ointe);
    int conv_clas_decl(char clas_data[CDATNO_NUMB][PARAM_LENGTH]);
    int conv_clas_cons(char clas_data[CDATNO_NUMB][PARAM_LENGTH]);
//    char *conv_decla(char *data, char *node_str);
    
    //
    int conv_ointe_type(char *param_type, char *meth_txt);
    
    //
    char *conv_decla(char *data, char *conte);

#ifdef __cplusplus
}
#endif

#endif /* CONV_UTILI_H */

