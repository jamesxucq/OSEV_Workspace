
#include "opera_utili.h"
#include "compa_utili.h"
#include "cstri_utili.h"
#include "quer_plan.h"

#include "conte_resou.h"
#include "dyli_list.h"

//
// cursa operation

int hand_open_conte(physi_conte *phy_con, rive_conne *rvcon, rive_ha *stora_ha, char *cont_name) {
    if (!phy_con->initi) {
        phy_con->slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
        phy_con->initi = 0x01;
    }
    //
    if (cont_name) {
        curso_resou *cures = phy_con->cures;
        for (; cures->procu; cures++);
        if (stora_ha->open_table(&(cures->procu), phy_con->slist->seion, cont_name, NULL)) {
            quiet_seion_bzl(&rvcon->slist, phy_con->slist);
            return -1;
        }
        strcpy(cures->cont_name, cont_name);
    }
    //
    return 0x00;
}

int hand_close_conte(physi_conte *phy_con, rive_conne *rvcon, rive_ha *stora_ha) {
    if (phy_con->initi) {
        curso_resou *cures = phy_con->cures;
        for (; cures->procu; cures++) stora_ha->close_curso(cures->procu);
        quiet_seion_bzl(&rvcon->slist, phy_con->slist);
        phy_con->initi = 0x00;
    }
    //
    return 0x00;
}

//

riv_curso_t *find_curso(rive_ha *stora_ha, physi_conte *phy_con, char *cont_name) {
    curso_resou *cures = phy_con->cures;
    int inde = 0x00;
    for (; strcmp(cont_name, cures->cont_name) && (SOUR_COTE > inde); inde++, cures++);
    if (SOUR_COTE == inde) return NULL;
    stora_ha->reset_curso(cures->procu);
    //
    return cures->procu;
}

riv_curso_t *creat_curso(rive_ha *stora_ha, physi_conte *phy_con, char *cont_name, char *lid_valu) {
    riv_curso_t *curso;
    char crea_uri[MAX_PATH];
    //
    crea_proj_uri(crea_uri, cont_name, lid_valu);
    printf("creat_curso, crea_uri:|%s|\n", crea_uri);
    if (stora_ha->open_curso(&curso, phy_con->slist->seion, crea_uri, NULL))
        return NULL;
    //
    return curso;
}

