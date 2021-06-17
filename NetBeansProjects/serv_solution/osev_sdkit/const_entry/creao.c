
#include <ctype.h>

#include "estr_utili.h"
#include "creao.h"
#include "conoda.h"
#include "dyli_list.h"

//
/*
     dyli_meth {
        char metnm[METH_LENGTH];
        void *lib_hand;
        //
        void *obje_data;
        int (*parser)(char **);
        void (*method)(void *);
        void (*create)(void *);
    };
 */

// cursor->set_key(cursor, ); /* Insert a record. */
// cursor->set_value(cursor, "value1"); // fix me 20170210
// -1:error 0x00:ok 0x01:exception

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

int creat_entity_obje(riv_curso_t *curso, rive_ha *stora_ha, hand_data *hando, char *clasn, char **paras) {
    char handn[HAND_LENGTH];
    if (!build_const_handn(handn, clasn, paras)) return -1;
    _LOG_DEBUG("creat_eobje_echo handn:|%s| clasn:|%s|", handn, clasn);
    //
    dyli_meth *dlmep = (dyli_meth *) action_value(handn, hando->ocuse_hm);
    if (!dlmep) {
        _LOG_DEBUG("dlmep:%lld ocuse_hm:%lld", (long long) dlmep, (long long) hando->ocuse_hm);
        return -1;
    }
    dyli_data *dldap = dlmep->dldat;
    //
    void *obje_data = (void *) malloc(dldap->data_size);
    if (!obje_data) return -1;
    creat_objeid_obj((osv_oid_t *) obje_data);
    // printf("paras, [0]:|%d| [1]:|%d|\n", *((int *) (paras[0x00] + 0x01)), ((int *) (paras[0x01] + 0x01))[0x00]);
    dlmep->parser(paras);
    int crea_valu = dlmep->method.meth_int(obje_data);
    if (!crea_valu) {
        print_test((struct test *) obje_data);
        printf("dldap->bound:%08X\n", dldap->bound);
        dldap->bound(curso, obje_data);
        crea_valu = stora_ha->inser_curso(curso);
    }
    //
    free(obje_data);
    return crea_valu;
}

int creat_eobje_echo(hand_data *hando, char *clasn, char **paras) {
    char handn[HAND_LENGTH];
    if (!build_const_handn(handn, clasn, paras)) return -1;
    printf("creat_eobje_echo handn:|%s|\n", handn);
    //
    dyli_meth *dlmep = (dyli_meth *) action_value(handn, hando->ocuse_hm);
    if (!dlmep) return -1;
    //
    return 0x00;
}



