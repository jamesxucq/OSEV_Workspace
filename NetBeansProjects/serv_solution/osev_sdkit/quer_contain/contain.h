/* 
 * File:   contain.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 3:00
 */

#ifndef CONTAIN_H
#define CONTAIN_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    contain *creat_conta_obje(char *osdb, char *cont_name, unsigned int stora_type);
    int qload_conta_obje(struct cono_list *clist);

    //
    int conve_conta_types(char *forma_types, char clas_data[CDATNO_NUMB][PARAM_LENGTH]);

#ifdef __cplusplus
}
#endif

#endif /* CONTAIN_H */

