
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "shel_macro.h"
#include "stri_utili.h"
#include "clie_obje.h"
#include "prepa_prompt.h"
#include "parse_command.h"
#include "clie_struct.h"

//

//

static char *split_command(char *obje, char *metho, char *line_stri, uint32 shell_mode, uint32 run_level) {
    char *parse_tok = kill_blank(line_stri);
    // 0x00:object method 0x01:only method 0x02:command
    switch (comd_meth_type(parse_tok)) {
        case 0x00:
        {
            switch (shell_mode) {
                case SHTP_LEVE:
                {
                    if (LEVEL_EXTEND_SPACE & run_level) strcpy(obje, _leve_defa_obje_.obje_iden);
                    else strcpy(obje, OSDB_DEFAULT_VALUE);
                    printf("split_command, run_level:%08X, obje:%s\n", run_level, obje);
                    break;
                }
                case SHTP_OSEV:
                    strcpy(obje, OSEV_DEFAULT_VALUE);
                    break;
                case SHTP_CLIE:
                    strcpy(obje, CLIE_DEFAULT_VALUE);
                    break;
            }
            // printf("[debug]split_command, cmd parse_tok:%s\n", parse_tok);
            parse_tok = method_space(metho, parse_tok);
            // printf("[debug]split_command, cmd parse_tok:%s\n", parse_tok);
        }
            break;
        case 0x01:
            // printf("[debug]split_command, method parse_tok:%s\n", parse_tok);
            parse_tok = split_obje_metho(obje, metho, parse_tok);
            if ((SHTP_OSEV == shell_mode) && !valid_osev_iden(obje))
                comple_osev_iden(obje, OSEV_DEFAULT_VALUE);
            // printf("[debug]split_command, method parse_tok:%s\n", parse_tok);
            break;
    }
    //
    return parse_tok;
}

//

struct coupl_node {
    const char *str1;
    const char *str2;
    int value;
    int attri;
};


#define COUPLE_VALUE(VALUE, ATTRI, TABLE, STR1, STR2) { \
    struct coupl_node *item; \
    for(item = (struct coupl_node *)TABLE; item->str1 && item->str2; ++item) \
        if(!strcasecmp(item->str1, STR1) && !strcasecmp(item->str2, STR2)) break; \
    VALUE = item->value; \
    ATTRI = item->attri; \
}

#define COMD_VALUE(DISTI, VALUE, TABLE, STR1) { \
    char **item; \
    for(item = (char **)TABLE; item[0x00]; ++item) { \
        if(!strcasecmp(item[0x00], STR1)) { \
            DISTI = VALUE; \
            break; \
        } \
    } \
}

//

static const struct coupl_node shel_clie_tab[] = {
    {"clie", "conne", comd_conne, ATTRI_MAJOR},
    {"clie", "exit", comd_exit, ATTRI_MAJOR},
    {"clie", "bye", comd_bye, ATTRI_MAJOR},
    {NULL, NULL, comd_clie, ATTRI_INVALID}
};

//

static const struct coupl_node shel_osev_tab[] = {
    {"clie", "exit", comd_exit, ATTRI_MAJOR},
    {"clie", "use", comd_use, ATTRI_MAJOR},
    {"clie", "quit", comd_quit, ATTRI_MAJOR},
    {NULL, NULL, comd_inval, ATTRI_INVALID}
};

static char *osev_cstat_tab[] = {"echo", "open", "close", "status", "stati", NULL};
static osv_str_t PRIVILE_TOK = osv_stri("privile");
static osv_str_t MANAGE_TOK = osv_stri("manage");

//

static const struct coupl_node shel_leve_tab[] = {
    {"clie", "level", comd_level, ATTRI_MAJOR},
    {"clie", "quit", comd_quit, ATTRI_MAJOR},
    {NULL, NULL, comd_leve, ATTRI_INVALID}
};

//

char *parse_command(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    char *parse_tok = split_command(oscmd->obje_iden, oscmd->comd_meth, oscmd->coline, shell_mode, run_level);
    if (!parse_tok) return NULL;
    // printf("[debug]parse_command, shell_mode:%d cmd:%s\n", shell_mode, oscmd->comd_conte);
    if (SHTP_LEVE == shell_mode) {
        COUPLE_VALUE(oscmd->comd_valu, oscmd->comd_attrib, shel_leve_tab, oscmd->obje_iden, oscmd->comd_meth)
    } else if (SHTP_OSEV == shell_mode) {
        COUPLE_VALUE(oscmd->comd_valu, oscmd->comd_attrib, shel_osev_tab, oscmd->obje_iden, oscmd->comd_meth)
        if (comd_inval == oscmd->comd_valu) {
            COMD_VALUE(oscmd->comd_valu, comd_stat, osev_cstat_tab, oscmd->comd_meth)
            if (comd_inval == oscmd->comd_valu) {
                if (!strcmp(oscmd->obje_iden + (strlen(oscmd->obje_iden) - PRIVILE_TOK.len), PRIVILE_TOK.data))
                    oscmd->comd_valu = comd_priv;
                else if (!strcmp(oscmd->obje_iden + (strlen(oscmd->obje_iden) - MANAGE_TOK.len), MANAGE_TOK.data))
                    oscmd->comd_valu = comd_mana;
            }
        }
    } else if (SHTP_CLIE == shell_mode) {
        COUPLE_VALUE(oscmd->comd_valu, oscmd->comd_attrib, shel_clie_tab, oscmd->obje_iden, oscmd->comd_meth)
    }
    //
    printf("[debug]parse_command, obje_iden:%s comd_valu:%d comd_meth:%s\n", oscmd->obje_iden, oscmd->comd_valu, oscmd->comd_meth);
    return parse_tok;
}

//

// obje:find() | clie:pretty("iih"); // fix me
// odb:echo() | extend:convert(GCC); // fix me
// odb:echo() | extend:convert("xxxx.cpp", MSVC); // fix me
// odb:echo() | extend:convert("xxx.java"); // fix me
#define EXTEND_TOK  "extend:"

int valid_command_type(char *comd_line, char *cline_stri) {
    strcpy(comd_line, kill_blank(cline_stri));
    int type_valu = 0x00;
    if (qstrst(cline_stri, EXTEND_TOK)) type_valu = 0x01;
    return type_valu;
}

//

static const struct coupl_node shel_exte_tab[] = {
    {"extend", "list", come_list, ATTRI_EXTEND},
    {"extend", "load", come_load, ATTRI_EXTEND},
    {"extend", "save", come_save, ATTRI_EXTEND},
    {"extend", "conve", come_conv, ATTRI_EXTEND},
    {"extend", "pretty", come_pret, ATTRI_EXTEND},
    {NULL, NULL, come_inval, ATTRI_INVALID}
};

char *parse_extend(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    char *parse_tok = split_command(oscmd->obje_iden, oscmd->comd_meth, oscmd->coline, shell_mode, run_level);
    if (!parse_tok) return NULL;
    // printf("[debug]parse_command, shell_mode:%d cmd:%s\n", shell_mode, oscmd->comd_conte);
    if (SHTP_LEVE == shell_mode) {
        COUPLE_VALUE(oscmd->comd_valu, oscmd->comd_attrib, shel_exte_tab, oscmd->obje_iden, oscmd->comd_meth)
        oscmd->meth_valu = -1;
    }
    //
    printf("[debug]parse_extend, cmde_valu:%d line_stri:%s\n", oscmd->comd_valu, oscmd->coline);
    return parse_tok;
}
