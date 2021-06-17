#include "commo_header.h"

#include "mstri_utili.h"
#include "mfile_utili.h"

#include "rstat_bzl.h"
#include "invo_bzl.h"
#include "hand_obje.h"
#include "hand_bzl.h"
#include "conoda.h"

/*
int handbzl_create(char *data_directory) {
    strcpy(_hand_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int handbzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

#define CLANG_SUFFIX ".c"
#define OBJEC_SUFFIX ".so"

// method class

int hcrea_metho_bzl(prod_data *sresp, hand_data *hando, hand_data *handa, char *clang_txt, char *osdb, char *meth_txt) {
    char clasn[CLASS_LENGTH];
    char metnm[METH_LENGTH];
    //
    if (!split_space_ex(clasn, metnm, meth_txt)) return -1;
    char handn[HAND_LENGTH];
    char mepan[HAND_LENGTH];
    build_handle_bzl(handn, mepan, meth_txt);
    char clan_path[MAX_PATH];
    char obje_path[MAX_PATH];
    CREAT_TEMPO_FILE(clan_path, osdb, handn, CLANG_SUFFIX)
    CREAT_OBJECT_FILE(obje_path, osdb, handn, OBJEC_SUFFIX)
            //
    if (save_clang_file(clan_path, clang_txt)) return -1;
    if (compi_clang_file(obje_path, clan_path, sresp->sebuf)) {
        (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
        return -1;
    }
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    if (open_meth_hand(hando, handa, clasn, obje_path, handn))
        return -1;
    //
    BUILD_OBJECT_NAME(obje_path, handn, OBJEC_SUFFIX)
    open_oattr(clasn, mepan, obje_path, osdb);
    //
    return 0x00;
}

int hcrea_class_bzl(prod_data *sresp, hand_data *handa, char *clang_txt, char *osdb, char *clas_decl) {
    char clasn[CLASS_LENGTH];
    if (!split_clame(clasn, clas_decl)) return -1;
    // 
    char clan_path[MAX_PATH];
    char obje_path[MAX_PATH];
    CREAT_TEMPO_FILE(clan_path, osdb, clasn, CLANG_SUFFIX)
    CREAT_OBJECT_FILE(obje_path, osdb, clasn, OBJEC_SUFFIX)
    if (save_clang_file(clan_path, clang_txt)) return -1;
    if (compi_clang_file(obje_path, clan_path, sresp->sebuf)) {
        (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
        return -1;
    }
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    if (open_data_hand(handa, obje_path, clasn)) return -1;
    //
    BUILD_OBJECT_NAME(obje_path, clasn, OBJEC_SUFFIX)
    open_dattr(clasn, obje_path, osdb);
    //
    return 0x00;
}

//

int hdrop_metho_bzl() {

    //
    return 0x00;
}

int hdrop_class_bzl() {

    //
    return 0x00;
}

//

int hand_load_metho(prod_data *sresp, hand_data *hando, hand_data *handa, char *clang_txt, char *osdb, char *clasn_metn) {
    char clasn[CLASS_LENGTH];
    char metnm[METH_LENGTH];
    char handn[HAND_LENGTH];
    //
    split_space(handn, metnm, clasn_metn);
    // build_handle_bzl(handn, meth_txt);
    char clan_path[MAX_PATH];
    char obje_path[MAX_PATH];
    CREAT_TEMPO_FILE(clan_path, osdb, handn, CLANG_SUFFIX)
    CREAT_OBJECT_FILE(obje_path, osdb, handn, OBJEC_SUFFIX)
    if (save_clang_file(clan_path, clang_txt)) return -1;
    if (compi_clang_file(obje_path, clan_path, sresp->sebuf)) {
        (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
        return -1;
    }
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    //
    if (open_meth_hand(hando, handa, clasn, obje_path, clasn_metn))
        return -1;
    // dele_meth_hand();
    //
    return 0x00;
}

int hand_load_class(prod_data *sresp, hand_data *handa, char *clang_txt, char *osdb, char *clasn) {
    char clan_path[MAX_PATH];
    char obje_path[MAX_PATH];
    CREAT_TEMPO_FILE(clan_path, osdb, clasn, CLANG_SUFFIX)
    CREAT_OBJECT_FILE(obje_path, osdb, clasn, OBJEC_SUFFIX)
    if (save_clang_file(clan_path, clang_txt))return -1;
    if (compi_clang_file(obje_path, clan_path, sresp->sebuf)) {
        (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
        return -1;
    }
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
    if (open_data_hand(handa, obje_path, clasn)) return -1;
    //
    return 0x00;
}

static int hand_load_oattr(hand_data *hando, hand_data *handa, oconte *ocont, char *osdb) {
    char handn[HAND_LENGTH];
    char obje_path[MAX_PATH];
    //
    CREAT_OBJECT_PATH(obje_path, osdb, ocont->library)
    BUILD_HANDLE_NAME(handn, ocont->clasn, ocont->mepan)
    _LOG_DEBUG("hand_load_oattr, clasn:%s handn:%s", ocont->clasn, handn);
    if (open_meth_hand(hando, handa, ocont->clasn, obje_path, handn))
        return -1;
    _LOG_DEBUG("hand_load_oattr, hando:%08X obje_path:%s", hando, obje_path);
    //
    return 0x00;
}

//

static int hand_load_dattr(hand_data *handa, dconte *dcont, char *osdb) {
    char obje_path[MAX_PATH];
    //
    CREAT_OBJECT_PATH(obje_path, osdb, dcont->library)
    _LOG_DEBUG("hand_load_dattr, clasn:%s", dcont->clasn);
    if (open_data_hand(handa, obje_path, dcont->clasn)) return -1;
    _LOG_DEBUG("hand_load_dattr, hando:%08X obje_path:%s", handa, obje_path);
    //
    return 0x00;
}

// osdb

int hload_odata_bzl(struct cono_list *clist) {
    dconte dcont;
    oconte ocont;
    unsigned int ainde;
    struct cono_list *clistmp;
    //
    for (clistmp = clist; clistmp; clistmp = clistmp->next) {
        _LOG_DEBUG("hload_odata_bzl:%s", clistmp->_osdb_);
        ainde = open_dconte(&dcont, clistmp->_osdb_);
        while (INVA_INDE_VALU != ainde) {
            ainde = read_dattr(&dcont, ainde);
            hand_load_dattr(&clistmp->cono_valu.handa, &dcont, clistmp->_osdb_);
        }
        close_dconte(&dcont);
        //
        ainde = open_oconte(&ocont, clistmp->_osdb_);
        while (INVA_INDE_VALU != ainde) {
            ainde = read_oattr(&ocont, ainde);
            hand_load_oattr(&clistmp->cono_valu.hando, &clistmp->cono_valu.handa, &ocont, clistmp->_osdb_);
        }
        close_oconte(&ocont);
    }
    //
    return 0x00;
}

int open_odata_bzl(conoda *coval, char *osdb) {
    dconte dcont;
    oconte ocont;
    unsigned int ainde;
    _LOG_DEBUG("open_odata_bzl:%s", osdb);
    //
    ainde = open_dconte(&dcont, osdb);
    while (INVA_INDE_VALU != ainde) {
        ainde = read_dattr(&dcont, ainde);
        hand_load_dattr(&coval->handa, &dcont, osdb);
    }
    close_dconte(&dcont);
    //
    ainde = open_oconte(&ocont, osdb);
    while (INVA_INDE_VALU != ainde) {
        ainde = read_oattr(&ocont, ainde);
        hand_load_oattr(&coval->hando, &coval->handa, &ocont, osdb);
    }
    close_oconte(&ocont);
    //
    return 0x00;
}

//

int close_odata_bzl(conoda *coval, char *osdb) {
    //
    return 0x00;
}