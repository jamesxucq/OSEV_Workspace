
/* 
 * File:   seio_list.h
 * Author: James Xu
 *
 * Created on 2017.2.7, AM 10:12
 */

#ifndef SESS_LIST_H
#define SESS_LIST_H

#include "rive_stru.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    seio_list *activ_seion(seio_list **slsth, rive_ha *stora_ha, riv_conne_t *conne);
    void quiet_seion(seio_list **slsth, seio_list *slist);
    void destroy_seion(seio_list *slist, rive_ha *stora_ha);

    //

#ifdef __cplusplus
}
#endif

#endif /* SESS_LIST_H */

