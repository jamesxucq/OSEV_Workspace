
/* 
 * File:   compa_utili.h
 * Author: james
 *
 * Created on 2021.4.1, PM2:51
 */

#ifndef COMPA_UTILI_H
#define COMPA_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif
    
    //
#include <stdio.h>
    
#include "commo_header.h"
#include "rive_stru.h"
#include "conte_resou.h"

    // not equal   
    int lid_text_noteq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu);
    int lid_lolo_noteq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu);
    int lid_doub_noteq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu);
    
    // equal   
    int lid_text_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu);
    int lid_lolo_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu);
    int lid_doub_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu);
    int lid_rid_equal(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *rid_valu);

    // great
    int lid_text_great(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu);
    int lid_lolo_great(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu);
    int lid_doub_great(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu);

    //
    int lid_text_leseq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu);
    int lid_lolo_leseq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu);
    int lid_doub_leseq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu);

    //
    int lid_text_less(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu);
    int lid_lolo_less(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu);
    int lid_doub_less(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu);

    //
    int lid_text_greeq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, char *stri_valu);
    int lid_lolo_greeq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, long long lolo_valu);
    int lid_doub_greeq(FILE *resul, riv_curso_t *lidcu, rive_ha *stora_ha, double doub_valu);

#ifdef __cplusplus
}
#endif

#endif /* COMPA_UTILI_H */

