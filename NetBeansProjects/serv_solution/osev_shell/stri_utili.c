#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

#include "commo_header.h"
#include "parse_command.h"
#include"osev_clie.h"
#include "stri_utili.h"

char _runcomd_directory_[PATH_MAX];

int creat_runcomd_directory(char *comd_dire, char *leve_dire) {
    char lcomd_name[PATH_MAX];
    sprintf(_runcomd_directory_, "%s/%s", getenv("HOME"), comd_dire);
    if (access(_runcomd_directory_, F_OK)) {
        if (mkdir(_runcomd_directory_, 0755)) {
            perror("mkdir error!");
            return -1;
        }
        sprintf(lcomd_name, "%s/%s", _runcomd_directory_, leve_dire);
        if (mkdir(lcomd_name, 0755)) {
            perror("mkdir error!");
            return -1;
        }
    }
    return 0x00;
}

char *runcomd_name(char *file_name) {
    static char rcomd_name[PATH_MAX];
    if ('\0' == _runcomd_directory_[0x00]) return NULL;
    sprintf(rcomd_name, "%s/%s", _runcomd_directory_, file_name);
    // printf("[debug]runcomd_name:%s\n", rcmd_name);
    return rcomd_name;
}

char *levecomd_name(char *leve_dire, char *file_name) {
    static char lcomd_name[PATH_MAX];
    if ('\0' == _runcomd_directory_[0x00]) return NULL;
    sprintf(lcomd_name, "%s/%s/%s", _runcomd_directory_, leve_dire, file_name);
    // printf("[debug]runcomd_name:%s\n", rcmd_name);
    return lcomd_name;
}

//

static char *delim_start(char *stri) {
    char *toke = stri;
    for (; isalnum(toke[0x00]) || ('_' == toke[0x00]); toke++);
    return toke;
}

static char *delim_end(char *stri) {
    char *toke = stri;
    for (; '\0' != toke[0x00] && !isalnum(toke[0x00]); toke++);
    return toke;
}


//  0x00:only method / command 0x01:object method

int comd_meth_type(char *stri) {
    if (':' == stri[0x00]) return 0x00;
    char *toksp = delim_start(stri);
    char *tokep = delim_end(toksp);
    if (tokep && toksp) {
        for (; tokep >= toksp; toksp++) {
            if (':' == toksp[0x00]) return 0x01;
        }
    }
    return 0x00;
}

//


#define SPACE_DELIM_TOK ':'

static int check_sptok(char *start, char *end) {
    // printf("start:|%s| end:|%s|\n", start, end);
    if (start == end) return 0x00;
    else if (start && end) {
        for (; end >= start; start++) {
            if (SPACE_DELIM_TOK == start[0x00]) return 0x00;
        }
    }
    //
    return -1;
}

//

static int split_array(char *space_array[SPACE_NUMB], char *stri) {
    char *toke = stri;
    //
    int inde = 0x00;
    for (; '\0' != toke[0x00]; inde++) {
        char *delisp = delim_start(toke);
        char *deliep = delim_end(delisp);
        if (check_sptok(delisp, deliep)) return -1;
        //
        space_array[inde] = toke;
        MKZERO(delisp);
        // printf("space_array[inde]:|%s|\n", space_array[inde]);
        toke = deliep;
    }
    space_array[inde] = NULL;
    //
    return 0x00;
}

static char *space_conte(char *obje_meth, char *stri) {
    char *toksp = stri;
    for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
    //
    char *toke = toksp;
    for (; '\0' != toke[0x00]; ++toke)
        if ('(' == toke[0x00] || '<' == toke[0x00]) break;

    //
    char *tokep = toke;
    for (; toksp != tokep && ' ' == tokep[-1]; tokep--);
    //
    strzcpy(obje_meth, toksp, tokep - toksp);
    return toke;
}

static int creat_space(char *obje, char *metho, char **space_array) {
    char *last_str = obje;
    last_str = lscpy(last_str, space_array[0x00]);
    //
    char **array_tok = space_array + 0x01;
    char *last_tok = array_tok[0x00];
    if (!last_tok) return -1;
    //
    for (array_tok++; array_tok[0x00]; array_tok++) {
        last_str = lccpy(last_str, ':');
        last_str = lscpy(last_str, last_tok);
        last_tok = array_tok[0x00];
    }
    lscpy(metho, last_tok);
    //
    return 0x00;
}

char *split_obje_metho(char *obje, char *metho, char *stri) {
    char obje_meth[OBJE_LENGTH + METH_LENGTH];
    char *parse_tok = space_conte(obje_meth, stri);
    // printf("obje_meth:|%s| stri:|%s|\n", obje_meth, stri);
    char *space_array[SPACE_NUMB];
    if (split_array(space_array, obje_meth)) return NULL;
    //
    if (creat_space(obje, metho, space_array)) return NULL;
    return parse_tok;
}

//

char *method_space(char *name, char *stri) {
    char *toksp, *tokep;
    //
    for (toksp = stri; '\0' != toksp[0x00]; ++toksp)
        if (' ' != toksp[0x00] && ':' != toksp[0x00]) break;
    for (tokep = toksp; '\0' != tokep[0x00]; ++tokep)
        if (' ' == tokep[0x00] || '(' == tokep[0x00] || '<' == tokep[0x00]) break;
    //
    strzcpy(name, toksp, tokep - toksp);
    return tokep;
}

char *next_param(char *para_str, char *stri) {
    char *toksp, *tokep;
    char tok;
    //
    for (toksp = stri; '\0' != toksp[0x00]; toksp++) {
        tok = toksp[0x00];
        if (' ' != tok && '(' != tok && ')' != tok && ',' != tok && ';' != tok && '>' != tok)
            break;
    }
    //
    if ('"' == toksp[0x00]) {
        for (tokep = toksp + 0x01; '"' != tokep[0x00]; tokep++)
            if ('\\' == tokep[0x00]) tokep++;
        ++tokep;
    } else {
        for (tokep = toksp; '\0' != tokep[0x00]; tokep++) {
            tok = tokep[0x00];
            if ('(' == tok || ')' == tok || ',' == tok || ';' == tok)
                break;
        }
    }
    strzcpy(para_str, toksp, tokep - toksp);
    //
    for (; '\0' != tokep[0x00]; tokep++) {
        tok = tokep[0x00];
        if (' ' != tok && '(' != tok && ')' != tok && ',' != tok && ';' != tok && '>' != tok)
            break;
    }
    //
    return tokep;
}

static char *not_blank(char *stri) {
    // printf("[debug]not_blank stri:%s\n", stri);
    char *toke = stri;
    for (; ' ' == toke[0x00] || '\0' == toke[0x00]; ++toke) {
        if ('\0' == toke[0x00])
            return NULL;
    }
    return toke;
}

static char *invoke_token(char *stri) {
    char *toke = stri;
    for (toke = stri; '(' != toke[0x00]; ++toke) {
        if ('\0' == toke[0x00]) {
            return NULL;
        }
    }
    return toke;
}

char *define_token(char *stri) {
    char *toke = stri;
    for (toke = stri; '<' != toke[0x00]; ++toke) {
        if ('\0' == toke[0x00]) {
            return NULL;
        }
    }
    return toke;
}

static char *have_delim(char *stri) {
    char *toke = stri;
    while (' ' == toke[0x00]) toke++;
    if (':' == toke[0x00]) return toke;
    return NULL;
}

// 0:yes -1:no

int accep_clie_metho(char *line_stri, char* obje_ide) {
    char *toke = kill_blank(line_stri);
    if (!toke) return -1;
    //
    if (!strncasecmp(obje_ide, toke, strlen(obje_ide))) {
        toke += strlen(obje_ide);
        if (!(toke = have_delim(toke))) return -1;
        toke++;
    }
    if (invoke_token(++toke)) return 0x00;
    //
    return -1;
}

int accep_osev_metho(char *line_stri, char *clie_obje, char *osev_obje) {
    char *toke = kill_blank(line_stri);
    if (!toke) return -1;
    //
    if (!strncasecmp(clie_obje, toke, strlen(clie_obje))) {
        toke += strlen(clie_obje);
        if (!(toke = have_delim(toke))) return -1;
        toke++;
    } else if (!strncasecmp(osev_obje, toke, strlen(osev_obje))) {
        toke += strlen(osev_obje);
        if (!(toke = have_delim(toke))) return -1;
        toke++;
    }
    if (invoke_token(++toke)) return 0x00;
    //
    return -1;
}

// 0:yes -1:no

int accep_osdb_metho(char *line_stri, char *clie_obje, char *osdb_obje, char *exte_obje) {
    char *toke = kill_blank(line_stri);
    if (!toke) return -1;
    printf("[debug]is_level_method toke:%s\n", toke);
    if (!strncasecmp(clie_obje, toke, strlen(clie_obje))) {
        toke += strlen(clie_obje);
    } else if (!strncasecmp(osdb_obje, toke, strlen(osdb_obje))) {
        toke += strlen(osdb_obje);
    } else if (!strncasecmp(exte_obje, toke, strlen(exte_obje))) {
        toke += strlen(exte_obje);
    } else return -1;
    //
    if (!(toke = have_delim(toke))) return -1;
    if (invoke_token(toke + 0x02)) return 0x00;
    //
    return -1;
}

// 0:yes -1:no

int accep_user_metho(char *line_stri) {
    char *toke = kill_blank(line_stri);
    if (!toke) return -1;
    if (strchr(toke, ':')) {
        if (invoke_token(toke + 0x02)) return 0x00;
    }
    return -1;
}

// 0:yes -1:no

int is_defin_class(char *line_stri) {
    static int end_step;
    char *tokep = kill_blank(line_stri);
    if (!tokep) return -1;
    //
    if (!end_step) {
        tokep = strchr(tokep, '<');
        if (tokep++) end_step = 0x01;
    }
    if (0x01 == end_step) {
        tokep = strchr(tokep, '>');
        if (tokep++) end_step = 0x02;
    }
    if (0x02 == end_step) {
        if (strchr(tokep, ';')) {
            end_step = 0x00;
            return 0x00;
        }
    }
    //
    return -1;
}

// 0:yes -1:no

int is_defin_metho(char *line_stri) {
    static int end_step;
    char *tokep = kill_blank(line_stri);
    if (!tokep) return -1;
    //
    if (!end_step) {
        tokep = strchr(tokep, '<');
        if (tokep++) end_step = 0x01;
    }
    if (0x01 == end_step) {
        tokep = strchr(tokep, '>');
        if (tokep++) end_step = 0x02;
    }
    if (0x02 == end_step) {
        if (strchr(tokep, '{')) {
            end_step = 0x00;
            return 0x00;
        }
    }
    //
    return -1;
}

int is_opera_obje(char *line_stri) {
    char *toke = kill_blank(line_stri);
    if (!toke) return -1;
    toke = strchr(toke, ':');
    if (toke) return 0x00;
    return -1;
}

int is_opera_conta(char *line_stri) {
    char *toke = kill_blank(line_stri);
    if (!toke) return -1;
    toke = strchr(++toke, ':');
    if (toke) return 0x00;
    return -1;
}

//
// 0:finish 0x01:continue -1:error 

int invok_metho_finis(char *line_stri) {
    static int end_step;
    //
    // printf("[debug]invok_metho_finis line_stri:%s\n", line_stri);
    char *tokep = line_stri;
    if (!end_step) {
        tokep = strchr(tokep, ')');
        // printf("[debug]invok_metho_finis tokep:%s\n", tokep);
        if (tokep++) end_step = 0x01;
    }
    if (0x01 == end_step) {
        tokep = strchr(tokep, ';');
        // printf("[debug]invok_metho_finis tokep:%s\n", tokep);
        if (tokep++) end_step = 0x02;
    }
    if (0x02 == end_step) {
        end_step = 0x00;
        if (not_blank(tokep)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

// NUll:continue 0x333:finish

static char* check_couple(char *stri) {
    static int couple_deep;
    char *lastchr = NULL;
    char *toke = stri;
    //
    for (; '\0' != toke[0x00]; ++toke) {
        if ('\\' == *toke) toke++;
        else if ('"' == toke[0x00]) {
            for (toke++; '"' != toke[0x00]; toke++)
                if ('\\' == toke[0x00]) toke++;
        } else if ('{' == toke[0x00]) ++couple_deep;
        else if ('}' == toke[0x00]) {
            lastchr = toke;
            --couple_deep;
        }
    }
    //
    if (!couple_deep) return lastchr;
    return NULL;
}

int class_defin_finis(char *line_stri) {
    static int end_step;
    //
    char *tokep = line_stri;
    if (!end_step) {
        tokep = strchr(tokep, ';');
        if (tokep++) end_step = 0x01;
    }
    if (0x01 == end_step) {
        end_step = 0x00;
        if (not_blank(tokep)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

int metho_defin_finis(char *line_stri) {
    static int end_step;
    //
    char *tokep = line_stri;
    if (!end_step) {
        if (strchr(tokep, '{')) end_step = 0x01;
    }
    if (0x01 == end_step) {
        tokep = check_couple(tokep);
        if (tokep++) end_step = 0x02;
    }
    if (0x02 == end_step) {
        end_step = 0x00;
        if (not_blank(tokep)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

int opera_objec_finis(char *line_stri) {
    static int end_step;
    //
    char *tokep = line_stri;
    if (!end_step) {
        tokep = strchr(tokep, ';');
        if (tokep++) end_step = 0x01;
    }
    if (0x01 == end_step) {
        end_step = 0x00;
        if (not_blank(tokep)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

int opera_conta_finis(char *line_stri) {
    static int end_step;
    //
    char *tokep = line_stri;
    if (!end_step) {
        tokep = strchr(tokep, ';');
        if (tokep++) end_step = 0x01;
    }
    if (0x01 == end_step) {
        end_step = 0x00;
        if (not_blank(tokep)) return -1;
        else return 0x00;
    }
    //
    return 0x01;
}

//
// osvp://james:123456@192.168.1.105:8888
#define OSVP_HEAD "osvp://"
#define HEAD_LENG 0x07

char *hide_command(char *line_stri) {
    char *toke = line_stri;
    toke = strstr(toke, OSVP_HEAD);
    if (!toke) return NULL;
    toke = strchr(toke + HEAD_LENG, ':');
    if (!toke) return NULL;
    if (!strchr(++toke, '@')) return NULL;
    for (; '@' != toke[0x00]; toke++) toke[0x00] = '*';
    //
    return line_stri;
}

//

char *have_nspace(char *para_str) {
    char *toke = para_str;
    for (; '\0' != toke[0x00]; toke++) {
        if (':' == toke[0x00]) return toke;
    }
    return NULL;
}

//
#define LEVE_OBJE_TOK "odb"
static char *lev12p_osdb_comd_tab[] = {"echo", "create", "drop", "replace", "integri", "reload", NULL};

#define LEVE_CLIE_TOK "clie"
static char *lev12p_clie_comd_tab[] = {"level", "quit", NULL};

int creat_class_metho(char *obje, char *metho) {
    char **toke;
    if (!strcasecmp(LEVE_OBJE_TOK, obje)) {
        toke = lev12p_osdb_comd_tab;
        for (; toke[0x00]; toke++) {
            if (!strcasecmp(metho, toke[0x00])) return 0x01;
        }
    }
    if (!strcasecmp(LEVE_CLIE_TOK, obje)) {
        toke = lev12p_clie_comd_tab;
        for (; toke[0x00]; toke++) {
            if (!strcasecmp(metho, toke[0x00])) return 0x01;
        }

    }
    //
    return 0x00;
}

//

int have_defa_obje(char *line_stri) {
    char *toke = line_stri;
    for (; (' ' == toke[0x00]) && ('\0' != toke[0x00]); toke++);
    if (':' == toke[0x00]) return 0x00;
    //
    return 0x01;
}

//

int check_redirect_obje(char *line_stri) {
    char *toke = qstrch(line_stri + 0x01, ':');
    if (!toke) return -1;
    //
    toke = qstrch(toke + 0x01, '(');
    if (!toke) return -1;
    toke = qstrch(toke + 0x01, ')');
    if (!toke) return -1;
    toke = qstrch(toke + 0x01, '>');
    if (!toke) return -1;
    toke = qstrch(toke + 0x01, ';');
    if (!toke) return -1;
    //
    return 0x00;
}

//

int single_command(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *cline_stri) {
    lscpy(comd_stri[0x00], cline_stri);
    comd_stri[0x01][0x00] = '\0';
    return 0x00;
}

int multi_command(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *cline_stri) {
    char *toksp = cline_stri;
    char *pipe_toke = qstrch(toksp, '|');
    int inde = 0x00;
    for (; pipe_toke; inde++) {
        char *last_str = lszcpy(comd_stri[inde], toksp, pipe_toke - toksp);
        lccpy(last_str, ';');
        toksp = pipe_toke + 0x01;
        pipe_toke = qstrch(toksp, '|');
    }
    lscpy(comd_stri[inde], toksp);
    inde++;
    comd_stri[inde][0x00] = '\0';
    //
    return 0x00;
}

//

char *analy_const_eobje_exte(char *paras_str, char *line_stri) {
    char *toksp = qstrch(line_stri, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(paras_str, toksp, tokep - toksp);
    //
    return paras_str;
}

//

char *analy_const_eobje_redi(char *redi_obje, char *paras_str, char *line_stri) {
    char *toksp = qstrch(line_stri, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(paras_str, toksp, tokep - toksp);
    //
    toksp = qstrch(tokep + 0x01, '>');
    if (!toksp) return NULL;
    for (toksp++; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
    tokep = qstrch(toksp + 0x01, ';');
    if (!tokep) return NULL;
    for (; toksp != tokep && ' ' == tokep[-1]; tokep--);
    strzcpy(redi_obje, toksp, tokep - toksp);
    //
    return redi_obje;
}

//
// rive:rive("tvtv", "test") > odb;
// odb:create("tvtv", "rive", "test");

char *analy_const_cobje(char *redi_obje, char *paras_str, char *line_stri, char *clasn) {
    char coline[PARAM_NUMB * PARAM_LENGTH];
    char *toksp = qstrch(line_stri, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(coline, toksp, tokep - toksp);
    //
    char *deli_tok = qstrch(coline, ',');
    if (!deli_tok) return NULL;
    deli_tok++;
    char *last_str = lszcpy(paras_str, coline, deli_tok - coline);
    last_str = lsprif(last_str, " \"%s\",", clasn);
    last_str = lscpy(last_str, deli_tok);
    //
    toksp = qstrch(tokep + 0x01, '>');
    if (!toksp) return NULL;
    for (toksp++; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
    tokep = qstrch(toksp + 0x01, ';');
    if (!tokep) return NULL;
    for (; toksp != tokep && ' ' == tokep[-1]; tokep--);
    strzcpy(redi_obje, toksp, tokep - toksp);
    //
    return redi_obje;
}

// xxx:open("12p34p");

char *analy_statu_open(char *paras_str, char *line_stri, char *obje_iden) {
    char coline[PARAM_NUMB * PARAM_LENGTH];
    char *toksp = qstrch(line_stri, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(coline, toksp, tokep - toksp);
    //
    char *last_str = lsprif(paras_str, "\"%s\",", obje_iden);
    lscpy(last_str, coline);
    //
    return paras_str;
}

//

char *analy_statu_stati(char *paras_str, char *line_stri, char *obje_iden) {
    char coline[PARAM_NUMB * PARAM_LENGTH];
    char *toksp = qstrch(line_stri, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(++toksp, ')');
    if (!tokep) return NULL;
    lszcpy(coline, toksp, tokep - toksp);
    //
    char *deli_tok = qstrch(coline, ',');
    if (deli_tok) {
        deli_tok++;
        char *last_str = lszcpy(paras_str, coline, deli_tok - coline);
        last_str = lsprif(last_str, " \"%s\", %s", obje_iden, deli_tok);
    } else lsprif(paras_str, "%s, \"%s\"", coline, obje_iden);
    //
    return paras_str;
}

//

char *find_paras_conte(char *paras, char *coline) {
    char *toksp = qstrch(coline, '(');
    if (!toksp) return NULL;
    char *tokep = qstrch(toksp + 0x01, ')');
    if (!tokep) return NULL;
    //
    strzcpy(paras, toksp + 0x01, tokep - toksp - 0x01);
    quote_decode(paras);
    return paras;
}

//

static char *split_host(serv_addr *saddr, char *stri) {
    char *delmi = strchr(stri, ':');
    if (delmi) {
        delmi[0x00] = '\0';
        strcpy(saddr->sin_addr, stri);
        saddr->sin_port = atoi(++delmi);
    } else {
        strcpy(saddr->sin_addr, stri);
        saddr->sin_port = OSEV_DEFAULT_PORT;
    }
    return stri;
}

static char *split_user(char *user_name, char *password, char *stri) {
    char *delmi = strchr(stri, ':');
    if (!delmi) return NULL;
    delmi[0x00] = '\0';
    strcpy(user_name, stri);
    strcpy(password, ++delmi);
    return delmi;
}

static char *split_osdb(char *osev_osdb, char *stri) {
    strcpy(osev_osdb, stri);
    return osev_osdb;
}

// osvp://james:123456@192.168.1.105:8888/odb
#define OSVP_HEAD "osvp://"
#define HEAD_LENG 0x07

static int split_uristr(serv_addr *saddr, struct auth_dat *auth, char *osev_osdb, const char *uri_stri) {
    char conne_str[URI_LENGTH];
    char *toksp, *tokep, *tokde;
    //
    toksp = strstr(uri_stri, OSVP_HEAD);
    if (!toksp) return URISTR_ILLEGAL;
    strcpy(conne_str, uri_stri + HEAD_LENG);
    toksp = conne_str;
    //
    tokep = strchr(toksp, '@');
    tokde = strchr(toksp, '/');
    if (tokep && tokde) {
        tokep[0x00] = '\0';
        tokde[0x00] = '\0';
        if (!split_user(auth->user_name, auth->pass_word, toksp))
            return URISTR_ILLEGAL;
        split_host(saddr, tokep + 0x01);
        split_osdb(osev_osdb, tokde + 0x01);
        return USER_HOST_OSDB;
    } else if (tokep && !tokde) {
        tokep[0x00] = '\0';
        if (!split_user(auth->user_name, auth->pass_word, toksp))
            return URISTR_ILLEGAL;
        split_host(saddr, tokep + 0x01);
        osev_osdb[0x00] = '\0';
        return USER_HOST_URI;
    } else if (!tokep && tokde) {
        tokde[0x00] = '\0';
        split_host(saddr, toksp);
        split_osdb(osev_osdb, tokde + 0x01);
        return HOST_OSDB_URI;
    } else if (!tokep && !tokde) {
        split_host(saddr, toksp);
        osev_osdb[0x00] = '\0';
        return HOST_ONLY_URI;
    }
    //
    return URISTR_ILLEGAL;
}

//

char *split_uristr_osdb(char *osev_osdb, const char *uri_stri) {
    char *toksp, *tokep;
    //
    toksp = strstr(uri_stri, OSVP_HEAD);
    if (!toksp) return NULL;
    toksp += HEAD_LENG;
    //
    tokep = strchr(toksp, '/');
    if (tokep) split_osdb(osev_osdb, tokep + 0x01);
    else if (!tokep) osev_osdb[0x00] = '\0';
    //
    return osev_osdb;
}

//

int parse_conne_uristr(svod_auth *clie_auth, const char *uri_stri) {
    char osev_osdb[OSEV_LENGTH];
    int paval = split_uristr(&clie_auth->saddr, &clie_auth->auth, osev_osdb, uri_stri);
    printf("[DEBUG] uri_stri:|%s|\n", uri_stri);
    printf("[DEBUG] _osev_osdb_:|%s| user_name:|%s| password:|%s|\n", osev_osdb, clie_auth->auth.user_name, clie_auth->auth.pass_word);
    printf("[DEBUG] sin_addr:%s sin_port:%d\n", clie_auth->saddr.sin_addr, clie_auth->saddr.sin_port);
    if (URISTR_ILLEGAL == paval) return URISTR_ILLEGAL;
    if (osev_osdb[0x00]) sprintf(clie_auth->osev_osdb, "%s", osev_osdb);
    else strcpy(clie_auth->osev_osdb, OSEV_DEFAULT_VALUE);
    //
    return paval;
}

//

void osevPrintError(char *err_labe, int err_num) {
    fprintf(stderr, OCLIE_TABLE"%s\n", err_labe);
}

void ocliePrintError(char *err_labe, int err_num) {
    // fprintf(stderr, "\033[0;34;47m%s\033[0m", err_labe);
    fprintf(stderr, OCLIE_TABLE"%s\n", err_labe);
}

//

char *inser_tail(char **stri, char *posi) {
    char **toke = stri;
    //
    for (; toke[0x00] && posi != toke[0x00]; toke++);
    if (!toke[0x00]) return NULL;
    //
    for (; stri != toke; toke--)
        toke[0x00] = toke[-1];
    toke[0x00] = posi;
    //
    return posi;
}

//

void comple_osev_iden(char *obje, char *packa) {
    char ostri[OBJE_LENGTH];
    strcpy(ostri, obje);
    char *last_str = lscpy(obje, packa);
    last_str = lccat(last_str, ':');
    lscat(last_str, ostri);
}

//
static osv_str_t odb_stri = osv_stri("odb");
static osv_str_t clie_stri = osv_stri("clie");
static osv_str_t *exce_iden_tab[] = {&odb_stri, &clie_stri, NULL};

int valid_osev_iden(char *obje) {
    osv_str_t **toke = exce_iden_tab;
    for (; toke[0x00]; toke++) {
        if (!strncmp(obje, toke[0x00]->data, toke[0x00]->len)) return 0x01;
    }
    //
    return 0x00;
}