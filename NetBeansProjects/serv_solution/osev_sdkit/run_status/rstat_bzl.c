#include "commo_header.h"
#include "third_party.h"

#include "rstr_utili.h"
#include "stat_utili.h"
#include "hand_bzl.h"
#include "quer_bzl.h"
#include "recurs_data.h"
#include "conve_rstat.h"
#include "conoda_bzl.h"
#include "authen_bzl.h"
#include "rive_bzl.h"

//
#include "rstat_obje.h"
#include "rstat_bzl.h"


/*
int rstabzl_create(char *data_directory) {
    strcpy(_rsta_data_directory_, data_directory);
    return 0x00; //succ
}
int rstabzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

//
#define EXCEP_RETU(CLIST, REVAL) { \
    close_clist_bzl(CLIST); \
    return REVAL; \
}

//

int open_osev_bzl(osv_oid_t *oid, char *osdb, uint32 leve_mask) {
    printf("open_osev_bzl:%s\n", osdb);
    int exist = check_osdb_exist(osdb);
    switch (exist) {
        case OSDB_OPENED:
            _LOG_DEBUG("odb opened:%s", osdb);
            if (find_osdb_attri(oid, osdb)) return -1;
            break;
        case OSDB_NOEXIS:
            _LOG_DEBUG("odb not exist, creat:%s", osdb);
            if (creat_osdb_conte(osdb)) return -1;
            creat_hattr_bzl(osdb)
            creat_cattr_bzl(osdb);
        case OSDB_EXISTS:
            _LOG_DEBUG("odb open:%s", osdb);
            struct cono_list *clistmp = open_clist_bzl(osdb, leve_mask);
            if (!clistmp) return -1;
            if (reset_privile_bzl(&clistmp->cono_valu.oid, leve_mask)) EXCEP_RETU(clistmp, -1)
                memcpy(oid, &clistmp->cono_valu.oid, sizeof (osv_oid_t));
            if (open_rive_bzl(clistmp->cono_valu.rvcon, osdb)) EXCEP_RETU(clistmp, -1)
                if (open_odata_bzl(&clistmp->cono_valu, osdb)) EXCEP_RETU(clistmp, -1)
                    //
                    if (open_osdb_flag(osdb, clistmp->cono_valu.leve_mask)) EXCEP_RETU(clistmp, -1)
                        break;
        default:
            _LOG_DEBUG("open_osev_bzl excep!");
            return -1;
            break;
    }
    //
    return 0x00;
}

//

int close_osev_bzl(char *osdb) {
    printf("close_osev_bzl:%s\n", osdb);
    struct cono_list *clistmp = find_clstn_bzl(osdb);
    if (!clistmp) return -1;
    if (close_osdb_flag(osdb)) return -1;
    //
    if (close_rive_bzl(clistmp->cono_valu.rvcon)) return -1;
    if (close_odata_bzl(&clistmp->cono_valu, osdb)) return -1;
    close_clist_bzl(clistmp);
    //
    if (!valid_osdb_clean(osdb)) {
        printf("odb is clean, drop %s.\n", osdb);
        if (drop_osdb_conte(osdb)) return -1;
    }
    //
    return 0x00;
}

//

int open_osdb_bzl(osv_oid_t *oid, uint32 leve_mask) {
    char temp[33];
    printf("open_osdb_bzl:|%s|\n", oidstr(temp, oid));
    char osdb[OSDB_LENGTH]; // odb name
    if (find_osdb_oid(osdb, oid)) return -1;
    //
    int exist = check_osdb_exist(osdb);
    switch (exist) {
        case OSDB_OPENED:
            _LOG_DEBUG("odb opened:%s", osdb);
            break;
        case OSDB_NOEXIS:
            _LOG_DEBUG("odb %s not exist!", osdb);
            return -1;
            break;
        case OSDB_EXISTS:
            _LOG_DEBUG("odb open:%s", osdb);
            struct cono_list *clistmp = open_clist_bzl(osdb, leve_mask);
            if (!clistmp) return -1;
            if (reset_privile_bzl(&clistmp->cono_valu.oid, leve_mask)) EXCEP_RETU(clistmp, -1)
                memcpy(oid, &clistmp->cono_valu.oid, sizeof (osv_oid_t));
            if (open_rive_bzl(clistmp->cono_valu.rvcon, osdb)) EXCEP_RETU(clistmp, -1)
                if (open_odata_bzl(&clistmp->cono_valu, osdb)) EXCEP_RETU(clistmp, -1)
                    if (open_osdb_flag(osdb, clistmp->cono_valu.leve_mask)) EXCEP_RETU(clistmp, -1)
                        break;
        default:
            _LOG_DEBUG("open_osdb_bzl excep!");
            return -1;
            break;
    }
    //
    return 0x00;
}

//

int close_osdb_bzl(osv_oid_t *oid) {
    char temp[33];
    printf("close_osdb_bzl:|%s|\n", oidstr(temp, oid));
    struct cono_list *clistmp = find_clsto_bzl(oid);
    if (!clistmp) return -1;
    if (close_osdb_flag(clistmp->_osdb_)) return -1;
    //
    if (close_rive_bzl(clistmp->cono_valu.rvcon)) return -1;
    if (close_odata_bzl(&clistmp->cono_valu, clistmp->_osdb_)) return -1;
    close_clist_bzl(clistmp);
    //
    return 0x00;
}

//

int echo_osev_bzl(prod_data *sresp) {
    osv_oid_t osev_oid;
    creat_objeid_osev(&osev_oid);
    memcpy(sresp->sebuf, &osev_oid, sizeof (osv_oid_t));
    (sresp->colen)[0x00] = sizeof (osv_oid_t);
    return 0x00;
}

//

int echo_osdb_bzl(prod_data *sresp, char *osdb) {
    printf("echo_osdb_bzl:%s\n", osdb);
    osv_oid_t osdb_oid;
    if (strcmp(OSDB_DEFAULT_VALUE, osdb)) {
        if (OSDB_NOEXIS == check_osdb_exist(osdb)) return -1;
        if (find_osdb_attri(&osdb_oid, osdb)) return -1;
    } else creat_objeid_osdb(&osdb_oid);
    memcpy(sresp->sebuf, &osdb_oid, sizeof (osv_oid_t));
    (sresp->colen)[0x00] = sizeof (osv_oid_t);
    //
    return 0x00;
}

//

int ostati_osdb_bzl(prod_data *sresp) {
    printf("osev_statu_bzl\n");
    strcpy((char *) sresp->sebuf, "osdb stati.");
    //
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    return 0x00;
}

int dstati_osdb_bzl(prod_data *sresp, osv_oid_t *oid) {
    printf("echo_osdb_bzl.\n");
    if (CMPOID_OSDB(oid)) {
        char osds_line[LARGE_TEXT_SIZE];
        char *osds_arra[MAX_OSDB_NUMB];
        if (list_osdb(osds_line, osds_arra, _COMMO_DIRECTORY_)) return -1;
        conve_osdb_all(sresp, osds_arra);
    } else {
        char osdb[OSDB_LENGTH];
        if (find_osdb_oid(osdb, oid)) return -1;
        conve_osdb_name(sresp, osdb);
    }
    //
    return 0x00;
}

//

int opened_osdb_bzl(char *osds_text, char **osds_open) {
    _LOG_TRACE("opened_osdb_bzl");
    char osds_line[LARGE_TEXT_SIZE];
    char *osds_arra[MAX_OSDB_NUMB];
    if (list_osdb(osds_line, osds_arra, _COMMO_DIRECTORY_)) return -1;
    //
    char *last_str = osds_text;
    char **osdb_open = osds_open;
    char **osdn = osds_arra;
    for (; osdn[0x00]; osdn++) {
        if (!valid_osdb_opened(osdn[0x00])) {
            lscpy_o(*osdb_open, osdn[0x00], last_str)
            osdb_open++;
        }
    }
    //
    return 0x00;
}

//

int set_oleve_bzl(char *osdb, uint32 leve_mask) {
    _LOG_DEBUG("set oleve bzl");
    struct cono_list *clistmp = find_clstn_bzl(osdb);
    if (!clistmp) return -1;
    if (reset_privile_bzl(clistmp->_oid_, leve_mask)) return -1;
    if (open_osdb_flag(osdb, leve_mask)) return -1;
    //
    return 0x00;
}

int set_dleve_bzl(osv_oid_t *oid, uint32 leve_mask) {
    _LOG_DEBUG("set dleve bzl");
    struct cono_list *clistmp = find_clsto_bzl(oid);
    if (!clistmp) return -1;
    if (reset_privile_bzl(oid, leve_mask)) return -1;
    if (open_osdb_flag(clistmp->_osdb_, leve_mask)) return -1;
    //
    return 0x00;
}