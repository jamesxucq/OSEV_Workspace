#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "expre_utili.h"
#include "estr_utili.h"
#include "quer_plan.h"
#include "dope_plan.h"
#include "physi_execu.h"
#include "synta_tree.h"

#include "dropo.h"

//

static void p_plan_node(plan_node *que_tok) {
    for (; que_tok->acti_oper; que_tok++)
        printf("que_tok->acti_oper:%08X cont_name:|%s|  source_str:|%s|\n", que_tok->acti_oper, que_tok->cont_name, que_tok->source_str);
}

// fix me, 20170412
// predicate drop / condition

static int condi_contad(rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *cont_name, char *para_str) {
    printf("condi_contad, dldap->data_size:%d\n", dldap->data_size);
    printf("para_str:|%s|\n", para_str);
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, para_str)) {
        _LOG_WARN("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    printf("creat_plan_dope\n");
    plan_node *quer_plan = (plan_node *) malloc(PLAN_ITEM_SZIE * sizeof (plan_node));
    if (!quer_plan) return -1;
    if (creat_plan_dope(quer_plan, cont_name, synt_head)) {
        free(quer_plan);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    p_plan_node(quer_plan);
    // physical execute
    int drop_valu = execu_physi_drop(rvcon, stora_ha, dldap, quer_plan);
    free(quer_plan);
    return drop_valu;
}

//

static int objeid_contad(rive_conne *rvcon, rive_ha *stora_ha, char *cont_name, char *para_str) {
    int drop_valu = 0x00;
    osv_oid_i obje_id;
    //
    printf("objeid_contad\n");
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    printf("conta->cont_name:%s\n", cont_name);
    if (stora_ha->open_table(&curso, slist->seion, cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    stroid((osv_oid_t *) & obje_id, para_str);
    stora_ha->set_key(curso, obje_id.stoid);
    if (0x00 == stora_ha->sear_curso(curso))
        drop_valu = stora_ha->remove_curso(curso);
    //
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    return drop_valu;
}

//

static int traver_contad(rive_conne *rvcon, rive_ha *stora_ha, char *cont_name) {
    int drop_valu = 0x00;
    //
    printf("traver_contad\n");
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    printf("conta->cont_name:%s\n", cont_name);
    if (stora_ha->open_table(&curso, slist->seion, cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    while (0x00 == stora_ha->next_curso(curso)) {
        drop_valu = stora_ha->remove_curso(curso);
        if (drop_valu) break;
    }
    //
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    return drop_valu;
}

//
// -1:error 0x00:ok 0x01:exception

int drop_entity_obje(rive_conne *rvcon, contain *conta, hand_data *handa, char **paras) {
    int drop_valu = -1;
    //
    printf("drop_entity_obje, paras[0x00]:%s\n", paras[0x00]);
    dyli_data *dldap = (dyli_data *) action_value(conta->data_type, handa->ocuse_hm);
    if (!dldap) {
        _LOG_DEBUG("doh dldap:%lld ocuse_hm:%lld", (long long) dldap, (long long) handa->ocuse_hm);
        return -1;
    }
    // -1:error 0x00:objeid 0x01:predicate / condition 0x02:"*"
    if (paras[0x00]) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
        switch (check_predi_type(paras[0x00])) {
            case PREDI_TYPE_OBJID:
                drop_valu = objeid_contad(rvcon, conta->stora_ha, conta->cont_name, paras[0x00]);
                break;
            case PREDI_TYPE_CONDI:
                drop_valu = condi_contad(rvcon, conta->stora_ha, dldap, conta->cont_name, paras[0x00]);
                break;
            case PREDI_TYPE_TRAVE:
                drop_valu = traver_contad(rvcon, conta->stora_ha, conta->cont_name);
                break;
            case PREDI_TYPE_EXCEP:
                break;
        }
    } else drop_valu = traver_contad(rvcon, conta->stora_ha, conta->cont_name);
    //
    return drop_valu;
}