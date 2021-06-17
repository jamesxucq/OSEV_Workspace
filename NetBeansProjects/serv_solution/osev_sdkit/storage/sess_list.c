
#include <stdlib.h>
#include <string.h>


#include "sess_list.h"
#include "rive_bzl.h"

//

seio_list *activ_seion(seio_list **slsth, rive_ha *stora_ha, riv_conne_t *conne) {
    seio_list *slist = NULL;
    //
    if ((*slsth)) {
        slist = *slsth;
        *slsth = slist->next;
        stora_ha->reset_sessi(slist->seion);
    } else {
        slist = (seio_list *) malloc(sizeof (seio_list));
        if (!slist) return slist;
        //
        if (stora_ha->open_sessi(conne, &slist->seion)) {
            stora_ha->close_sessi(slist->seion);
            return NULL;
        }
    }
    //
    return slist;
}

//

void quiet_seion(seio_list **slsth, seio_list *slist) {
    slist->next = (*slsth);
    *slsth = slist;
}

//

void destroy_seion(seio_list *slist, rive_ha *stora_ha) {
    for (; slist; slist = slist->next) {
        stora_ha->close_sessi(slist->seion);
    }
}