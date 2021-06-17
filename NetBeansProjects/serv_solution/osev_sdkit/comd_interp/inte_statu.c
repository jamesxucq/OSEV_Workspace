#include "commo_header.h"

#include "istri_utili.h"
#include "rstat_bzl.h"
#include "authen_bzl.h"
#include "inte_statu.h"

//
#define SPAR_ECHO_VALU 0x00

//
#define SPAR_STATI_TYPE 0x00
#define SPAR_STATI_OID  0x01

//
#define SPAR_OSDB_NAME 0x00
#define SPAR_OSDB_OID 0x00
#define SPAR_OPEN_LEVE 0x01

//
#define SPAR_STAT_TYPE 0x00
#define SPAR_STAT_NAID 0x01
#define SPAR_STAT_SELEVE 0x02

// osev:echo(odb);
// osev:open(odb);
// osev:close(odb);
// osev:status(odb);
// osev:auth(odb);

// odb:echo();
// odb:open();
// odb:close();
// odb:status();
// odb:auth();

//

static char *ostat_echo(char *data_line, char **paras, char *requ_data) {
    printf("parse ostat_echo\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    paras[0x00] = NULL;
    return data_line;
}

static char *ostat_open(char *data_line, char **paras, char *requ_data) {
    printf("parse ostat_open\n");
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

static char *ostat_close(char *data_line, char **paras, char *requ_data) {
    printf("parse ostat_close\n");
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

static char *ostat_status(char *data_line, char **paras, char *requ_data) {
    printf("parse ostat_status\n");
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

static char *ostat_stati(char *data_line, char **paras, char *requ_data) {
    printf("parse ostat_stati\n");
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

char* (*parse_ostatu_tab[])(char *, char **, char *) = {
    ostat_echo,
    ostat_open,
    ostat_close,
    ostat_status,
    ostat_stati
};

//

static char *dstat_echo(char *data_line, char **paras, char *requ_data) {
    printf("parse dstat_echo\n");
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

static char *dstat_open(char *data_line, char **paras, char *requ_data) {
    printf("parse dstat_open\n");
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

static char *dstat_close(char *data_line, char **paras, char *requ_data) {
    printf("parse dstat_close\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    char *last_str = parse_obje(data_line, paras, parse_tok);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *dstat_status(char *data_line, char **paras, char *requ_data) {
    printf("parse dstat_status\n");
    char *parse_tok = requ_data;
    int req_len;
    parse_tok = pobje_conte(&req_len, parse_tok);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    printf("parse dstat_status, req_len:%d\n", req_len);
    //
    char *last_str = decode_general(data_line, paras, parse_tok, req_len);
    if (!last_str) {
        paras[0x00] = NULL;
        return NULL;
    }
    //
    return last_str;
}

static char *dstat_stati(char *data_line, char **paras, char *requ_data) {
    printf("parse dstat_stati\n");
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

char* (*parse_dstatu_tab[])(char *, char **, char *) = {
    dstat_echo,
    dstat_open,
    dstat_close,
    dstat_status,
    dstat_stati
};

char* (**parse_status_tab[])(char *, char **, char *) = {
    parse_ostatu_tab,
    parse_dstatu_tab
};

int valid_status() {
    printf("valid_status osev_osdb.\n");
    //    
    return 0x00;
}

// status

static int osev_echo(prod_data *sresp, char **paras) {
    printf("osev echo\n");
    if (paras[SPAR_ECHO_VALU]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    if (echo_osev_bzl(sresp)) {
        PDAT_EXCEP_TAIL(sresp, ECHO_OID_EXCE)
        return -1;
    }
    //
    return 0x00;
}

static int osev_open(prod_data *sresp, char **paras) {
    printf("osev open\n");
    if (!paras[SPAR_OSDB_NAME]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    osv_oid_t obje_oid;
    if (open_osev_bzl(&obje_oid, paras[SPAR_OSDB_NAME], ((uint32 *) paras[SPAR_OPEN_LEVE])[0x00])) {
        PDAT_EXCEP_TAIL(sresp, OPEN_ODB_EXCE)
        return -1;
    }
    //
    build_oid_bzl(sresp, &obje_oid);
    return 0x00;
}

static int osev_close(prod_data *sresp, char **paras) {
    printf("osev close\n");
    if (!paras[SPAR_OSDB_NAME]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    if (close_osev_bzl(paras[SPAR_OSDB_NAME])) {
        PDAT_EXCEP_TAIL(sresp, CLOSE_ODB_EXCE)
        return -1;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int osev_status(prod_data *sresp, char **paras) {
    printf("osev status\n");
    if (!paras[SPAR_STAT_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[SPAR_STAT_TYPE])[0x00]) {
        case STATU_SHOW:
            break;
        case STATU_SETLEVE:
            if (set_oleve_bzl(paras[SPAR_STAT_NAID], ((uint32 *) paras[SPAR_STAT_SELEVE])[0x00])) {
                PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
                return -1;
            }
            PDAT_NONE_TAIL(sresp)
            break;
        case STATU_PRIVILE:
            if (reloa_privi_bzl(sresp)) {
                PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
                return -1;
            }
            PDAT_NONE_TAIL(sresp)
            break;
        default:
            _LOG_DEBUG("osev_status:%u", ((uint32 *) paras[SPAR_STAT_TYPE])[0x00]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

static int osev_stati(prod_data *sresp, char **paras) {
    printf("osev_stati\n");
    if (!paras[SPAR_STATI_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[SPAR_STATI_TYPE])[0x00]) {
        case STATI_OSDB:
            if (ostati_osdb_bzl(sresp)) {
                PDAT_EXCEP_TAIL(sresp, STATI_OSDB_EXCE)
                return -1;
            }
            break;
        default:
            break;
    }
    //
    return 0x00;
}

int (*hand_ostatu_tab[])(prod_data *, char **) = {
    osev_echo,
    osev_open,
    osev_close,
    osev_status,
    osev_stati
};

//

static int osdb_echo(prod_data *sresp, char **paras) {
    printf("odb echo\n");
    if (!paras[SPAR_ECHO_VALU]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    if (echo_osdb_bzl(sresp, paras[SPAR_ECHO_VALU])) {
        PDAT_EXCEP_TAIL(sresp, ECHO_OID_EXCE)
        return -1;
    }
    //
    return 0x00;
}

static int osdb_open(prod_data *sresp, char **paras) {
    printf("odb open\n");
    if (!paras[SPAR_OSDB_OID]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    if (open_osdb_bzl((osv_oid_t *) paras[SPAR_OSDB_OID], ((uint32 *) paras[SPAR_OPEN_LEVE])[0x00])) {
        PDAT_EXCEP_TAIL(sresp, OPEN_ODB_EXCE)
        return -1;
    }
    //
    build_oid_bzl(sresp, (osv_oid_t *) paras[SPAR_OSDB_OID]);
    return 0x00;
}

static int osdb_close(prod_data *sresp, char **paras) {
    printf("odb close\n");
    if (!paras[SPAR_OSDB_OID]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    if (close_osdb_bzl((osv_oid_t *) paras[SPAR_OSDB_OID])) {
        PDAT_EXCEP_TAIL(sresp, CLOSE_ODB_EXCE)
        return -1;
    }
    //
    PDAT_NONE_TAIL(sresp)
    return 0x00;
}

static int osdb_status(prod_data *sresp, char **paras) {
    printf("odb status\n");
    if (!paras[SPAR_STAT_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[SPAR_STAT_TYPE])[0x00]) {
        case STATU_SHOW:
            break;
        case STATU_SETLEVE:
            if (set_dleve_bzl((osv_oid_t *) paras[SPAR_STAT_NAID], ((uint32 *) paras[SPAR_STAT_SELEVE])[0x00])) {
                PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
                return -1;
            }
            PDAT_NONE_TAIL(sresp)
            break;
        case STATU_PRIVILE:
            if (reloa_privi_bzl(sresp)) {
                PDAT_EXCEP_TAIL(sresp, OSDB_ADMIN_EXCE)
                return -1;
            }
            PDAT_NONE_TAIL(sresp)
            break;
        default:
            _LOG_DEBUG("osdb_status:%u", ((uint32 *) paras[SPAR_STAT_TYPE])[0x00]);
            PDAT_NONE_TAIL(sresp)
            return -1;
    }
    //
    return 0x00;
}

static int osdb_stati(prod_data *sresp, char **paras) {
    printf("odb stati\n");
    if (!paras[SPAR_STATI_TYPE]) {
        PDAT_EXCEP_TAIL(sresp, INVA_PARA_EXCE)
        return -1;
    }
    //
    switch (((uint32 *) paras[SPAR_STATI_TYPE])[0x00]) {
        case STATI_OSDB:
            if (dstati_osdb_bzl(sresp, (osv_oid_t *) paras[SPAR_STATI_OID])) {
                PDAT_EXCEP_TAIL(sresp, STATI_OSDB_EXCE)
                return -1;
            }
            break;
        default:
            break;
    }
    //
    return 0x00;
}

int (*hand_dstatu_tab[])(prod_data *, char **) = {
    osdb_echo,
    osdb_open,
    osdb_close,
    osdb_status,
    osdb_stati
};