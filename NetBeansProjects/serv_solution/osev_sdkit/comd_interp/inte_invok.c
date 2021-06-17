#include "commo_header.h"
#include "istri_utili.h"

#include "invo_bzl.h"
#include "hand_bzl.h"
#include "inte_invok.h"

// odb:list();
// odb:creat();
// odb:replace();
// odb:drop();
// odb:integri();
// odb:reload();

//

static char *invok_list(char *data_line, char **paras, char *requ_data) {
    printf("parse invok_list\n");
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

static char *invok_creat(char *data_line, char **paras, char *requ_data) {
    printf("parse invok_creat\n");
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

static char *invok_repla(char *data_line, char **paras, char *requ_data) {
    printf("parse invok_repla\n");
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

static char *invok_drop(char *data_line, char **paras, char *requ_data) {
    printf("parse invok_drop\n");
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

static char *invok_integri(char *data_line, char **paras, char *requ_data) {
    printf("parse invok_integri\n");
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

static char *invok_reload(char *data_line, char **paras, char *requ_data) {
    printf("parse invok_reload\n");
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

char* (*parse_invok_tab[])(char *, char **, char *) = {
    invok_list,
    invok_creat,
    invok_repla,
    invok_drop,
    invok_integri,
    invok_reload
};

//

int valid_invoke() {
    // strcpy(coin_invo->space_str, osdb);
    return 0x00;
}

// invoke

static int metho_list(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand metho list.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    if (list_metho_bzl(sresp, osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, METH_NOT_FOUND)
        return -1;
    }
    return 0x00;
}

//

static int metho_creat(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand metho creat.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    char clang_txt[ADVAN_OBJE_SIZE];
    MKZERO(clang_txt);
    //
    if (comp_metho_bzl(clang_txt, osdb, paras[0x00])) {
        robk_metho_bzl(osdb, paras[0x00]);
        PDAT_EXCEP_TAIL(sresp, CREAT_METH_EXCE)
        return -1;
    }
    //
    if (hcrea_metho_bzl(sresp, hando, handa, clang_txt, osdb, paras[0x00])) {
        robk_metho_bzl(osdb, paras[0x00]);
        PDAT_EXCEP_HEAD(sresp, OSEV_ATTACH_EXCE)
        return -1;
    }
    //
    return 0x00;
}

//

static int metho_drop(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand metho drop.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    if (hdrop_metho_bzl()) {
        PDAT_EXCEP_TAIL(sresp, DROP_METH_EXCE)
        return -1;
    }
    if (dele_metho_bzl(osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, DROP_METH_EXCE)
        return -1;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int metho_reload(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand metho reload.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    char clang_txt[ADVAN_OBJE_SIZE];
    MKZERO(clang_txt);
    //
    if (load_metho_bzl(clang_txt, osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, RELOA_METH_EXCE)
        return -1;
    }
    /*
        if (hload_metho_bzl(dlsth, clang_txt, osdb, paras[0x00])) {
            PDAT_EXCEP_TAIL(sresp, COMP_METH_EXCE)
            return -1;
        }
     */
    //　PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int metho_repla(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand metho replace.\n");
    if (!paras[0x00]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    char clang_txt[ADVAN_OBJE_SIZE];
    MKZERO(clang_txt);
    //
    if (repla_metho_bzl(clang_txt, osdb, paras[0x00])) {
        PDAT_EXCEP_TAIL(sresp, CREAT_METH_EXCE)
        return -1;
    }
    //
    if (hcrea_metho_bzl(sresp, hando, handa, clang_txt, osdb, paras[0x00])) {
        PDAT_EXCEP_HEAD(sresp, OSEV_ATTACH_EXCE)
        return -1;
    }
    //
    return 0x00;
}

static int metho_none(prod_data *sresp, hand_data *hando, hand_data *handa, char *osdb, char **paras) {
    printf("hand metho null.\n");
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

int (*hand_invok_tab[])(prod_data *, hand_data *, hand_data *, char *, char **) = {
    metho_list,
    metho_creat,
    metho_repla,
    metho_drop,
    metho_none,
    metho_reload
};

//