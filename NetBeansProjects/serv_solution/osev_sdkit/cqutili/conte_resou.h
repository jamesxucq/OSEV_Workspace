
/* 
 * File:   conte_resou.h
 * Author: james
 *
 * Created on 20210301, PM3:10
 */

#ifndef CONTE_RESOU_H
#define CONTE_RESOU_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "quer_plan.h"

    //

    typedef struct {
        riv_curso_t *procu;
        char cont_name[OBJE_LENGTH];
    } curso_resou;

    typedef struct {
        int initi; // 0:uninit 1:ok
        seio_list *slist;
        curso_resou cures[SOUR_COTE];
    } physi_conte;

    // cursa operation
    int hand_open_conte(physi_conte *phy_con, rive_conne *rvcon, rive_ha *stora_ha, char *cont_name);
    int hand_close_conte(physi_conte *phy_con, rive_conne *rvcon, rive_ha *stora_ha);
    
    //
    riv_curso_t *find_curso(rive_ha *stora_ha, physi_conte *phy_con, char *cont_name);
    riv_curso_t *creat_curso(rive_ha *stora_ha, physi_conte *phy_con, char *cont_name, char *lid_valu);
#define CLOSE_CURSO(STORA_HA, LID_CURS) STORA_HA->close_curso(LID_CURS)

#ifdef __cplusplus
}
#endif

#endif /* CONTE_RESOU_H */

