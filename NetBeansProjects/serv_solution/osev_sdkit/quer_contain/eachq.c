#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opera_utili.h"
#include "astri_utili.h"
#include "cstri_utili.h"
#include "dyli_list.h"
#include "eachq.h"

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
    osv_oid_i obje_oid;
    union _retype_ retype;
} retval;
#pragma pack()

// static int type_len[0x07] = {0, 1, 1, 2, 2, 4, 4, 8, 8, 8, 8, 8, 8};
static int type_len[13] = {12, 13, 13, 14, 14, 16, 16, 20, 20, 20, 20, 20, 20};

// fix me, 20170412
// predicate find / condition

static int condi_contae(prod_data *sresp, riv_curso_t *curso, rive_ha *stora_ha, dyli_meth *dlmep, char *clasn, char *para_str) {
    // dyli_data *dldap = dlmep->dldat;
    printf("predica contao, dlmep->retype:%d\n", dlmep->retype);
    //
    return 0x00;
}

//

static int objeid_contae(prod_data *sresp, riv_curso_t *curso, rive_ha *stora_ha, dyli_meth *dlmep, char *para_str) {
    dyli_data *dldap = dlmep->dldat;
    osv_oid_i obje_oid;
    printf("objeid contao, dlmep->retype:%d\n", dlmep->retype);
    //
    stroid((osv_oid_t *) & obje_oid, para_str);
    stora_ha->set_key(curso, obje_oid.stoid);
    if (0x00 != stora_ha->sear_curso(curso)) return -1;
    //
    retval rvalu;
    mapid_unique((osv_oid_t *) & rvalu.obje_oid);
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) return -1;
    dldap->solve(obje_data, curso);
    rvalu.obje_oid.stoid = ((osv_oid_i *) obje_data)->stoid;
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
    return 0x00;
}

//

static int traver_contae(prod_data *sresp, riv_curso_t *curso, rive_ha *stora_ha, dyli_meth *dlmep) {
    dyli_data *dldap = dlmep->dldat;
    printf("traver contao, dlmep->retype:%d\n", dlmep->retype);
    //
    retval rvalu;
    mapid_unique((osv_oid_t *) & rvalu.obje_oid);
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) return -1;
    int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(curso); inde++) {
        dldap->solve(obje_data, curso);
        rvalu.obje_oid.stoid = ((osv_oid_i *) obje_data)->stoid;
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
    return 0x00;
}

//

static int decode_invok_paras(char *clasn, char *metnm, char *each_line, char *paras[PARAM_NUMB], char *invop_str) {
    char para_str[PARAM_LENGTH];
    if (!split_qeach(clasn, metnm, para_str, invop_str)) return -1;
    qeach_paras(each_line, paras, para_str);
    printf("clasn:%s metnm:%s para_str:%s\n", clasn, metnm, para_str);
    printf("paras[0x00]:%s paras[0x01]:%s\n", paras[0x00], paras[0x01]);
    //
    return 0x00;
}

int each_conta_obje(prod_data *sresp, riv_curso_t *curso, rive_ha *stora_ha, hand_data *hando, char *clasn, char **paras) {
    _LOG_DEBUG("cuo clasn:|%s|", clasn);
    _LOG_DEBUG("paras[0x00]:|%s| paras[0x01]:|%s|", paras[0x00], paras[0x01]);
    //
    char each_clasn[CLASS_LENGTH];
    char each_metn[METH_LENGTH];
    char each_line[LINE_LENGTH];
    char *eparas[PARAM_NUMB];
    //
    decode_invok_paras(each_clasn, each_metn, each_line, eparas, paras[0x00]);
    if (strcmp(clasn, each_clasn)) return -1;
    //    
    char handn[HAND_LENGTH];
    if (!build_query_handn(handn, each_clasn, each_metn, eparas)) return -1;
    _LOG_DEBUG("cuo handn:|%s| clasn:|%s|", handn, clasn);
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
                each_valu = objeid_contae(sresp, curso, stora_ha, dlmep, paras[0x01]);
                break;
            case PREDI_TYPE_CONDI:
                each_valu = condi_contae(sresp, curso, stora_ha, dlmep, clasn, paras[0x01]);
                break;
            case PREDI_TYPE_TRAVE:
                each_valu = traver_contae(sresp, curso, stora_ha, dlmep);
                break;
            case PREDI_TYPE_EXCEP:
                break;
        }
    } else each_valu = traver_contae(sresp, curso, stora_ha, dlmep);
    //
    return each_valu;
}
