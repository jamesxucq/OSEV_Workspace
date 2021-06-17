#include "commo_header.h"
#include "astri_utili.h"

#include "quer_obje.h"
#include "creaq.h"
#include "dropq.h"
#include "facto.h"
#include "findq.h"
#include "eachq.h"

#include "rive_bzl.h"
#include "cona_utili.h"
#include "quer_bzl.h"
#include "conoda.h"

//

/*
int querbzl_create(char *data_directory) {
    strcpy(_quer_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int querbzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */


//

int quer_echo_bzl(prod_data *sresp, contain *conta) {
    memcpy(sresp->sebuf, &conta->oid, sizeof (osv_oid_t));
    (sresp->colen)[0x00] = sizeof (osv_oid_t);
    return 0x00;
}

int quer_creat_bzl(rive_conne *rvcon, char *osdb, char **paras) {
    int quer_valu = -1;
    printf("create a contain instance.\n");
    rive_ha *stora_ha = _storage_ha_[((uint32 *) paras[0x01])[0x00]];
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    // printf("paras[0x00]:|%s| paras[0x01]:|%s| paras[0x02]:|%s|\n", paras[0x00], paras[0x01], paras[0x02]);
    quer_valu = qcreat_conta_obje(slist->seion, stora_ha, osdb, paras[0x00], ((uint32 *) paras[0x01])[0x00], paras[0x02]);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    return quer_valu;
}

int quer_drop_bzl(rive_conne *rvcon, rive_ha *stora_ha, char *osdb, char **paras) {
    int quer_valu = -1;
    // drop contain
    printf("drop contain.\n");
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    printf("r paras[0x00]:%s\n", paras[0x00]);
    quer_valu = drop_conta_obje(slist->seion, stora_ha, osdb, paras[0x00]);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    return quer_valu;
}

int quer_find_bzl(prod_data *sresp, query_data *qrequ) {
printf("quer_find_bzl, qrequ->paras[0x00]:|%s|\n", qrequ->paras[0x00]);
    contain *conta = (contain *) action_value(qrequ->paras[0x00], qrequ->conda->contn_hm);
    if (conta) return -1;
    //
    int quer_valu = find_conta_obje(sresp, qrequ->rvcon, conta->stora_ha, qrequ->handa, conta->data_type, qrequ->paras);
    return quer_valu;
}

int quer_facto_bzl(prod_data *sresp, query_data *qrequ) {
printf("quer_facto_bzl\n");
    int quer_valu = -1;
    contain *conta = (contain *) action_value(qrequ->paras[0x00], qrequ->conda->contn_hm);
    if (conta) return -1;
    quer_valu = facto_class_obje(sresp, qrequ->rvcon, conta->stora_ha, qrequ->handa, qrequ->paras);
    return quer_valu;
}

int quer_invok_bzl(prod_data *sresp, contain *conta, hand_data *hando, rive_conne *rvcon, char **paras) {
    int quer_valu = -1;
    // each conta object
    printf("each conta object.\n");
    rive_ha *stora_ha = conta->stora_ha;
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    printf("conta->cont_name:%s\n", conta->cont_name);
    if (stora_ha->open_table(&curso, slist->seion, conta->cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    quer_valu = each_conta_obje(sresp, curso, stora_ha, hando, conta->data_type, paras);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    return quer_valu;
}

//
