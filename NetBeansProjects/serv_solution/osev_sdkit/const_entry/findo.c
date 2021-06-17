#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cqutili/expre_utili.h"
#include "../cqutili/physi_execu.h"
#include "opera_utili.h"
#include "estr_utili.h"
#include "findo.h"
#include "dyli_list.h"
#include "quer_plan.h"
#include "synta_tree.h"
#include "load_entry.h"
#include "find_plan.h"

//

static void p_plan_node(plan_node *que_tok) {
    for (; que_tok->acti_oper; que_tok++)
        printf("que_tok->acti_oper:%08X cont_name:|%s|  source_str:|%s|\n", que_tok->acti_oper, que_tok->cont_name, que_tok->source_str);
}

// fix me, 20170412
// predicate find / condition

static int condi_contao(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *cont_name, char *para_str) {
    printf("condi_contao, dldap->data_size:%d\n", dldap->data_size);
    printf("para_str:|%s|\n", para_str);
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, para_str)) {
        _LOG_WARN("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    printf("creat_find_plan_single\n");
    plan_node *quer_plan = (plan_node *) malloc(PLAN_ITEM_SZIE * sizeof (plan_node));
    if (!quer_plan) return -1;
    if (creat_find_plan_single(quer_plan, cont_name, synt_head)) {
        free(quer_plan);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    p_plan_node(quer_plan);
    // physical execute
    int find_valu = execu_physi_find(sresp, rvcon, stora_ha, dldap, quer_plan);
    free(quer_plan);
    return find_valu;
}

//

static int objeid_contao(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *cont_name, char *obje_iden) {
    printf("objeid contao, dldap->data_size:%d\n", dldap->data_size);
    //
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    if (stora_ha->open_table(&curso, slist->seion, cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    osv_oid_i obje_id;
    stroid((osv_oid_t *) & obje_id, obje_iden);
    if (obje_id.osev_unique != instan_unique()) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    stora_ha->set_key(curso, obje_id.stoid);
    if (0x00 != stora_ha->sear_curso(curso)) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //find object error!
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    mapid_unique((osv_oid_t *) obje_data);
    dldap->solve(obje_data, curso);
    if (0x00 >= APPEND_DATAS(sresp->sedat, obje_data, dldap->data_size)) {
        free(obje_data);
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    rewind(sresp->sedat);
    (sresp->colen)[0x00] = dldap->data_size;
    //
    free(obje_data);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    return 0x00;
}

//

struct test {
    osv_oid_i obje_oid;
    int xx;
    int ax;
    int cx;
};

/*
static void print_test(struct test *obje) {
    char oid_stri[OID_LINE_LEN];
    oidstr(oid_stri, (osv_oid_t *) & obje->obje_oid);
    printf("|%s|%d|%d|%d|\n", oid_stri, obje->xx, obje->ax, obje->cx);
}
 */

static int traver_contao(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *cont_name) {
    printf("traver contao, dldap->data_size:%d\n", dldap->data_size);
    //
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    if (stora_ha->open_table(&curso, slist->seion, cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    mapid_unique((osv_oid_t *) obje_data);
    int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(curso); inde++) {
        dldap->solve(obje_data, curso);
        // print_test((struct test *) obje_data);
        // printf("wt_next_curs\n");
        if (0x00 >= APPEND_DATAS(sresp->sedat, obje_data, dldap->data_size)) {
            free(obje_data);
            stora_ha->close_curso(curso);
            quiet_seion_bzl(&rvcon->slist, slist);
            return -1;
        }
        // log_binary_file(obje_data, dldap->data_size, "./binary_code.bin_f");
    }
    rewind(sresp->sedat);
    (sresp->colen)[0x00] = dldap->data_size * inde;
    printf("(sresp->colen)[0x00]:%llu\n", (sresp->colen)[0x00]);
    //
    free(obje_data);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    return 0x00;
}

//

int find_oenti_obje(prod_data *sresp, rive_conne *rvcon, contain *conta, hand_data *handa, char **paras) {
    _LOG_DEBUG("cuo clasn:|%s| handa->ocuse_hm:%08X", conta->data_type, handa->ocuse_hm);
    //
    dyli_data *dldap = (dyli_data *) action_value(conta->data_type, handa->ocuse_hm);
    if (!dldap) {
        _LOG_DEBUG("doh dldap:%lld ocuse_hm:%lld", (long long) dldap, (long long) handa->ocuse_hm);
        return -1;
    }
    // printf("dldap:%08X, dldap->bound:%08X\n", dldap, dldap->bound);
    int find_valu = -1;
    if (paras[0x00]) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
        switch (check_predi_type(paras[0x00])) {
            case PREDI_TYPE_OBJID:
                find_valu = objeid_contao(sresp, rvcon, conta->stora_ha, dldap, conta->cont_name, paras[0x00]);
                break;
            case PREDI_TYPE_CONDI:
                find_valu = condi_contao(sresp, rvcon, conta->stora_ha, dldap, conta->cont_name, paras[0x00]);
                break;
            case PREDI_TYPE_TRAVE:
                find_valu = traver_contao(sresp, rvcon, conta->stora_ha, dldap, conta->cont_name);
                break;
            default:
                break;
        }
    } else find_valu = traver_contao(sresp, rvcon, conta->stora_ha, dldap, conta->cont_name);
    //
    return find_valu;
}

//

int find_oenti_clas(prod_data *sresp, rive_conne *rvcon, contain *conta, hand_data *handa, char **paras) {
    _LOG_DEBUG("cuo clasn:|%s| handa->ocuse_hm:%08X", conta->data_type, handa->ocuse_hm);
    //
    dyli_data *dldap = (dyli_data *) action_value(conta->data_type, handa->ocuse_hm);
    if (!dldap) {
        _LOG_DEBUG("doh dldap:%lld ocuse_hm:%lld", (long long) dldap, (long long) handa->ocuse_hm);
        return -1;
    }
    // printf("dldap:%08X, dldap->bound:%08X\n", dldap, dldap->bound);
    printf("para_str:|%s|\n", paras[0x01]);
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, paras[0x01])) {
        _LOG_WARN("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    printf("creat_find_plan_single\n");
    plan_node *quer_plan = (plan_node *) malloc(PLAN_ITEM_SZIE * sizeof (plan_node));
    if (creat_find_plan_single(quer_plan, conta->cont_name, synt_head)) {
        free(quer_plan);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    // physical
    printf("execu_physi_find\n");
    int find_valu = execu_physi_find(sresp, rvcon, conta->stora_ha, dldap, quer_plan);
    free(quer_plan);
    return find_valu;
}

//

int find_oenti_cont(prod_data *sresp, rive_conne *rvcon, contain *dcont, contain *conta, hand_data *handa, char **paras) {
    _LOG_DEBUG("cuo clasn:|%s| handa->ocuse_hm:%08X", conta->data_type, handa->ocuse_hm);
    //
    dyli_data *dldap = (dyli_data *) action_value(conta->data_type, handa->ocuse_hm);
    if (!dldap) {
        _LOG_DEBUG("doh dldap:%lld ocuse_hm:%lld", (long long) dldap, (long long) handa->ocuse_hm);
        return -1;
    }
    // printf("dldap:%08X, dldap->bound:%08X\n", dldap, dldap->bound);
    printf("para_str:|%s|\n", paras[0x01]);
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, paras[0x01])) {
        _LOG_WARN("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    printf("creat_find_plan_single\n");
    plan_node *quer_plan = (plan_node *) malloc(PLAN_ITEM_SZIE * sizeof (plan_node));
    if (creat_find_plan_single(quer_plan, conta->cont_name, synt_head)) {
        free(quer_plan);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    // physical
    printf("execu_physi_find\n");
    if (execu_physi_find(sresp, rvcon, conta->stora_ha, dldap, quer_plan)) {
        free(quer_plan);
        return -1;
    }
    free(quer_plan);
    // load obje to contaion
    if (load_obje_cont(dcont, sresp)) return -1;
    return 0x00;
}