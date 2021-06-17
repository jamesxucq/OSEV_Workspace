
#include "ostri_utili.h"
#include "clas_list.h"
#include "clas_save.h"
#include "clas_load.h"
#include "conve.h"

#include "conv_utili.h"
#include "echo_clang.h"
#include "invo_bzl.h"

//
/*
int compbzl_create(char *data_directory) {
    strcpy(_comp_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int compbzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */
//
#define RETU_DELE(CLAA, CLAM, RET_VAL) { \
        CLAA_STRU_DELE(CLAA) \
        CLAM_STRU_DELE(CLAM) \
        return RET_VAL; \
    }

#define RETU_DELA(CLAA, RET_VAL) { \
        CLAA_STRU_DELE(CLAA) \
        return RET_VAL; \
    }

#define RETU_DELM(CLAM, RET_VAL) { \
        CLAM_STRU_DELE(CLAM) \
        return RET_VAL; \
    }

//

int list_metho_bzl(prod_data *sresp, char *osdb, char *metho) {
    char clasn[CLASS_LENGTH];
    char metnm[METH_LENGTH];
    if (!split_space(clasn, metnm, metho)) return -1;
    char clas_path[MAX_PATH];
    //
    clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELM(clasm, -1)
        list_meth_conte(sresp, metnm, &clasm);
    //
    CLAM_STRU_DELE(clasm)
    return 0x00;
}

//
#define LIST_CLAS_OBJID 0x0001
#define LIST_CLAS_ATTRIB 0x0002
#define LIST_CLAS_INHERIT 0x0004
#define LIST_CLAS_CONTEN 0x0008

#define RESET_PROD_DATA(SRESP)  (SRESP->colen)[0x00] = 0x00;

int list_class_bzl(prod_data *sresp, char *osdb, char *clasn, uint32 etype) {
    char clas_path[MAX_PATH];
    printf("clasn:|%s| etype:|%08X|\n", clasn, etype);
    RESET_PROD_DATA(sresp)
    if ((LIST_CLAS_OBJID | LIST_CLAS_ATTRIB | LIST_CLAS_INHERIT) & etype) {
        char clas_oain[LARGE_TEXT_SIZE];
        CREAT_CLATT_FILE(clas_path, osdb, clasn)
        printf("clas_path:|%s|\n", clas_path);
        if (LIST_CLAS_OBJID & etype) {
            if (!find_class_objid(clas_oain, clas_path)) return -1;
            printf("clas_oain:|%s|\n", clas_oain);
            echo_class_objid(sresp, clas_oain);
        }
        if (LIST_CLAS_ATTRIB & etype) {
            if (!find_class_attri(clas_oain, clas_path)) return -1;
            echo_class_attri(sresp, clas_oain);
        }
        if (LIST_CLAS_INHERIT & etype) {
            if (!find_class_inheri(clas_oain, clas_path)) return -1;
            echo_class_inheri(sresp, clas_oain);
        }
    }
    //
    if (LIST_CLAS_CONTEN & etype) {
        clas_meta clasm;
        memset(&clasm, '\0', sizeof (clas_meta));
        CREAT_CLASS_FILE(clas_path, osdb, clasn)
        printf("clas_path:%s\n", clas_path);
        if (!parse_class_conte(&clasm, clas_path)) RETU_DELM(clasm, -1)
            echo_class_meta(sresp, &clasm);
        CLAM_STRU_DELE(clasm)
    }
    //
    return 0x00;
}

//

int list_clasd_bzl(char *clas_decl, char *osdb, char *clasn) {
    char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    printf("clas_path:%s\n", clas_path);
    if (!parse_class_decla(clas_decl, clas_path)) return -1;
    //
    return 0x00;
}

//

int dele_metho_bzl(char *osdb, char *methd) {
    char clasn[CLASS_LENGTH], metnm[METH_LENGTH];
    char *paras = split_space_ex(clasn, metnm, methd);
    if (!paras) return -1;
    //
    clas_attr clasa;
    char clat_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        //
        clas_meta clasm;
    char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    memset(&clasm, '\0', sizeof (clas_meta));
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELE(clasa, clasm, -1)
        //
        metho * menod = dele_metho(&clasm.meth_list, metnm, paras);
    if (!menod) RETU_DELE(clasa, clasm, -1)
        METH_DELE(menod)
        clasa.version++;
    if (save_class_conte(clat_path, &clasa, clas_path, &clasm)) RETU_DELE(clasa, clasm, -1)
        //
        CLAA_STRU_DELE(clasa)
        CLAM_STRU_DELE(clasm)
        return 0x00;
}

int dele_class_bzl(char *osdb, char *clasn) {
    char clat_path[MAX_PATH];
    char clas_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    if (class_dele_conte(clat_path, clas_path)) return -1;
    //
    return 0x00;
}

//

int comp_metho_bzl(char *clang_txt, char *osdb, char *meth_txt) {
    char clasn[CLASS_LENGTH], metnm[METH_LENGTH], decla[METH_LENGTH];
    if (!split_metho_ex(clasn, metnm, decla, meth_txt)) return -1;
    //
    char clat_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        //
        char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELE(clasa, clasm, -1)
        //
        int meth_type = chk_meth_type(clasm.clas_decl, metnm);
    if (-1 == meth_type) RETU_DELE(clasa, clasm, -1)
        if (!conve_advan_clang(clang_txt, meth_txt, clasm.clas_decl, meth_type)) RETU_DELE(clasa, clasm, -1)
            //
            metho * menod = find_metho_ex(clasm.meth_list, metnm, decla);
    if (menod) RETU_DELE(clasa, clasm, -1)
        printf("appe_mlist_txt\n");
    menod = appe_mlist_txt(&clasm.meth_list, meth_txt);
    if (!menod) RETU_DELE(clasa, clasm, -1)
        if (save_class_conte(clat_path, &clasa, clas_path, &clasm)) RETU_DELE(clasa, clasm, -1)
            //
            CLAA_STRU_DELE(clasa)
            CLAM_STRU_DELE(clasm)
            return 0x00;
}

//

int robk_metho_bzl(char *osdb, char *meth_txt) {
    char clasn[CLASS_LENGTH], metnm[METH_LENGTH], decla[METH_LENGTH];
    if (!split_metho_ex(clasn, metnm, decla, meth_txt)) return -1;
    //
    clas_attr clasa;
    char clat_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        //
        clas_meta clasm;
    char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    memset(&clasm, '\0', sizeof (clas_meta));
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELE(clasa, clasm, -1)
        //
        metho * menod = dele_metho_ex(&clasm.meth_list, metnm, decla);
    if (!menod) RETU_DELE(clasa, clasm, -1)
        METH_DELE(menod)
        clasa.version++;
    if (save_class_conte(clat_path, &clasa, clas_path, &clasm)) RETU_DELE(clasa, clasm, -1)
        //
        CLAA_STRU_DELE(clasa)
        CLAM_STRU_DELE(clasm)
        return 0x00;
}

//

int comp_class_bzl(char *clang_txt, char *osdb, char *clas_decl) {
    char clasn[CLASS_LENGTH];
    if (!split_clame(clasn, clas_decl)) return -1;
    if (!conve_class_clang(clang_txt, clas_decl)) {
        _LOG_INFO("conve class %s exception!", clasn);
        return -1;
    }
    //
    char clat_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
            char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    printf("clas_path:%s\n", clas_path);
    if (!class_exist(clat_path) || !class_exist(clas_path)) {
        _LOG_INFO("class %s exists!", clasn);
        return -1;
    }
    //
    if (creat_class_conte(clat_path, clas_path, clasn, clas_decl))
        return -1;
    //
    return 0x00;
}

//

int robk_class_bzl(char *osdb, char *clas_decl) {
    char clasn[CLASS_LENGTH];
    if (!split_clame(clasn, clas_decl)) return -1;
    //
    char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    printf("unlink clas_path:%s\n", clas_path);
    unlink(clas_path);
    //
    return 0x00;
}

//

int comp_imeth_bzl(char *clang_txt, char *osdb, char *meth_txt) {
    char clasn[CLASS_LENGTH], metnm[METH_LENGTH], decla[METH_LENGTH];
    if (!split_metho_ex(clasn, metnm, decla, meth_txt)) return -1;
    //
    char clat_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        //
        char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELE(clasa, clasm, -1)
        //
        int meth_type = chk_meth_type(clasm.clas_decl, metnm);
    if (-1 == meth_type) RETU_DELE(clasa, clasm, -1)
        if (!conve_advan_clang(clang_txt, meth_txt, clasm.clas_decl, meth_type)) RETU_DELE(clasa, clasm, -1)
            //
            metho * menod = find_metho_ex(clasm.meth_list, metnm, decla);
    if (menod) RETU_DELE(clasa, clasm, -1)
        printf("appe_mlist_txt\n");
    menod = appe_mlist_txt(&clasm.meth_list, meth_txt);
    if (!menod) RETU_DELE(clasa, clasm, -1)
        if (save_class_conte(clat_path, &clasa, clas_path, &clasm)) RETU_DELE(clasa, clasm, -1)
            //
            CLAA_STRU_DELE(clasa)
            CLAM_STRU_DELE(clasm)
            return 0x00;
}

//

int robk_imeth_bzl(char *osdb, char *clasn, char *metnm, char *parat, char *iclas) {
    char clat_path[MAX_PATH];
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    //
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        inherit * innod = dele_imeth(&clasa.inhe_list, metnm, parat, iclas);
    if (!innod) RETU_DELA(clasa, -1)
        IMETH_DELE(innod)
        if (save_class_attri(clat_path, &clasa)) RETU_DELA(clasa, -1)
            CLAA_STRU_DELE(clasa)
            //

            return 0x00;
}

//

int repla_metho_bzl(char *clang_txt, char *osdb, char *meth_txt) {
    char clasn[CLASS_LENGTH], metnm[METH_LENGTH], decla[METH_LENGTH];
    if (!split_metho_ex(clasn, metnm, decla, meth_txt)) return -1;
    //
    char clat_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        //
        char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELE(clasa, clasm, -1)
        //
        int meth_type = chk_meth_type(clasm.clas_decl, metnm);
    if (-1 == meth_type) RETU_DELE(clasa, clasm, -1)
        if (!conve_advan_clang(clang_txt, meth_txt, clasm.clas_decl, meth_type)) RETU_DELE(clasa, clasm, -1)
            //
            metho * menod = find_metho_ex(clasm.meth_list, metnm, decla);
    if (!menod) RETU_DELE(clasa, clasm, -1)
        printf("modi_metho\n");
    modi_metho(menod, metnm, meth_txt);
    clasa.version++;
    if (save_class_conte(clat_path, &clasa, clas_path, &clasm)) RETU_DELE(clasa, clasm, -1)
        //
        CLAA_STRU_DELE(clasa)
        CLAM_STRU_DELE(clasm)

        return 0x00;
}

int repla_class_bzl(char *clang_txt, char *osdb, char *clas_decl) {
    char clasn[CLASS_LENGTH];
    if (!split_clame(clasn, clas_decl)) return -1;
    if (!conve_class_clang(clang_txt, clas_decl)) return -1;
    //
    char clat_path[MAX_PATH];
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
            char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    printf("clas_path:%s\n", clas_path);
    if (class_exist(clat_path) || class_exist(clas_path)) return -1;
    //
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        //
        clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELE(clasa, clasm, -1)
        strcpy(clasm.clas_decl, clas_decl);
    //
    clasa.version++;
    if (save_class_conte(clat_path, &clasa, clas_path, &clasm)) RETU_DELE(clasa, clasm, -1)
        CLAA_STRU_DELE(clasa)
        CLAM_STRU_DELE(clasm)
        //

        return 0x00;
}

//

int load_metho_bzl(char *clang_txt, char *osdb, char *meth_txt) {
    char clasn[CLASS_LENGTH], metnm[METH_LENGTH], decla[METH_LENGTH];
    int meth_type = check_space_type(clasn, metnm, decla, meth_txt);
    char clas_path[MAX_PATH];
    //
    clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELM(clasm, -1)
        //
        metho * menod = find_metho_ex(clasm.meth_list, metnm, decla);
    if (!menod) RETU_DELM(clasm, -1)
        if (!conve_advan_clang(clang_txt, menod->meth_txt, clasm.clas_decl, meth_type)) RETU_DELM(clasm, -1)
            //
            CLAM_STRU_DELE(clasm)

            return 0x00;
}

int load_class_bzl(char *clang_txt, char *osdb, char *clasn) {
    char clas_path[MAX_PATH];
    //
    clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELM(clasm, -1)
        if (!conve_class_clang(clang_txt, clasm.clas_decl)) RETU_DELM(clasm, -1)
            //
            CLAM_STRU_DELE(clasm)

            return 0x00;
}


//

int class_integri_bzl(char *osdb, char *clasn) {
    char clat_path[MAX_PATH];
    int integri = 0x00;
    //
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        integri = clasa.integrity;
    //
    CLAA_STRU_DELE(clasa)

    return integri;
}

//

int parse_cdata_bzl(char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *osdb, char *clasn) {
    char clas_path[MAX_PATH];
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
            // printf("clas_path:%s osdb:%s clasn:%s\n", clas_path, osdb, clasn);
            char clas_decl[LARGE_TEXT_SIZE];
    if (!find_class_defin(clas_decl, clas_path)) return -1;
    // printf("parse_cdata_bzl, clas_decl:%s\n", clas_decl);
    if (parse_class_data_ex(clas_data, clas_decl)) return -1;
    // printf("clas_name:%s\n", clas_name);

    return 0x00;
}

//

int creat_imeth_bzl(char *advan_txt, char *osdb, char *clasn, char *metnm, char *parat, char *iclas) {
    char clas_path[MAX_PATH];
    clas_meta clasm;
    memset(&clasm, '\0', sizeof (clas_meta));
    CREAT_CLASS_FILE(clas_path, osdb, clasn)
    if (!parse_class_conte(&clasm, clas_path)) RETU_DELM(clasm, -1)
        echo_imeth_conte(advan_txt, metnm, parat, &clasm);
    CLAM_STRU_DELE(clasm)
    //
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    CREAT_CLATT_FILE(clas_path, osdb, clasn)
    if (!parse_class_attri(&clasa, clas_path)) RETU_DELA(clasa, -1)
        if (!addi_imeth(&clasa.inhe_list, metnm, parat, iclas)) RETU_DELA(clasa, -1)
            if (save_class_attri(clas_path, &clasa)) RETU_DELA(clasa, -1)
                CLAA_STRU_DELE(clasa)
                //

                return 0x00;
}

int drop_imeth_bzl(char *osdb, char *clasn, char *metnm, char *parat, char *iclas) {
    char clat_path[MAX_PATH];
    clas_attr clasa;
    memset(&clasa, '\0', sizeof (clas_attr));
    strcpy(clasa.clasn, clasn);
    //
    CREAT_CLATT_FILE(clat_path, osdb, clasn)
    if (!parse_class_attri(&clasa, clat_path)) RETU_DELA(clasa, -1)
        inherit * innod = dele_imeth(&clasa.inhe_list, metnm, parat, iclas);
    if (!innod) RETU_DELA(clasa, -1)
        IMETH_DELE(innod)
        if (save_class_attri(clat_path, &clasa)) RETU_DELA(clasa, -1)
            CLAA_STRU_DELE(clasa)
            //

            return 0x00;
}

//

int build_imeth_bzl(char *crea_clas, char *inhe_line, char *iclas[METH_NUMB], char *imeth[METH_NUMB], char *parat[PARAM_NUMB], char *clas_decl) {
    char *last_str = inhe_line;
    char *toke = parse_clasn(crea_clas, clas_decl);
    struct varia_type vtype[CDATNO_NUMB];
    parse_class_meta(vtype, toke);
    //
    char clas_conte[CLASS_LENGTH];
    char meth_conte[METH_LENGTH];
    char paras[PARAM_LENGTH];
    int inde = 0x00;
    for (; (toke = conte_node(clas_conte, meth_conte, paras, toke)); inde++) {
        printf("clas_conte:%s meth_conte:%s\n", clas_conte, meth_conte);
        lscpy_o(iclas[inde], clas_conte, last_str)
        lscpy_o(imeth[inde], meth_conte, last_str)
        conv_iinte_type(parat[inde], vtype, paras);
    }
    MKNONE(iclas[inde]);
    MKNONE(imeth[inde]);
    MKNONE(parat[inde]);
    //
    return 0x00;
}