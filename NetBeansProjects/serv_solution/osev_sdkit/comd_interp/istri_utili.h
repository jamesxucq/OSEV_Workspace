
/* 
 * File:   istri_utili.h
 * Author: James Xu
 *
 * Created on 2016.12.31, AM 9:26
 */

#ifndef ISTRI_UTILI_H
#define ISTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    //
    char *decode_const_invok(char *data_line, char **paras, char *requ_data, int req_len);
    char *decode_invok_list(char *data_line, char **paras, char *requ_data, int req_len);

    //

    
    //

#ifdef __cplusplus
}
#endif

#endif /* ISTRI_UTILI_H */

