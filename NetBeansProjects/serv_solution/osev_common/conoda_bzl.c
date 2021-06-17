
#include "commo_macro.h"
#include "hash_table_ex.h"

#include "rive_bzl.h"
#include "hand_bzl.h"
#include "rstat_bzl.h"
#include "quer_bzl.h"

#include "cona_list.h"
#include "dyli_list.h"
#include "conoda_bzl.h"
#include "authen_bzl.h"

//

static int init_conta_list(struct cono_list **clsth, char **osds_arra) {
    struct cono_list *clistmp;
    char **osdn = osds_arra;
    //
    for (; *osdn; osdn++) {
        clistmp = appe_clist_new(clsth);
        strcpy(clistmp->cono_valu.osdb_name, *osdn);
        if (attri_osdb_bzl(&clistmp->cono_valu.oid, *osdn)) {
            close_clist(&_conta_list_, clistmp);
            continue;
        }
        clistmp->cono_valu.leve_mask = reset_privalu_bzl(&clistmp->cono_valu.oid, *osdn);
        if (!clistmp->cono_valu.leve_mask) {
            close_clist(&_conta_list_, clistmp);
            continue;
        }
        clistmp->cono_valu.handa.ocuse_hm = create_action(free_dyme, ODATA_BACKET_SIZE);
        clistmp->cono_valu.hando.ocuse_hm = create_action(free_dyme, ODATA_BACKET_SIZE);
        clistmp->cono_valu.conda.contn_hm = create_action(cona_free, CONTA_BACKET_SIZE);
        clistmp->cono_valu.conda.conto_hm = creat_oid_hm(CONTA_BACKET_SIZE);
    }
    //
    return 0x00;
}

//

int rive_init_conn(struct cono_list *clist) {
    struct cono_list *clistmp;
    for (clistmp = clist; clistmp; clistmp = clistmp->next) {
        if (open_rive_bzl(clistmp->cono_valu.rvcon, clistmp->_osdb_))
            return -1;
        _LOG_INFO("rive_init_conn:%s", clistmp->_osdb_);
    }
    //
    return 0x00;
}

//

int conbzl_create() {
    char osds_line[LARGE_TEXT_SIZE];
    char *osds_arra[MAX_OSDB_NUMB];
    printf("conbzl create strat!\n");
    //
    if (opened_osdb_bzl(osds_line, osds_arra)) {
        printf("opened_osdb_bzl error!\n");
        return ERR_FAULT;
    }
    //
    if (init_conta_list(&_conta_list_, osds_arra)) {
        printf("init_conta_list error!\n");
        return ERR_FAULT;
    }
    if (rive_init_conn(_conta_list_)) {
        printf("rive_init_conn error!\n");
        return ERR_FAULT;
    }
    if (hload_odata_bzl(_conta_list_)) {
        printf("hload_odata_bzl error!\n");
        return ERR_FAULT;
    }
    if (qload_conta_bzl(_conta_list_)) { // fix me 20161716
        printf("qload_conta_bzl error!\n");
        return ERR_FAULT;
    }
    //
    printf("conbzl create end!\n");
    return 0x00;
}

int conbzl_destroy() {
    char osds_line[LARGE_TEXT_SIZE];
    char *osds_arra[MAX_OSDB_NUMB];
    printf("conbzl destroy strat!\n");
    //
    if (opened_osdb_bzl(osds_line, osds_arra)) return -1;
    //
    // if (qunlo_conta_bzl(_conta_list_)) return -1; // fix me 20161716
    // if (hunlo_odata_bzl(_conta_list_)) return -1;
    // if (rive_final_conn(_conta_list_)) return -1;
    // if (final_conta_list(&_conta_list_, osds_arra)) return -1;
    //
    printf("conbzl destroy end!\n");
    return 0x00;
}

//

struct cono_list *open_clist_bzl(char *osdb, uint32 leve_mask) {
    struct cono_list *clistmp = appe_clist_new(&_conta_list_);
    strcpy(clistmp->cono_valu.osdb_name, osdb);
    if (attri_osdb_bzl(&clistmp->cono_valu.oid, osdb)) {
        close_clist(&_conta_list_, clistmp);
        return NULL;
    }
    clistmp->cono_valu.leve_mask = leve_mask;
    if (!clistmp->cono_valu.leve_mask) {
        close_clist(&_conta_list_, clistmp);
        return NULL;
    }
    //
    clistmp->cono_valu.handa.ocuse_hm = create_action(free_dyme, ODATA_BACKET_SIZE);
    clistmp->cono_valu.hando.ocuse_hm = create_action(free_dyme, ODATA_BACKET_SIZE);
    clistmp->cono_valu.conda.contn_hm = create_action(cona_free, CONTA_BACKET_SIZE);
    clistmp->cono_valu.conda.conto_hm = creat_oid_hm(CONTA_BACKET_SIZE);
    //
    return clistmp;
}

//
