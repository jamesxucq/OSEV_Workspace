
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opera_utili.h"
#include "astri_utili.h"
#include "facto.h"
#include "dyli_list.h"

// fix me, 20170412
// predicate facto / condition

static int condi_contaq(prod_data *sresp, rive_ha *stora_ha, dyli_data *dldap, char *clasn, char *source_str, char *obje_iden) {
    printf("condi_contaq_cla, dldap->data_size:%d\n", dldap->data_size);
    int facto_valu = 0x00;
    //
    return facto_valu;
}

//

static int objeid_contaq(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *source_str, char *obje_iden) {
    printf("objeid_contaq_cla, dldap->data_size:%d\n", dldap->data_size);
    //
    riv_curso_t *curso;
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne);
    if (stora_ha->open_table(&curso, slist->seion, source_str, NULL)) {
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    //
    osv_oid_i obje_oid;
    //
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
    //facto object error!
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) {
        stora_ha->close_curso(curso);
        quiet_seion_bzl(&rvcon->slist, slist);
        return -1;
    }
    dldap->solve(obje_data, curso);
    creat_objeid_obj((osv_oid_t *) obje_data);
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
    free(obje_data);
    return 0x00;
}

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

static int traver_contaq(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, dyli_data *dldap, char *source_str) {
    printf("traver_contaq_cla, dldap->data_size:%d\n", dldap->data_size);
    int snumb = query_source_numb(source_str);
    if (0x01 == snumb) {
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
            creat_objeid_obj((osv_oid_t *) obje_data);
            print_test((struct test *) obje_data);
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
        free(obje_data);
    }
    //
    return 0x00;
}

// odb:factory("clasn", "conobje", "obje:numb() > 0x00");
// :factory("clasn", conobje", "obje:numb() > 0x00");
// :factory("clasn", conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:factory("clasn", "conobje");

int facto_class_obje(prod_data *sresp, rive_conne *rvcon, rive_ha *stora_ha, hand_data *handa, char **paras) {
    _LOG_DEBUG("facto_class_obje clasn:|%s|", paras[0x00]);
    dyli_data *dldap = (dyli_data *) action_value(paras[0x00], handa->ocuse_hm);
    if (!dldap) {
        _LOG_DEBUG("doh dldap:%lld ocuse_hm:%lld", (long long) dldap, (long long) handa->ocuse_hm);
        return -1;
    }
    // 
    int facto_valu = -1;
    if (paras[0x02]) {
        switch (check_predi_type(paras[0x02])) {
            case PREDI_TYPE_OBJID:
                facto_valu = objeid_contaq(sresp, rvcon, stora_ha, dldap, paras[0x01], paras[0x02]);
                break;
            case PREDI_TYPE_CONDI:
                facto_valu = condi_contaq(sresp, stora_ha, dldap, paras[0x00], paras[0x01], paras[0x02]);
                break;
            case PREDI_TYPE_TRAVE:
                facto_valu = traver_contaq(sresp, rvcon, stora_ha, dldap, paras[0x01]);
                break;
            default:
                break;
        }
    } else facto_valu = traver_contaq(sresp, rvcon, stora_ha, dldap, paras[0x01]);
    //
    return facto_valu;
}

//
