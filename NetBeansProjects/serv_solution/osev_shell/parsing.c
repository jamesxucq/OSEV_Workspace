
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "stri_utili.h"
#include "prepa_prompt.h"

#include "parsing.h"

int paras_parsing(char *paras_line, char **paras, char *line_txt) {
    char *parse_tok = line_txt;
    char para_str[PARAM_LENGTH];
    // printf("[debug]param_parsing line_txt:|%s|\n", line_txt);
    char *last_str = paras_line;
    char **paras_tok = paras;
    //
    int inde = 0x00;
    for (; ('\0' != parse_tok[0x00]) && PARAM_NUMB > inde; inde++, paras_tok++) {
        parse_tok = next_param(para_str, parse_tok);
        // printf("[debug]param_parsing parse_tok:|%s|\n", parse_tok);
        if ('\0' == para_str[0x00]) break;
        lscpy_o(paras_tok[0x00], para_str, last_str);
        // printf("[debug]param_parsing paras_tok[0x00]:|%s|\n", paras_tok[0x00]);
    }
    paras_tok[0x00] = NULL;
    //
    return 0x00;
}

//
static char* objtit_tab[] = {
    "clie",
    "osev",
    "odb",
    "extend"
};

int cline_leve1(char *line_stri) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        if (!accep_osdb_metho(line_stri, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_defin_metho(line_stri)) continue_step = 0x02;
        else continue_type = -1;
    }
    //
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_stri);
            break;
        case 0x02:
            continue_type = metho_defin_finis(line_stri);
            break;
    }
    //
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

int cline_leve2p(char *line_stri) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        if (!accep_osdb_metho(line_stri, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_defin_metho(line_stri)) continue_step = 0x02;
        else if (!is_defin_class(line_stri)) continue_step = 0x03;
        else continue_type = -1;
    }
    //
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_stri);
            break;
        case 0x02:
            continue_type = metho_defin_finis(line_stri);
            break;
        case 0x03:
            continue_type = class_defin_finis(line_stri);
            break;
    }
    //
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

int cline_leve3(char *line_stri) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        if (!accep_osdb_metho(line_stri, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_opera_obje(line_stri)) continue_step = 0x02;
        else continue_type = -1;
    }
    //
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_stri);
            break;
        case 0x02:
            continue_type = opera_objec_finis(line_stri);
            break;
    }
    //
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

int cline_leve4p(char *line_stri) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        if (!accep_osdb_metho(line_stri, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_opera_conta(line_stri)) continue_step = 0x02;
        else continue_type = -1;
    }
    //
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_stri);
            break;
        case 0x02:
            continue_type = opera_conta_finis(line_stri);
            break;
    }
    //
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

int level_check_line(char *line_stri, uint32 run_level) {
    static int conti_valu; // 0x00:cmd 0x01:continue -1:error
    printf("[debug]level_check_line run_level:%08X line_stri:|%s|\n", run_level, line_stri);
    //
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LEVE_ONE:
            conti_valu = cline_leve1(line_stri);
            break;
        case LEVE_TWOP:
            conti_valu = cline_leve2p(line_stri);
            break;
        case LEVE_THRE:
            conti_valu = cline_leve3(line_stri);
            break;
        case LEVE_FOUP:
            conti_valu = cline_leve4p(line_stri);
            break;
    }
    //
    printf("[debug]level_check_line conti_valu:%d\n", conti_valu);
    return conti_valu;
}

int clie_check_line(char *line_stri) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        // printf("[debug]clie_check_line 1:%d\n", continue_type);
        if (!accep_clie_metho(line_stri, objtit_tab[0x00])) {
            continue_step = 0x01;
            // printf("[debug]clie_check_line 2:%d\n", continue_type);
        } else continue_type = 0x00;
    }
    if (0x01 == continue_step) {
        // printf("[debug]clie_check_line 3:%d\n", continue_type);
        continue_type = invok_metho_finis(line_stri);
    }
    // printf("[debug]continue_type:%d\n", continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

int osev_check_line(char *line_stri) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        // printf("[debug]osev_check_line 1\n");
        if (!accep_osev_metho(line_stri, objtit_tab[0x00], objtit_tab[0x01]) ||
                !accep_user_metho(line_stri)) {
            continue_step = 0x01;
            // printf("[debug]osev_check_line 2\n");
        } else continue_type = -1;
    }
    if (0x01 == continue_step) {
        // printf("[debug]osev_check_line 3\n");
        continue_type = invok_metho_finis(line_stri);
    }
    // printf("[debug]continue_type:%d\n", continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

// 0:end 1:contine 0x02:exception -1:error

int finis_cline(char *line_stri, uint32 shell_mode, uint32 run_level) {
    int conti_valu = 0x00; //0x00:cmd 0x01:continue -1:error
    switch (shell_mode) {
        case SHTP_LEVE:
            conti_valu = level_check_line(line_stri, run_level);
            break;
        case SHTP_OSEV:
            conti_valu = osev_check_line(line_stri);
            break;
        case SHTP_CLIE:
            conti_valu = clie_check_line(line_stri);
            break;
    }
    // printf("[debug]finish_statem conti_valu:%d\n", conti_valu);
    return conti_valu;
}

//
// 0:end 1:contine 0x02:exception -1:error

int parse_command_conte(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *cline_txt, uint32 shell_mode) {
    int conte_valu = 0x00; //0x00:cmd 0x01:continue -1:error
    switch (shell_mode) {
        case SHTP_CLIE:
            conte_valu = single_command(comd_stri, cline_txt);
            break;
        case SHTP_OSEV:
        case SHTP_LEVE:
            conte_valu = multi_command(comd_stri, cline_txt);
            break;
    }
    //
    return conte_valu;
}