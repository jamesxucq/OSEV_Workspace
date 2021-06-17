
#include <stdio.h>
#include <ctype.h>
#include <pthread.h>

#include "commo_macro.h"
#include "parse_command.h"
#include "clie_obje.h"
#include "stri_utili.h"
#include "conv_utili.h"
#include "shel_macro.h"

//
#define INVA_PRIV       0x00000000
//
// general scope
#define SCOP_OSEV       0x01000000
#define SCOP_OSDB       0x02000000 // osdb level
#define SCOP_EOBJ       0x04000000
// SCOP_OSDB sub scope
#define LEVE_ONE            0x00010000
#define LEVE_TWOP           0x00020000
#define LEVE_THRE           0x00040000
#define LEVE_FOUP           0x00080000
#define OSDB_LEVE_OTTF (LEVE_ONE | LEVE_TWOP | LEVE_THRE | LEVE_FOUP)
//
// general privile
// SCOP_OSEV privile
#define SVOD_PRIVI      0x00000100 // role / user
#define SVOD_ODBM       0x00000200 // manage the odb
#define SVOD_CLUST      0x00000400 // clust
// SCOP_OSDB LEVEL privile
#define ODLE_READ       0x00000001
#define ODLE_WRITE      0x00000002
#define ODLE_EXECU      0x00000004
// SCOP_EOBJ privile
#define COEN_ECHO       0x00000001
#define COEN_CREAT      0x00000002
#define COEN_DROP       0x00000004
#define COEN_FIND       0x00000008
#define COEN_UPDAT      0x00000010
#define COEN_INSER      0x00000020
#define COEN_FACTO      0x00000040
#define COEN_INVOK      0x00000080

//
// "12p34p" "1,2+,3,4+" "1 2p 3 4p"

struct value_node {
    const char *text;
    uint32 value;
};

static const struct value_node level_value_table[] = {
    {"1", LEVE_ONE},
    {"2+", LEVE_TWOP},
    {"3", LEVE_THRE},
    {"4+", LEVE_FOUP},
    {NULL, 0x00}
};

static const struct value_node level_alpha_table[] = {
    {"1", LEVE_ONE},
    {"2p", LEVE_TWOP},
    {"3", LEVE_THRE},
    {"4p", LEVE_FOUP},
    {NULL, 0x00}
};

#define TEXT_VALUE(VALUE, TABLE, TEXT) { \
    struct value_node *item; \
    for(item = (struct value_node *)TABLE; item->text; ++item) \
        if(!strcasecmp(item->text, TEXT)) break; \
    VALUE = item->value; \
}

static char *leve_alph(char *alph_valu, char *stri) {
    char *toke = stri;
    if (isdigit(toke[0x00])) alph_valu[0x00] = toke[0x00];
    else return NULL;
    if (isalpha((toke + 0x01)[0x00])) {
        alph_valu[0x01] = (++toke)[0x00];
    } else alph_valu[0x01] = '\0';
    //
    return toke;
}

uint32 parse_level(char *leve_stri) {
    // printf("leve_stri:|%s|\n", leve_stri);
    char alph_stri[0x03];
    uint32 leval, leve_valu = 0x00;
    //
    alph_stri[0x02] = '\0';
    char *toke = leve_stri;
    for (; toke[0x00]; toke++) {
        if (' ' == toke[0x00] || ',' == toke[0x00]) continue;
        if (!(toke = leve_alph(alph_stri, toke))) return 0x00;
        // printf("alph_stri:|%s|\n", alph_stri);
        TEXT_VALUE(leval, level_value_table, alph_stri)
        if (!leval) TEXT_VALUE(leval, level_alpha_table, alph_stri)
            if (!leval) return 0x00;
        leve_valu |= leval;
    }
    //
    printf("leve_valu:|%08X|\n", leve_valu);
    return leve_valu;
}

// "f7e6fa4bd931435c03000000:1,2p,3,4p"
#define INVA_DIST -1
#define ONLY_OSDB 0x01
#define OSDB_LEVE 0x02
#define OSDB_CONT 0x03

static void take_symbol(char *symbol, char *stri) {
    char *toksp = kill_blank(stri);
    if (toksp) {
        char *tokep = strchr(toksp + 0x01, ' ');
        if (tokep) tokep[0x00] = '\0';
        strcpy(symbol, toksp);
    }
}

static uint32 levcon_type(char *stri) {
    char *toke = kill_blank(stri);
    if (!toke) return 0x00;
    if (isalpha(toke[0x00])) return OSDB_CONT;
    if (isdigit(toke[0x00])) return OSDB_LEVE;
    return 0x00;
}

static uint32 split_disti(char *odbl, char *levcon, char *dist_name) {
    uint32 levco_type = INVA_DIST;
    char *toke;
    //
    if ((toke = strchr(dist_name, ':'))) {
        toke[0x00] = '\0';
        take_symbol(odbl, dist_name);
        levco_type = levcon_type(++toke);
        if (OSDB_CONT == levco_type) take_symbol(levcon, toke);
        else if (OSDB_LEVE == levco_type) strcpy(levcon, toke);
    } else levco_type = ONLY_OSDB;
    //
    return levco_type;
}

//
static osv_str_t OSEV_DEFAULT_TOK = osv_stri("osev");

static uint32 parse_dist_scope(char *dist_name, char *obje_iden) {
    uint32 leval;
    uint32 scop_valu = INVA_PRIV;
    //
    char odbl[OSEV_LENGTH], levcon[OBJE_LENGTH];
    if (strncmp(OSEV_DEFAULT_TOK.data, obje_iden, OSEV_DEFAULT_TOK.len)) {
        int dist_type = split_disti(odbl, levcon, dist_name);
        switch (dist_type) {
            case ONLY_OSDB:
                scop_valu = SCOP_OSDB | OSDB_LEVE_OTTF;
                break;
            case OSDB_LEVE:
                strcpy(dist_name, odbl);
                leval = parse_level(levcon);
                if (!leval) return INVA_PRIV;
                scop_valu = SCOP_OSDB | leval;
                break;
            case OSDB_CONT:
                sprintf(dist_name, "%s:%s", odbl, levcon);
                scop_valu = SCOP_EOBJ;
                break;
            default:
                scop_valu = INVA_PRIV;
                break;
        }
    } else scop_valu = SCOP_OSEV;
    //
    return scop_valu;
}

//
static struct paras_node statu_type_tab[] = {
    {"SHOW", "1I"}, // STATU_SHOW
    {"SET_LEVEL", "2I"}, // STATU_SETLEVE
    {"RESET_PRIVILE", "3I"}, // STATU_PRIVILE
    {NULL, "0I"}
};

int sconv_statu_para(char **paras) {
    PARAS_VALUE(paras[0x00], statu_type_tab);
    if (!strcmp("0I", paras[0x00])) return -1;
    //
    return 0x00;
}

//
static struct paras_node stati_type_tab[] = {
    {"ODB", "1I"}, // STATI_OSDB
    {NULL, "0I"}
};

int sconv_stati_para(char **paras) {
    PARAS_VALUE(paras[0x00], stati_type_tab);
    if (!strcmp("0I", paras[0x00])) return -1;
    //
    return 0x00;
}

// xxx:echo(); => odb:echo("xxx");

int sconv_echo_styl(char **paras, char *obje_iden) {
    if (!strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        if (paras[0x00])return -1;
    } else strcpy(obje_iden, OSDB_DEFAULT_VALUE);
    return 0x00;
}

//

// osev:open("xxx", "12p34p");
// xxx:open("12p34p");
// xxx:open("12p34p"); => odb:open("xxx", "12p34p");

int sconv_open_styl(char **paras, char *obje_iden) {
    uint32 leve_valu;
    if (strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        quote_decode(paras[0x00]);
        leve_valu = parse_level(paras[0x00]);
        expand_tail(paras + 0x01, paras[0x00]);
        sprintf(paras[0x01], "%uI", leve_valu);
        //
        pthread_mutex_lock(&_conta_cache_mutex_);
        osv_oid_t *obje_oid = find_osdb(_conta_cache_hm_, obje_iden, _shell_clie_);
        pthread_mutex_unlock(&_conta_cache_mutex_);
        if (!obje_oid) {
            printf("Not found %s !\n", obje_iden);
            return -1;
        }
        // 
        expand_tail(paras, paras[0x01]);
        memcpy_o(paras[0x00], obje_oid, sizeof (osv_oid_t));
        strcpy(obje_iden, OSDB_DEFAULT_VALUE);
    } else {
        quote_decode(paras[0x01]);
        leve_valu = parse_level(paras[0x01]);
        sprintf(paras[0x01], "%uI", leve_valu);
    }
    //
    return 0x00;
}

//
// xxx:close(); => odb:close("xxx");

int sconv_close_styl(char **paras, char *obje_iden, char *sline) {
    if (strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        if (paras[0x00]) return -1;
        pthread_mutex_lock(&_conta_cache_mutex_);
        osv_oid_t *obje_oid = find_osdb(_conta_cache_hm_, obje_iden, _shell_clie_);
        pthread_mutex_unlock(&_conta_cache_mutex_);
        if (!obje_oid) {
            printf("Not found %s !\n", obje_iden);
            return -1;
        }
        // 
        paras[0x00] = sline;
        memcpy_o(paras[0x00], obje_oid, sizeof (osv_oid_t));
        paras[0x01] = NULL;
        strcpy(obje_iden, OSDB_DEFAULT_VALUE);
    } else {
        if (!paras[0x00]) return -1;
        else if (paras[0x01]) return -1;
    }
    //
    return 0x00;
}

//

// xxx:status(AUTH, ON); => odb:status(AUTH, "xxx", ON);
// osev:status(SET_LEVEL, "xodb", "12p");
// odb:status(SET_LEVEL, "12p");
// osev:status(RESET_PRIVILE, "xodb");
// odb:status(RESET_PRIVILE);

int sconv_statu_styl(char **paras, char *obje_iden) {
    uint32 leve_valu;
    //
    if (strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        pthread_mutex_lock(&_conta_cache_mutex_);
        osv_oid_t *obje_oid = find_osdb(_conta_cache_hm_, obje_iden, _shell_clie_);
        pthread_mutex_unlock(&_conta_cache_mutex_);
        if (!obje_oid) {
            printf("Not found %s !\n", obje_iden);
            return -1;
        }
        if (!strcmp("2I", paras[0x00])) {
            quote_decode(paras[0x01]);
            leve_valu = parse_level(paras[0x01]);
            sprintf(paras[0x01], "%uI", leve_valu);
        }
        strcpy(obje_iden, OSDB_DEFAULT_VALUE);
    } else {
        if (!strcmp("2I", paras[0x00])) {
            quote_decode(paras[0x02]);
            leve_valu = parse_level(paras[0x02]);
            sprintf(paras[0x02], "%uI", leve_valu);
        }
    }
    //
    return 0x00;
}

//
// xxx:stati(OSDB); => odb:stati(OSDB, "xxx");

int sconv_stati_styl(char **paras, char *obje_iden) {
    if (strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        pthread_mutex_lock(&_conta_cache_mutex_);
        osv_oid_t *obje_oid = find_osdb(_conta_cache_hm_, obje_iden, _shell_clie_);
        pthread_mutex_unlock(&_conta_cache_mutex_);
        if (!obje_oid) {
            printf("Not found %s !\n", obje_iden);
            return -1;
        }
        // 
        if (!strcmp("1I", paras[0x00])) {
            expand_tail(paras + 0x01, paras[0x00]);
            memcpy_o(paras[0x01], obje_oid, sizeof (osv_oid_t));
            // printf("sconv_stati_para_styl, coun:%d\n", paras[0x01][0x01]);
        }
        //
        strcpy(obje_iden, OSDB_DEFAULT_VALUE);
    }
    //
    return 0x00;
}

//
// osev:list(ROLE, "admin");
// odb:list(ROLE, "admin");

// osev:role(ADD, "admin");
// odb:role(ADD, "admin");

// osev:user(ADD, "david", "123456");
// odb:user(ADD, "david", "123456")

//

struct conv_node {
    const char *stri;
    uint32 value;
};

#define PRIVI_VALUE(VALU, STRI, TABLE) { \
    struct conv_node *item; \
    for(item = (struct conv_node *)TABLE; item->stri; ++item) \
        if(!strcmp(item->stri, STRI)) break; \
        VALU |= item->value; \
}

//

static struct conv_node priv_osev_tab[] = {
    {"ALL_PRIVI", SVOD_PRIVI | SVOD_ODBM | SVOD_CLUST}, //
    {"PRIVI", SVOD_PRIVI}, // 
    {"ODBM", SVOD_ODBM}, // 
    {"CLUST", SVOD_CLUST}, // 
    {NULL, 0x00}
};

static struct conv_node priv_odb_tab[] = {
    {"ALL_PRIVI", ODLE_READ | ODLE_WRITE | ODLE_EXECU}, //
    {"READ", ODLE_READ}, // 
    {"WRITE", ODLE_WRITE}, // 
    {"EXECU", ODLE_EXECU}, // 
    {NULL, 0x00}
};

static struct conv_node role_cont_tab[] = {
    {"ALL_PRIVI", COEN_ECHO | COEN_CREAT | COEN_DROP | COEN_FIND | COEN_UPDAT | COEN_INSER | COEN_FACTO | COEN_INVOK}, //
    {"ECHO", COEN_ECHO}, // 
    {"CREAT", COEN_CREAT}, // 
    {"DROP", COEN_DROP}, // 
    {"FIND", COEN_FIND}, // 
    {"UPDAT", COEN_UPDAT}, // 
    {"INSER", COEN_INSER}, // 
    {"FACTO", COEN_FACTO}, // 
    {"INVOK", COEN_INVOK}, // 
    {NULL, 0x00}
};

static char *privi_actio(char *priv_stri, char *privi) {
    char *toksp = privi;
    for (; '|' == toksp[0x00] || ' ' == toksp[0x00] || ',' == toksp[0x00]; toksp++);
    if ('\0' == toksp[0x00]) return NULL;
    char *tokep = strpbrk(toksp + 0x01, "| ,");
    if (tokep) strzcpy(priv_stri, toksp, tokep - toksp);
    else tokep = escpy(priv_stri, toksp);
    //
    return tokep;
}

static uint32 parse_privile(uint32 scop_valu, char *privi) {
    uint32 priv_valu = 0x00;
    char priv_stri[PARAM_LENGTH];
    char *toke = privi;
    //
    if (SCOP_OSDB & scop_valu) {
        while ((toke = privi_actio(priv_stri, toke))) {
            PRIVI_VALUE(priv_valu, priv_stri, priv_odb_tab)
        }
        PRIVI_VALUE(priv_valu, priv_stri, priv_odb_tab)
    } else if (SCOP_EOBJ & scop_valu) {
        while ((toke = privi_actio(priv_stri, toke))) {
            PRIVI_VALUE(priv_valu, priv_stri, role_cont_tab)
        }
        PRIVI_VALUE(priv_valu, priv_stri, role_cont_tab)
    } else if (SCOP_OSEV & scop_valu) {
        while ((toke = privi_actio(priv_stri, toke))) {
            PRIVI_VALUE(priv_valu, priv_stri, priv_osev_tab)
        }
        PRIVI_VALUE(priv_valu, priv_stri, priv_osev_tab)
    }
    //
    return priv_valu;
}

//

static int check_priv_valu(uint32 scop_valu, uint32 priv_valu) {
    if (SCOP_OSDB & scop_valu) {
        if (~(ODLE_READ | ODLE_WRITE | ODLE_EXECU) & priv_valu)
            return -1;
    } else if (SCOP_EOBJ & scop_valu) {
        if (~(COEN_ECHO | COEN_CREAT | COEN_DROP | COEN_FIND | COEN_FACTO | COEN_INVOK) & priv_valu)
            return -1;
    } else if (SCOP_OSEV & scop_valu) {
        if (~(SVOD_PRIVI | SVOD_ODBM | SVOD_CLUST) & priv_valu)
            return -1;
    } else return -1;
    //
    return 0x00;
}

//
static struct paras_node priv_role_tab[] = {
    {"ADD", "1I"}, // ADDI_ROLE
    {"DEL", "2I"}, // DELE_ROLE
    {"GRANT", "3I"}, // GRANT_PRIV
    {"REVOKE", "4I"}, // REVOKE_PRIV
    {NULL, "0I"}
};

// osev:privile:role(GRANT, "rd3", ALL_PRIVI);
// osev:privile:role(REVOKE, "rd3", ALL_PRIVI);
// paras[0x02]:dist_name, paras[0x03]:privi, paras[0x00]:role_type

int pconv_role_para(char **paras, char *obje_iden) {
    PARAS_VALUE(paras[0x00], priv_role_tab);
    //
    uint32 scope_valu = 0x00;
    uint32 priv_valu = 0x00;
    // GRANT_PRIV REVOKE_PRIV
    if (!strcmp("3I", paras[0x00]) || !strcmp("4I", paras[0x00])) {
        scope_valu = parse_dist_scope(paras[0x02], obje_iden);
        // printf("paras[0x02]:%s\n", paras[0x02]);
        if (!scope_valu) return -1;
        priv_valu = parse_privile(scope_valu, paras[0x03]);
        // printf("paras[0x03]:%s priv_valu:%d\n", paras[0x03], priv_valu);
        if (!priv_valu) return -1;
        if (check_priv_valu(scope_valu, priv_valu)) return -1;
        sprintf(paras[0x03], "%uI", scope_valu | priv_valu);
    }
    //
    return 0x00;
}

//
static struct paras_node priv_list_tab[] = {
    {"ROLE", "1I"}, // LIST_ROLE
    {"USER", "2I"}, // LIST_USER
    {NULL, "0I"}
};

static struct paras_node priv_user_tab[] = {
    {"ADD", "1I"}, // ADDI_USER
    {"DEL", "2I"}, // DELE_USER
    {"GRANT", "3I"}, // GRANT_ROLE
    {"REVOKE", "4I"}, // REVOKE_ROLE
    {NULL, "0I"}
};

void pconv_list_para(char **paras) {
    PARAS_VALUE(paras[0x00], priv_list_tab);
}

void pconv_user_para(char **paras) {
    PARAS_VALUE(paras[0x00], priv_user_tab);
    //
    char salt_paswd[SALT_LENGTH + PASWD_LENGTH];
    char *salt = salt_paswd;
    char *password = salt_paswd + SALT_LENGTH;
    //
    if (!strcmp("1I", paras[0x00])) {
        random_salt(salt);
        unsigned char ecb_key[KEY_LENGTH];
        build_authen_key(ecb_key, salt);
        crypto_encode_ecb((unsigned char *) password, (unsigned char *) paras[0x02], ecb_key);
        printf("salt_paswd:%s\n", salt_paswd);
        memcpy_o(paras[0x02], salt_paswd, SALT_LENGTH + PASWD_LENGTH);
    }
}

//
static struct paras_node quer_creat_tab[] = {
    {"witi", "0I"}, // ENGINE_WTIGER
    {NULL, "FFFF"}
};

//

int lconv_foup_para(unsigned int mvalu, char **paras) {
    int conv_valu = 0x00;
    //
    switch (mvalu) {
        case quer_creat:
            quote_decode(paras[0x01]);
            PARAS_VALUE(paras[0x01], quer_creat_tab);
            if (!strcmp("FFFF", paras[0x01])) conv_valu = -1;
            break;
        default:
            break;
    }
    //
    return conv_valu;
}