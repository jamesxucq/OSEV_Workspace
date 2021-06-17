
#include "conoda_bzl.h"
#include "quer_bzl.h"
#include "priv_utili.h"

// ENGINE_WTIGER;

struct priv_cont _priv_data_[] = {
    {AUTH_ROLES_CONT, DEFA_ROLE_CLAS},
    {AUTH_OUSER_CONT, DEFA_USER_CLAS},
    {AUTH_CUSER_CONT, DEFA_USER_CLAS},
    {NULL, NULL}
};

//

int check_priv_data(cont_data *conda, struct priv_cont *priv_data) {
    contain *conta;
    struct priv_cont *prico = priv_data;
    for (; prico->cont_name && prico->clas_type; prico++) {
        conta = (contain *) action_value(prico->cont_name, conda->contn_hm);
        if (!conta) return -1;
        if (strcmp(prico->clas_type, conta->data_type)) return -1;
    }
    //
    return 0x00;
}

//

/*
static void print_test(struct test *obje) {
    char oid_stri[OID_LINE_LEN];
    oidstr(oid_stri, (osv_oid_t *) & obje->obje_oid);
    printf("|%s|%d|%d|%d|\n", oid_stri, obje->xx, obje->ax, obje->cx);
}
 */

#define OSEV_LIVE_INIT(COVALU, CONTA_NAME) \
    contain *conta = (contain *) action_value(CONTA_NAME, COVALU->conda.contn_hm); \
    if (!conta) return -1; \
    dyli_data *dldap = (dyli_data *) action_value(conta->data_type, COVALU->handa.ocuse_hm); \
    if (!dldap) return -1; \
    rive_conne *rvcon = COVALU->rvcon + conta->stora_ha->storage_type; \
    rive_ha *stora_ha = conta->stora_ha; \
    riv_curso_t *curso; \
    seio_list *slist = activ_seion_bzl(&rvcon->slist, stora_ha, rvcon->conne); \
    if (stora_ha->open_table(&curso, slist->seion, CONTA_NAME, NULL)) { \
        quiet_seion_bzl(&rvcon->slist, slist); \
        return -1; \
    }

#define OSEV_LIVE_FINA     stora_ha->close_curso(curso); \
    quiet_seion_bzl(&rvcon->slist, slist);

//

int live_recu_load(struct liv_list **llsth, conoda *coval, char *contn) {
    OSEV_LIVE_INIT(coval, contn)
    printf("load contn:%s, dldap->data_size:%d\n", contn, dldap->data_size);
    printf("dldap->clasn:%s\n", dldap->clasn);
    //
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) {
        OSEV_LIVE_FINA
        return -1;
    }
    mapid_unique((osv_oid_t *) obje_data);
    while (0x00 == stora_ha->next_curso(curso)) {
        dldap->solve(obje_data, curso);
        if (!appe_live_list(llsth, obje_data, dldap->data_size)) {
            free(obje_data);
            OSEV_LIVE_FINA
            return -1;
        }
        // log_binary_file(obje_data, dldap->data_size, "./binary_code.bin_f");
    }
    //
    free(obje_data);
    OSEV_LIVE_FINA
    return 0x00;
}

//

int live_insert(conoda *coval, char *contn, void *data) {
    OSEV_LIVE_INIT(coval, contn)
    printf("objeid_contaq_cla, dldap->data_size:%d\n", dldap->data_size);
    //
    // log_binary_file(data, dldap->data_size, "./binary_code.bin_bound");
    dldap->bound(curso, data);
    if (0x00 != stora_ha->inser_curso(curso)) {
        OSEV_LIVE_FINA
        return -1;
    }
    //
    OSEV_LIVE_FINA
    return 0x00;
}

//

int live_load(void *data, conoda *coval, char *contn, osv_oid_t *oid) {
    OSEV_LIVE_INIT(coval, contn)
    printf("objeid_contaq_cla, dldap->data_size:%d\n", dldap->data_size);
    //
    stora_ha->set_key(curso, ((osv_oid_i *) oid)->stoid);
    if (0x00 != stora_ha->sear_curso(curso)) {
        // printf("ret:%d\n", ret);
        OSEV_LIVE_FINA
        return -1;
    }
    mapid_unique((osv_oid_t *) data);
    dldap->solve(data, curso);
    // log_binary_file(data, dldap->data_size, "./binary_code.bin_solve");
    //
    OSEV_LIVE_FINA
    return 0x00;
}

int live_save(conoda *coval, char *contn, void *data, osv_oid_t *oid) {
    OSEV_LIVE_INIT(coval, contn)
    printf("objeid_contaq_cla, dldap->data_size:%d\n", dldap->data_size);
    char oid_stri[OID_LINE_LEN];
    printf("|%s|\n", oidstr(oid_stri, oid));
    //
    stora_ha->set_key(curso, ((osv_oid_i*) oid)->stoid);
    dldap->bound(curso, data);
    if (0x00 != stora_ha->update_curso(curso)) {
        OSEV_LIVE_FINA
        return -1;
    }
    //
    OSEV_LIVE_FINA
    return 0x00;
}

int live_remove(conoda *coval, char *contn, osv_oid_t *oid) {
    OSEV_LIVE_INIT(coval, contn)
    printf("objeid_contaq_cla, dldap->data_size:%d\n", dldap->data_size);
    char oid_stri[OID_LINE_LEN];
    printf("|%s|\n", oidstr(oid_stri, oid));
    //
    stora_ha->set_key(curso, ((osv_oid_i*) oid)->stoid);
    if (0x00 != stora_ha->remove_curso(curso)) {
        OSEV_LIVE_FINA
        return -1;
    }
    //
    OSEV_LIVE_FINA
    return 0x00;
}