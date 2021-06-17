#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opera_utili.h"
#include "estr_utili.h"
#include "dope_plan.h"
#include "dyli_list.h"
#include "physi_execu.h"
#include "expre_utili.h"
#include "eacho.h"

//

union _retype_ {
    char rchar;
    unsigned char rucha;
    short rshor;
    unsigned short rusho;
    int rint;
    unsigned int ruint;
    long rlong;
    unsigned long rulong;
    long long rllong;
    unsigned long long rullon;
    double rdoub;
    char* rchap;
};

#pragma pack(1)

typedef struct {
    osv_oid_i obje_id;
    union _retype_ retype;
} retval;
#pragma pack()

// static int type_len[0x07] = {0, 1, 1, 2, 2, 4, 4, 8, 8, 8, 8, 8, 8};
static int type_len[13] = {12, 13, 13, 14, 14, 16, 16, 20, 20, 20, 20, 20, 20};

//

static void p_plan_node(plan_node *que_tok) {
    for (; que_tok->acti_oper; que_tok++)
        printf("que_tok->acti_oper:%08X cont_name:|%s|  source_str:|%s|\n", que_tok->acti_oper, que_tok->cont_name, que_tok->source_str);
}

// fix me, 20170412
// predicate find / condition

static int condi_contae(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_meth *dlmep, char *cont_name, char *para_str) {
    printf("condi_drop, dldap->data_size:%d\n", dlmep->dldat->data_size);
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
    int each_valu = execu_physi_each(sresp, rvcon, stora_ha, dlmep, quer_plan);
    free(quer_plan);
    return each_valu;
}

//

static int objeid_contae(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_meth *dlmep, char *cont_name, char *para_str) {
    dyli_data *dldap = dlmep->dldat;
    osv_oid_i obje_id;
    printf("objeid contao, dlmep->retype:%d\n", dlmep->retype);
    //
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
    if (0x00 != stora_ha->sear_curso(curso)) return -1;
    //
    retval rvalu;
    mapid_unique((osv_oid_t *) & rvalu.obje_id);
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) return -1;
    dldap->solve(obje_data, curso);
    rvalu.obje_id.stoid = ((osv_oid_i *) obje_data)->stoid;
    switch (dlmep->retype) {
        case rtyp_void:
            dlmep->method.meth_void(obje_data);
            break;
        case rtyp_char:
            rvalu.retype.rchar = dlmep->method.meth_char(obje_data);
            break;
        case rtyp_ucha:
            rvalu.retype.rucha = dlmep->method.meth_ucha(obje_data);
            break;
        case rtyp_shor:
            rvalu.retype.rshor = dlmep->method.meth_shor(obje_data);
            break;
        case rtyp_usho:
            rvalu.retype.rusho = dlmep->method.meth_usho(obje_data);
            break;
        case rtyp_int:
            rvalu.retype.rint = dlmep->method.meth_int(obje_data);
            break;
        case rtyp_uint:
            rvalu.retype.ruint = dlmep->method.meth_uint(obje_data);
            break;
        case rtyp_long:
            rvalu.retype.rlong = dlmep->method.meth_long(obje_data);
            break;
        case rtyp_ulon:
            rvalu.retype.rulong = dlmep->method.meth_ulong(obje_data);
            break;
        case rtyp_llon:
            rvalu.retype.rllong = dlmep->method.meth_llong(obje_data);
            break;
        case rtyp_ullo:
            rvalu.retype.rullon = dlmep->method.meth_ullong(obje_data);
            break;
        case rtyp_chap:
            rvalu.retype.rchap = dlmep->method.meth_chap(obje_data);
            break;
    }
    dldap->bound(curso, obje_data);
    if (!stora_ha->update_curso(curso)) {
        if (0x00 >= APPEND_DATAS(sresp->sedat, (char *) &rvalu, type_len[dlmep->retype])) {
            free(obje_data);
            return -1;
        }
    }
    rewind(sresp->sedat);
    (sresp->colen)[0x00] = type_len[dlmep->retype];
    //
    free(obje_data);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    return 0x00;
}

//

static int traver_contae(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_meth *dlmep, char *cont_name) {
    dyli_data *dldap = dlmep->dldat;
    printf("traver contao, dlmep->retype:%d\n", dlmep->retype);
    //
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    printf("conta->cont_name:%s\n", cont_name);
    if (stora_ha->open_table(&curso, slist->seion, cont_name, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    retval rvalu;
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) {
        return -1;
    }
    mapid_unique((osv_oid_t *) & rvalu.obje_id);
    int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(curso); inde++) {
        dldap->solve(obje_data, curso);
        rvalu.obje_id.stoid = ((osv_oid_i *) obje_data)->stoid;
        switch (dlmep->retype) {
            case rtyp_void:
                dlmep->method.meth_void(obje_data);
                break;
            case rtyp_char:
                rvalu.retype.rchar = dlmep->method.meth_char(obje_data);
                break;
            case rtyp_ucha:
                rvalu.retype.rucha = dlmep->method.meth_ucha(obje_data);
                break;
            case rtyp_shor:
                rvalu.retype.rshor = dlmep->method.meth_shor(obje_data);
                break;
            case rtyp_usho:
                rvalu.retype.rusho = dlmep->method.meth_usho(obje_data);
                break;
            case rtyp_int:
                rvalu.retype.rint = dlmep->method.meth_int(obje_data);
                printf("rvalu.retype.rint:%d\n", rvalu.retype.rint);
                break;
            case rtyp_uint:
                rvalu.retype.ruint = dlmep->method.meth_uint(obje_data);
                break;
            case rtyp_long:
                rvalu.retype.rlong = dlmep->method.meth_long(obje_data);
                break;
            case rtyp_ulon:
                rvalu.retype.rulong = dlmep->method.meth_ulong(obje_data);
                break;
            case rtyp_llon:
                rvalu.retype.rllong = dlmep->method.meth_llong(obje_data);
                break;
            case rtyp_ullo:
                rvalu.retype.rullon = dlmep->method.meth_ullong(obje_data);
                break;
            case rtyp_chap:
                rvalu.retype.rchap = dlmep->method.meth_chap(obje_data);
                break;
        }
        dldap->bound(curso, obje_data);
        if (!stora_ha->update_curso(curso)) {
            if (0x00 >= APPEND_DATAS(sresp->sedat, (char *) &rvalu, type_len[dlmep->retype])) {
                free(obje_data);
                return -1;
            }
        }
    }
    rewind(sresp->sedat);
    (sresp->colen)[0x00] = type_len[dlmep->retype] * inde;
    printf("(sresp->colen)[0x00]:%llu\n", (sresp->colen)[0x00]);
    //
    free(obje_data);
    stora_ha->close_curso(curso);
    quiet_seion_bzl(&rvcon->slist, slist);
    //
    return 0x00;
}

//

static char *decode_invop(char *each_line, char *paras[PARAM_NUMB], char *invop_str) {
    printf("decode_invop\n");
    char *parse_tok = invop_str;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) return NULL;
    //
    char *last_str = decode_object(each_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static int decode_invok(char *clasn, char *metnm, char *each_line, char *paras[PARAM_NUMB], char *invop_str) {
    printf("decode_invok\n");
    char *parse_tok = invop_str;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) return -1;
    printf("req_len:%d", req_len);
    //
    char para_cont[PARAM_LENGTH];
    parse_tok = pstyl_stri(para_cont, parse_tok);
    if (!parse_tok) return -1;
    strcpy(clasn, para_cont);
    printf(" clasn:|%s|", clasn);
    //
    parse_tok = pstyl_stri(para_cont, parse_tok);
    if (!parse_tok) return -1;
    strcpy(metnm, para_cont);
    printf(" metnm:|%s|", metnm);
    //
    if (!decode_invop(each_line, paras, parse_tok)) return -1;
    printf(" paras[0x00]:|%s| paras[0x01]:|%s|\n", paras[0x00], paras[0x01]);
    //
    return 0x00;
}

//

int each_entity_obje(prod_data *sresp, rive_conne *rvcon, contain *conta, hand_data *hando, char **paras) {
    _LOG_DEBUG("each_entity_obje clasn:|%s| paras[0x00]:|%s| paras[0x01]:|%s|", conta->data_type, paras[0x00], paras[0x01]);
    //
    char each_clasn[CLASS_LENGTH];
    char each_metn[METH_LENGTH];
    char each_line[LINE_LENGTH];
    char *eparas[PARAM_NUMB];
    decode_invok(each_clasn, each_metn, each_line, eparas, paras[0x00]);
    if (strcmp(conta->data_type, each_clasn)) return -1;
    //    
    char handn[HAND_LENGTH];
    if (!build_qcons_handn(handn, each_clasn, each_metn, eparas)) return -1;
    _LOG_DEBUG("cuo handn:|%s| clasn:|%s|", handn, conta->data_type);
    //
    dyli_meth *dlmep = (dyli_meth *) action_value(handn, hando->ocuse_hm);
    if (!dlmep) {
        _LOG_DEBUG("doh dlmep:%lld ocuse_hm:%lld", (long long) dlmep, (long long) hando->ocuse_hm);
        return -1;
    }
    dlmep->parser(eparas);
    //    
    int each_valu = -1;
    if (paras[0x01]) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
        switch (check_predi_type(paras[0x01])) {
            case PREDI_TYPE_OBJID:
                each_valu = objeid_contae(sresp,  rvcon, conta->stora_ha, dlmep, conta->cont_name, paras[0x01]);
                break;
            case PREDI_TYPE_CONDI:
                each_valu = condi_contae(sresp, rvcon, conta->stora_ha, dlmep, conta->cont_name, paras[0x01]);
                break;
            case PREDI_TYPE_TRAVE:
                each_valu = traver_contae(sresp,  rvcon, conta->stora_ha, dlmep, conta->cont_name);
                break;
            case PREDI_TYPE_EXCEP:
                break;
        }
    } else each_valu = traver_contae(sresp,  rvcon, conta->stora_ha, dlmep, conta->cont_name);
    //
    return each_valu;
}