
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opera_utili.h"
#include "astri_utili.h"
#include "expre_utili.h"
#include "findq.h"
#include "dyli_list.h"
#include "find_plan.h"
#include "synta_tree.h"

//

struct test {
    osv_oid_i obje_oid;
    int xx;
    int ax;
    int cx;
};

static void print_test(struct test *obje) {
    char oid_stri[OID_LINE_LEN];
    oidstr(oid_stri, (osv_oid_t *) & obje->obje_oid);
    printf("|%s|%d|%d|%d|\n", oid_stri, obje->xx, obje->ax, obje->cx);
}

// odb:find("clasn", "conobje", "obje:numb() > 0x00");
// :find("cobje", "conobje", "obje:numb() > 0x00");
// :find("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// odb:find("cobje", "conobje");
// fix me, 20170412
// predicate find / condition

static int condi_contaq(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *source_str, char *para_str) {
    printf("condi_contaq, dldap->data_size:%d\n", dldap->data_size);
    char quer_conta[SOUR_COTE][OBJE_LENGTH];
    int socou = query_source_coten(quer_conta, source_str);
    if (!socou) return -1;
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, para_str)) {
        _LOG_WARN("condi_contaq: %s\n", erro_msg);
        return -1;
    }
    //
    plan_node *quer_plan = (plan_node *) malloc(PLAN_ITEM_SZIE * sizeof (plan_node));
    if (creat_find_plan_multip(quer_plan, quer_conta, synt_head)) {
        free(quer_plan);
        return -1;
    }
    // physical
    int find_valu = execu_physi_find(sresp, rvcon, stora_ha, dldap, quer_plan);
    DESTROY_STREE(synt_head);
    free(quer_plan);
    //
    return find_valu;
}

static int objeid_contaq(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *source_str, char *obje_iden) {
    printf("objeid_contaq_con, dldap->data_size:%d\n", dldap->data_size);
    int socou = query_source_numb(source_str);
    if (0x01 != socou) return -1;
    //
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    if (stora_ha->open_table(&curso, slist->seion, source_str, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    osv_oid_i obje_oid;
    stroid((osv_oid_t *) & obje_oid, obje_iden);
    if (obje_oid.osev_unique != instan_unique()) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    stora_ha->set_key(curso, obje_oid.stoid);
    if (0x00 != stora_ha->sear_curso(curso)) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    // find object error!
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    mapid_unique((osv_oid_t *) obje_data);
    dldap->solve(obje_data, curso);
    if (0x00 >= APPEND_DATAS(sresp->sedat, obje_data, dldap->data_size)) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        free(obje_data);
        return -1;
    }
    rewind(sresp->sedat);
    (sresp->colen)[0x00] = dldap->data_size;
    //
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    free(obje_data);
    return 0x00;
}

//

static int traver_contaq(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *source_str) {
    printf("traver_contaq_con, dldap->data_size:%d\n", dldap->data_size);
    int socou = query_source_numb(source_str);
    if (0x01 != socou) return -1;
    //
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    if (stora_ha->open_table(&curso, slist->seion, source_str, NULL)) {
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
    int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(curso); inde++) {
        dldap->solve(obje_data, curso);
        print_test((struct test *) obje_data);
        // printf("wt_next_curs\n");
        if (0x00 >= APPEND_DATAS(sresp->sedat, obje_data, dldap->data_size)) {
            stora_ha->close_curso(curso);
            quiet_seion_bzl(&rvcon->slist, slist);
            free(obje_data);
            return -1;
        }
        // log_binary_file(obje_data, dldap->data_size, "./binary_code.bin_f");
    }
    rewind(sresp->sedat);
    (sresp->colen)[0x00] = dldap->data_size * inde;
    // printf("(sresp->colen)[0x00]:%d\n", (sresp->colen)[0x00]);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    free(obje_data);
    return 0x00;
}


//

int find_conta_obje(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, hand_data *handa, char *clasn, char **paras) {
    _LOG_DEBUG("find_conta_obje clasn:|%s|", clasn);
    //
    dyli_data *dldap = (dyli_data *) action_value(clasn, handa->ocuse_hm);
    if (!dldap) {
        _LOG_DEBUG("doh dldap:%lld ocuse_hm:%lld", (long long) dldap, (long long) handa->ocuse_hm);
        return -1;
    }
    //
    int find_valu = -1;
    if (paras[0x02]) { // -1:error 0x00:objeid 0x01:predi
        switch (check_predi_type(paras[0x00])) {
            case PREDI_TYPE_OBJID:
                find_valu = objeid_contaq(sresp, rvcon, stora_ha, dldap, paras[0x01], paras[0x02]);
                break;
            case PREDI_TYPE_CONDI:
                find_valu = condi_contaq(sresp, rvcon, stora_ha, dldap, paras[0x01], paras[0x02]);
                break;
            case PREDI_TYPE_TRAVE:
                find_valu = traver_contaq(sresp, rvcon, stora_ha, dldap, paras[0x01]);
                break;
            default:
                break;
        }
    } else find_valu = traver_contaq(sresp, rvcon, stora_ha, dldap, paras[0x01]);
    //
    return find_valu;
}