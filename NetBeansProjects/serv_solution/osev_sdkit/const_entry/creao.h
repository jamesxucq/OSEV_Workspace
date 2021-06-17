
/* 
 * File:   creao.h
 * Author: James Xu
 *
 * Created on 2017.3.20, PM3:24
 */

#ifndef CREAO_H
#define CREAO_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // -1:error 0x00:ok 0x01:exception
    int creat_entity_obje(riv_curso_t *curso, rive_ha *stora_ha, hand_data *hando, char *clasn, char **paras);
    int creat_eobje_echo(hand_data *hando, char *clasn, char **paras);


#ifdef __cplusplus
}
#endif

#endif /* CREAO_H */

