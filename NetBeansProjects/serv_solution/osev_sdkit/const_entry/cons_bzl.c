#include "commo_header.h"

#include "cons_obje.h"
#include "creao.h"
#include "dropo.h"
#include "eacho.h"
#include "findo.h"
#include "inser.h"
#include "updat.h"

#include "rive_bzl.h"
#include "cons_bzl.h"
#include "osev_struct.h"

/*
int invobzl_create(char *data_directory) {
    strcpy(_invo_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int invobzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

int cons_echo_bzl(prod_data *sresp, contain *conta) {
    memcpy(sresp->sebuf, &conta->oid, sizeof (osv_oid_t));
    (sresp->colen)[0x00] = sizeof (osv_oid_t);
    return 0x00;
}

int cons_creat_bzl(prod_data *sresp, contain *conta, hand_data *hando, rive_conne *rvcon, char **paras) {
    int cons_valu = -1;
    // create a user object
    printf("creat a user object.\n");
    rive_ha *stora_ha = conta->stora_ha;
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    if (stora_ha->open_table(&curso, slist->seion, conta->cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    printf("conta->cont_name:%s\n", conta->cont_name);
    // wt_begin_transa_sess(slist->seion);
    cons_valu = creat_entity_obje(curso, stora_ha, hando, conta->data_type, paras);
    // wt_commit_transa_sess(slist->seion);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    PDAT_NONE_TAIL(sresp)
            //
    return cons_valu;
}

int cons_drop_bzl(prod_data *sresp, contain *conta, hand_data *handa, rive_conne *rvcon, char **paras) {
    // drop user object
    printf("drop user object.\n");
    if (drop_entity_obje(rvcon, conta, handa, paras))
        return -1;
    PDAT_NONE_TAIL(sresp)
            //
    return 0x00;
}

int cons_updat_bzl(prod_data *sresp, contain *conta, hand_data *handa, rive_conne *rvcon, char **paras) {
    int cons_valu = -1;
    // updat user object
    printf("updat user object.\n");
    rive_ha *stora_ha = conta->stora_ha;
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    printf("conta->cont_name:%s\n", conta->cont_name);
    if (stora_ha->open_table(&curso, slist->seion, conta->cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    cons_valu = updat_entity_obje(curso, stora_ha, handa, conta->data_type, paras);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    PDAT_NONE_TAIL(sresp)
            //
    return cons_valu;
}

int cons_inser_bzl(prod_data *sresp, contain *conta, hand_data *handa, rive_conne *rvcon, char **paras) {
    int cons_valu = -1;
    // inser user object
    printf("inser user object.\n");
    rive_ha *stora_ha = conta->stora_ha;
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    printf("conta->cont_name:%s\n", conta->cont_name);
    if (stora_ha->open_table(&curso, slist->seion, conta->cont_name, RIV_NOVWT_CONF)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    cons_valu = inser_entity_obje(curso, stora_ha, handa, conta->data_type, paras);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    PDAT_NONE_TAIL(sresp)
            //
    return cons_valu;
}

//

int cons_each_bzl(prod_data *sresp, contain *conta, hand_data *hando, rive_conne *rvcon, char **paras) {
    // each user object
    printf("each user object.\n");
    //
    int cons_valu = each_entity_obje(sresp, rvcon, conta, hando, paras);
    return cons_valu;
}

//

int cons_find_bzl(prod_data *sresp, contain *conta, hand_data *handa, rive_conne *rvcon, conoda *coval, char **paras) {
    printf("cons_find_bzl\n");
    // zero / one param
    if (!paras[0x00] || !paras[0x01]) return find_oenti_obje(sresp, rvcon, conta, handa, paras);
    // two param. contain
    contain *dcont = (contain *) action_value(paras[0x00], coval->conda.contn_hm);
    if (dcont) {
        printf("find contain\n");
        if (!find_oenti_cont(sresp, rvcon, dcont, conta, handa, paras)) {
            PDAT_NONE_TAIL(sresp);
            return 0x00;
        }
        return -1;
    }
    // two param. class
    printf("find class\n");
    // class = find_class();
    // if (class) return find_oenti_clas(sresp, rvcon, conta, handa, paras);
    // declaration
    // decla = find_decla();
    // if (decla) return find_oenti_decl(sresp, rvcon, conta, handa, paras);
    //
    return -1;
}
