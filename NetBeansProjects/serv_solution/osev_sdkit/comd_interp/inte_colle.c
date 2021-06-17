#include "commo_header.h"
#include "istri_utili.h"

#include "invo_bzl.h"
#include "hand_bzl.h"

#include "inte_colle.h"


//
static char *colle_list(char *data_line, char **paras, char *requ_data) {
    printf("parse colle_list\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //    
    char *last_str = decode_invok_list(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *colle_creat(char *data_line, char **paras, char *requ_data) {
    printf("parse colle_creat\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_text(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *colle_repla(char *data_line, char **paras, char *requ_data) {
    printf("parse colle_repla\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_text(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *colle_drop(char *data_line, char **paras, char *requ_data) {
    printf("parse colle_drop\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_stri(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *colle_integri(char *data_line, char **paras, char *requ_data) {
    printf("parse colle_integri\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_stri(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *colle_reload(char *data_line, char **paras, char *requ_data) {
    printf("parse colle_reload\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_stri(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

char* (*parse_colle_tab[])(char *, char **, char *) = {
    colle_list,
    colle_creat,
    colle_repla,
    colle_drop,
    colle_integri,
    colle_reload
};


//
//

static int class_list(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand class list.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    if (list_class_bzl(sresp, osdb, paras[0x00], ((uint32 *) paras[0x00 + 0x01])[0x00])) {
        PDAT_EXCEP_TAIL(sresp, CLAS_NOT_FOUND)
        return -1;
    }
    printf("execu_str:%s\n", sresp->sebuf);
    return 0x00;
}

//

static int class_creat_conte(prod_data *sresp, hand_data *handa, char *osdb, char *paras) {
    char clang_txt[ADVAN_OBJE_SIZE];
    MKZERO(clang_txt);
    //
    if (comp_class_bzl(clang_txt, osdb, paras)) {
        robk_class_bzl(osdb, paras);
        PDAT_EXCEP_TAIL(sresp, CREAT_CLAS_EXCE)
        return -1;
    }
    printf("hcrea_class_bzl.\n");
    if (hcrea_class_bzl(sresp, handa, clang_txt, osdb, paras)) {
        robk_class_bzl(osdb, paras);
        PDAT_EXCEP_TAIL(sresp, COMP_CLAS_EXCE)
        return -1;
    }
    //
    return 0x00;
}

static int class_creat_inheri(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char *paras) {
    char crea_clas[CLASS_LENGTH];
    char inhe_line[LINE_LENGTH];
    char *iclas[METH_NUMB], *imeth[METH_NUMB], *patyp[METH_NUMB];
    if (build_imeth_bzl(crea_clas, inhe_line, iclas, imeth, patyp, paras)) {
        PDAT_EXCEP_TAIL(sresp, CREAT_INHER_EXCE)
        return -1;
    }
    //
    char advan_txt[LARGE_TEXT_SIZE], clang_txt[ADVAN_OBJE_SIZE];
    char **clasn = iclas, **metnm = imeth, **parat = patyp;
    for (; clasn[0x00] || metnm[0x00]; ++clasn, ++metnm, ++parat) {
        MKZERO(clang_txt);
        if (creat_imeth_bzl(advan_txt, osdb, clasn[0x00], metnm[0x00], parat[0x00], crea_clas)) {
            robk_imeth_bzl(osdb, clasn[0x00], metnm[0x00], parat[0x00], crea_clas);
            PDAT_EXCEP_TAIL(sresp, CREAT_INHER_EXCE)
            return -1;
        }
        if (comp_imeth_bzl(clang_txt, osdb, advan_txt)) {
            robk_imeth_bzl(osdb, clasn[0x00], metnm[0x00], parat[0x00], crea_clas);
            PDAT_EXCEP_TAIL(sresp, CREAT_INHER_EXCE)
            return -1;
        }
        if (hcrea_metho_bzl(sresp, hando, handa, clang_txt, osdb, paras)) {
            robk_imeth_bzl(osdb, clasn[0x00], metnm[0x00], parat[0x00], crea_clas);
            PDAT_EXCEP_HEAD(sresp, OSEV_ATTACH_EXCE)
            return -1;
        }
    }
    //
    return 0x00;
}

static int class_creat(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand class creat.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    if (class_creat_conte(sresp, handa, osdb, paras[0x00]))
        return -1;
    if (class_creat_inheri(sresp, hando, handa, osdb, paras[0x00]))
        return -1;
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int class_repla(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand class replace.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    char clang_txt[ADVAN_OBJE_SIZE];
    MKZERO(clang_txt);
    //
    if (repla_class_bzl(clang_txt, osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, CREAT_CLAS_EXCE)
        return -1;
    }
    printf("hcrea_class_bzl.\n");
    if (hcrea_class_bzl(sresp, handa, clang_txt, osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, COMP_CLAS_EXCE)
        return -1;
    }
    //
    return 0x00;
}

//

static int class_drop_conte(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char *clasn) {
    if (hdrop_class_bzl()) {
        PDAT_EXCEP_TAIL(sresp, DROP_CLAS_EXCE)
        return -1;
    }
    if (dele_class_bzl(osdb, clasn)) {
        PDAT_EXCEP_TAIL(sresp, DROP_CLAS_EXCE)
        return -1;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int class_drop_inheri(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char *clasn) {
    char clasd[LARGE_TEXT_SIZE];
    if (list_clasd_bzl(clasd, osdb, clasn)) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    char drop_clas[CLASS_LENGTH];
    char inhe_line[LINE_LENGTH];
    char *iclas[METH_NUMB], *imeth[METH_NUMB], *patyp[METH_NUMB];
    if (build_imeth_bzl(drop_clas, inhe_line, iclas, imeth, patyp, clasd)) {
        PDAT_EXCEP_TAIL(sresp, CREAT_INHER_EXCE)
        return -1;
    }
    //
    char **metnm = imeth;
    for (; metnm[0x00]; ++metnm) {
        if (hdrop_metho_bzl()) {
            PDAT_EXCEP_TAIL(sresp, DROP_CLAS_EXCE)
            return -1;
        }
        if (drop_imeth_bzl(osdb, iclas[0x00], metnm[0x00], patyp[0x00], drop_clas)) {
            PDAT_EXCEP_TAIL(sresp, DROP_CLAS_EXCE)
            return -1;
        }
    }
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int class_drop(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand class drop.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    if (class_drop_inheri(sresp, hando, handa, osdb, paras[0x00]))
        return -1;
    if (class_drop_conte(sresp, hando, handa, osdb, paras[0x00]))
        return -1;
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int class_integri(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand class integri.\n");
    int integri = class_integri_bzl(osdb, paras[0x00]);
    printf("integri:%d\n", integri);
    switch (integri) {
        case 0x00:
            PDAT_EXCEP_TAIL(sresp, CLAS_INTEG_EXCE)
            return -1;
        case 0x01:
            break;
        case -1:
            PDAT_EXCEP_TAIL(sresp, CLAS_INFO_EXCE)
            return -1;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int class_reload(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand metho reload.\n");
    char clang_txt[ADVAN_OBJE_SIZE];
    MKZERO(clang_txt);
    //
    if (load_class_bzl(clang_txt, osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, RELOA_CLAS_EXCE)
        return -1;
    }
    /*
        if (hload_class_bzl(dlsth, clang_txt, osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, COMP_CLAS_EXCE)
        }
     */
    // PDAT_NONE_TAIL(sresp)
    return 0x00;
}

int (*hand_colle_tab[])(prod_data *, hand_data *, hand_data *, char *, char **) = {
    class_list,
    class_creat,
    class_repla,
    class_drop,
    class_integri,
    class_reload
};
