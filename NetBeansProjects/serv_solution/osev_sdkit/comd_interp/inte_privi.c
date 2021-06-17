

#include "commo_header.h"

#include "istri_utili.h"
#include "authen_bzl.h"
#include "inte_privi.h"

//
#define PPAR_LIST_TYPE    0x00
#define PPAR_LIST_NAME    0x01
//
#define PPAR_ROLE_TYPE    0x00
#define PPAR_ROLE_NAME    0x01
#define PPAR_DIST_NAME    0x02
#define PPAR_PRIVILE      0x03
//
#define PPAR_USER_TYPE    0x00
#define PPAR_USER_NAME    0x01
#define PPAR_SALT_PASWD   0x02   
#define PPAR_ROLE_EXTE    0x02
//

//
#define CHECK_RETURN(FUNC_INVO) if (FUNC_INVO) return -1;

// osev:list(odb);
// osev:user(odb);
// osev:role(odb);

// odb:list();
// odb:user();
// odb:role();

//

static char *opriv_list(char *data_line, char **paras, char *requ_data) {
    printf("parse opriv_list\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *opriv_role(char *data_line, char **paras, char *requ_data) {
    printf("parse opriv_role\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    printf("req_len:%d\n", req_len);
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *opriv_user(char *data_line, char **paras, char *requ_data) {
    printf("parse opriv_ouser\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

char* (*parse_oprivi_tab[])(char *, char **, char *) = {
    opriv_list,
    opriv_role,
    opriv_user
};

//

static char *dpriv_list(char *data_line, char **paras, char *requ_data) {
    printf("parse dpriv_list\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *dpriv_role(char *data_line, char **paras, char *requ_data) {
    printf("parse dpriv_role\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *dpriv_user(char *data_line, char **paras, char *requ_data) {
    printf("parse dpriv_user\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

char* (*parse_dprivi_tab[])(char *, char **, char *) = {
    dpriv_list,
    dpriv_role,
    dpriv_user
};

char* (**parse_privile_tab[])(char *, char **, char *) = {
    parse_oprivi_tab,
    parse_dprivi_tab
};

int valid_privile() {
    printf("valid_privile osev_osdb.\n");
    //    
    return 0x00;
}

// privile

static int osev_list(prod_data *sresp, char **paras) {
    printf("osev list\n");
    if (!paras[PPAR_LIST_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[PPAR_LIST_TYPE])[0x00]) {
        case LIST_ROLE:
            CHECK_RETURN(olist_role_bzl(sresp, paras[PPAR_LIST_NAME]))
            break;
        case LIST_USER:
            CHECK_RETURN(olist_user_bzl(sresp, paras[PPAR_LIST_NAME]))
            break;
        default:
            _LOG_DEBUG("osev_list 1:%u", ((uint32 *) paras[PPAR_LIST_TYPE])[0x00]);
            _LOG_DEBUG("osev_list 2:%s", paras[PPAR_ROLE_NAME]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

static int osev_role(prod_data *sresp, char **paras) {
    printf("osev role\n");
    if (!paras[PPAR_ROLE_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[PPAR_ROLE_TYPE])[0x00]) {
        case ADDI_ROLE:
            CHECK_RETURN(oadd_role_bzl(sresp, paras[PPAR_ROLE_NAME]))
            break;
        case DELE_ROLE:
            CHECK_RETURN(odel_role_bzl(sresp, paras[PPAR_ROLE_NAME]))
            break;
        case GRANT_PRIV:
            CHECK_RETURN(ogran_priv_bzl(sresp, paras[PPAR_ROLE_NAME], paras[PPAR_DIST_NAME], ((uint32 *) paras[PPAR_PRIVILE])[0x00]))
            break;
        case REVOKE_PRIV:
            CHECK_RETURN(orevk_priv_bzl(sresp, paras[PPAR_ROLE_NAME], paras[PPAR_DIST_NAME], ((uint32 *) paras[PPAR_PRIVILE])[0x00]))
            break;
        default:
            _LOG_DEBUG("osev_role 1:%u", ((uint32 *) paras[PPAR_ROLE_TYPE])[0x00]);
            _LOG_DEBUG("osev_role 2:%s", paras[PPAR_ROLE_NAME]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

static int osev_user(prod_data *sresp, char **paras) {
    printf("osev user\n");
    if (!paras[PPAR_USER_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[PPAR_USER_TYPE])[0x00]) {
        case ADDI_USER:
            CHECK_RETURN(oadd_user_bzl(sresp, paras[PPAR_USER_NAME], paras[PPAR_SALT_PASWD]))
            break;
        case DELE_USER:
            CHECK_RETURN(odel_user_bzl(sresp, paras[PPAR_USER_NAME]))
            break;
        case GRANT_ROLE:
            CHECK_RETURN(ogran_role_bzl(sresp, paras[PPAR_USER_NAME], paras[PPAR_ROLE_EXTE]))
            break;
        case REVOKE_ROLE:
            CHECK_RETURN(orevk_role_bzl(sresp, paras[PPAR_USER_NAME], paras[PPAR_ROLE_EXTE]))
            break;
        default:
            _LOG_DEBUG("osev_ouser:%u", ((uint32 *) paras[PPAR_USER_TYPE])[0x00]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

int (*hand_oprivi_tab[])(prod_data *, char **) = {
    osev_list,
    osev_role,
    osev_user,
};

//

static int osdb_list(prod_data *sresp, char **paras) {
    printf("odb privi list\n");
    if (!paras[PPAR_LIST_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[PPAR_LIST_TYPE])[0x00]) {
        case LIST_ROLE:
            CHECK_RETURN(dlist_role_bzl(sresp, paras[PPAR_LIST_NAME]))
            break;
        case LIST_USER:
            CHECK_RETURN(dlist_user_bzl(sresp, paras[PPAR_LIST_NAME]))
            break;
        default:
            _LOG_DEBUG("osev_list 1:%u", ((uint32 *) paras[PPAR_LIST_TYPE])[0x00]);
            _LOG_DEBUG("osev_list 2:%s", paras[PPAR_ROLE_NAME]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

static int osdb_role(prod_data *sresp, char **paras) {
    printf("odb role\n");
    if (!paras[PPAR_ROLE_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[PPAR_ROLE_TYPE])[0x00]) {
        case ADDI_ROLE:
            CHECK_RETURN(dadd_role_bzl(sresp, paras[PPAR_ROLE_NAME]))
            break;
        case DELE_ROLE:
            CHECK_RETURN(ddel_role_bzl(sresp, paras[PPAR_ROLE_NAME]))
            break;
        case GRANT_PRIV:
            CHECK_RETURN(dgran_priv_bzl(sresp, paras[PPAR_ROLE_NAME], paras[PPAR_DIST_NAME], ((uint32 *) paras[PPAR_PRIVILE])[0x00]))
            break;
        case REVOKE_PRIV:
            CHECK_RETURN(drevk_priv_bzl(sresp, paras[PPAR_ROLE_NAME], paras[PPAR_DIST_NAME], ((uint32 *) paras[PPAR_PRIVILE])[0x00]))
            break;
        default:
            _LOG_DEBUG("osdb_role:%u", ((uint32 *) paras[PPAR_ROLE_TYPE])[0x00]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

static int osdb_user(prod_data *sresp, char **paras) {
    printf("odb user\n");
    if (!paras[PPAR_USER_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[PPAR_USER_TYPE])[0x00]) {
        case ADDI_USER:
            CHECK_RETURN(dadd_user_bzl(sresp, paras[PPAR_USER_NAME], paras[PPAR_SALT_PASWD]))
            break;
        case DELE_USER:
            CHECK_RETURN(ddel_user_bzl(sresp, paras[PPAR_USER_NAME]))
            break;
        case GRANT_ROLE:
            CHECK_RETURN(dgran_role_bzl(sresp, paras[PPAR_USER_NAME], paras[PPAR_ROLE_EXTE]))
            break;
        case REVOKE_ROLE:
            CHECK_RETURN(drevk_role_bzl(sresp, paras[PPAR_USER_NAME], paras[PPAR_ROLE_EXTE]))
            break;
        default:
            _LOG_DEBUG("osdb_cuser:%u", ((uint32 *) paras[PPAR_USER_TYPE])[0x00]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

int (*hand_dprivi_tab[])(prod_data *, char **) = {
    osdb_list,
    osdb_role,
    osdb_user
};