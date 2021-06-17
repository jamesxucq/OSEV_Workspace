#include <pthread.h>

#include "commo_header.h"
#include "third_party.h"

#include "clie_obje.h"
#include "parse_command.h"
#include "conve_command.h"
#include "prepa_check.h"
#include "check_command.h"
#include "parsing.h"
#include "osev_bzl.h"

//
char* history_dire[] = {
    ".oclie",
    "oleve"
};

char* history_table[] = {
    "oclie",
    "osev",
    "oleve"
};

char* history_level[] = {
    "lone",
    "ltwop",
    "lthr",
    "lfoup"
};

//

void completion_caba(const char *buf, linenoiseCompletions *lc) {
    if (buf[0x00] == 'c') {
        linenoiseAddCompletion(lc, "clie:");
    } else if (buf[0x00] == 'o') {
        linenoiseAddCompletion(lc, "odb:");
        linenoiseAddCompletion(lc, "osev:");
    }
}

//

int creat_shell_bzl() {
    pthread_mutex_init(&_colle_cache_mutex_, NULL);
    pthread_mutex_lock(&_colle_cache_mutex_);
    _colle_cache_hm_ = create_action(cache_free, CACHE_BACKET_SIZE);
    pthread_mutex_unlock(&_colle_cache_mutex_);
    if (!_colle_cache_hm_) return -1;

    //
    pthread_mutex_init(&_conta_cache_mutex_, NULL);
    pthread_mutex_lock(&_conta_cache_mutex_);
    _conta_cache_hm_ = create_action(cache_free, CACHE_BACKET_SIZE);
    pthread_mutex_unlock(&_conta_cache_mutex_);
    if (!_conta_cache_hm_) return -1;
    //
    printf("check auth cache ok!\n");
    return ERR_SUCCESS; //succ
}

void destroy_shell_bzl() {
    pthread_mutex_lock(&_conta_cache_mutex_);
    if (_conta_cache_hm_) {
        action_dele(_conta_cache_hm_);
        _conta_cache_hm_ = NULL;
    }
    pthread_mutex_unlock(&_conta_cache_mutex_);
    //
    pthread_mutex_destroy(&_conta_cache_mutex_);
}

//

static void print_oscmd(osev_command *oscmd) {
    printf("print_oscmd --------------------\n");
    printf("coline:|%s|\n", oscmd->coline);
    printf("comd_valu:|%d|\n", oscmd->comd_valu);
    printf("obje_iden:|%s|\n", oscmd->obje_iden);
    printf("comd_meth:|%s|\n", oscmd->comd_meth);
    printf("meth_valu:%d\n", oscmd->meth_valu);
    printf("comd_attrib:%d\n", oscmd->comd_attrib);
    //
    int inde = 0x00;
    for (; oscmd->paras[inde] && '\0' != oscmd->paras[inde][0x00]; inde++)
        printf("oscmd->paras[%d]:|%s|\n", inde, oscmd->paras[inde]);
    printf("--------------------\n");
}


//

static int valid_command(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    char *parse_tok = parse_command(oscmd, shell_mode, run_level);
    if (!parse_tok) {
        // fprintf(stderr, "read method error!\n");
        ocliePrintError("Read method error!", 0);
        return -1;
    }
    // print_oscmd(oscmd);
    if (-1 == prepa_check(oscmd, shell_mode, run_level)) {
        ocliePrintError("Prepare check error!", 0);
        return -1;
    }
    //
    char *conve_tok = conve_command(oscmd, shell_mode, run_level);
    if (conve_tok) parse_tok = conve_tok;
    if (-1 == check_method(oscmd, shell_mode, run_level)) {
        // fprintf(stderr, "method not found!\n");
        ocliePrintError("Object or Method not found!", 0);
        return -1;
    }
    print_oscmd(oscmd);
    if (-1 == paras_parsing(oscmd->paras_line, oscmd->paras, parse_tok)) {
        // fprintf(stderr, "parse param error!\n");
        ocliePrintError("Parse param error!", 0);
        return -1;
    }
    printf("valid_command, comd_conte:%s:%s\n", oscmd->obje_iden, oscmd->comd_meth);
    //
    return 0x00;
}

static int valid_extend(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    char *parse_tok = parse_extend(oscmd, shell_mode, run_level);
    if (!parse_tok) {
        // fprintf(stderr, "read method error!\n");
        ocliePrintError("Read method error!", 0);
        return -1;
    }
    if (-1 == check_extend(oscmd, shell_mode, run_level)) {
        // fprintf(stderr, "method not found!\n");
        ocliePrintError("Method not found!", 0);
        return -1;
    }
    if (-1 == paras_parsing(oscmd->paras_line, oscmd->paras, parse_tok)) {
        // fprintf(stderr, "parse param error!\n");
        ocliePrintError("Parse param error!", 0);
        return -1;
    }
    printf("valid_extend, oscmd->coline:%s\n", oscmd->coline);
    //
    return 0x00;
}

int valida_command_bzl(osev_command *oscmd, char *comd_stri, shel_stat_t *shel_stat) {
    int chk_valu = 0x00;
    //
    printf("[debug] valida_command_bzl comd_stri:%s\n", comd_stri);
    if (valid_command_type(oscmd->coline, comd_stri)) {
        printf("extend coline:%s\n", oscmd->coline);
        chk_valu = valid_extend(oscmd, shel_stat->shell_mode, shel_stat->run_level);
    } else {
        printf("coline:%s\n", oscmd->coline);
        chk_valu = valid_command(oscmd, shel_stat->shell_mode, shel_stat->run_level);
    }
    // printf("chk_valu:%d\n", chk_valu);
    return chk_valu;
}

//

void p_command(osev_command *oscmd) {
    printf("oscmd->coline:%s\n", oscmd->coline);
    printf("oscmd->comd_attrib:%08x\n", oscmd->comd_attrib);
    printf("oscmd->comd_valu:%u\n", oscmd->comd_valu);
    printf("oscmd->obje_iden:%s\n", oscmd->obje_iden);
    printf("oscmd->comd_meth:%s\n", oscmd->comd_meth);
    printf("oscmd->meth_valu:%u\n", oscmd->meth_valu);
    printf("oscmd->reserved:%d\n", oscmd->reserved);
}

int method_execute_bzl(shel_resu *resu, shel_stat_t *shel_stat, osev_command *oscmd) {
    p_command(oscmd);
    //
    if (ATTRI_MAJOR & oscmd->comd_attrib) {
        if (method_execute(resu, shel_stat, oscmd)) {
            ocliePrintError("Method execute exception!", 0);
            output_except(resu->resu_data, resu->res_len);
            return -1;
        }
    } else if (ATTRI_EXTEND & oscmd->comd_attrib) {
        if (extend_command(oscmd, resu)) {
            ocliePrintError("Extend command exception!", 0);
            return -1;
        }
    } else {
        ocliePrintError("Execute attribute exception!", 0);
        return -1;
    }
    //
    return 0x00;
}


//

uint32 shell_status_bzl(shel_stat_t *shel_stat, osev_command *oscmd) {
    // printf("[debug]1 shell_status_bzl, shell_mode:%d run_level:%08X\n", shel_stat->shell_mode, shel_stat->run_level);
    _last_shel_stat_.shell_mode = shel_stat->shell_mode;
    _last_shel_stat_.run_level = shel_stat->run_level;
    //
    if (ATTRI_MAJOR & oscmd->comd_attrib) {
        uint32 shell_type = builtin_command(oscmd, shel_stat->shell_mode);
        if (SHEL_TYPE_EXIT == shell_type) return SHEL_TYPE_EXIT;
        if (shell_type != _last_shel_stat_.shell_mode) {
            if (SHTP_LEVE == shell_type)
                linenoiseHistoryReload(levecomd_name(history_table[SHTP_LEVE], history_level[ONLY_LEVEL_VALUE(shel_stat->run_level)]));
            else linenoiseHistoryReload(runcomd_name(history_table[shell_type]));
            shel_stat->shell_mode = shell_type;
        }
        if (SHTP_LEVE == shell_type) {
            uint32 level_type = clie_run_level(oscmd, _last_shel_stat_.run_level);
            if (level_type != _last_shel_stat_.run_level) {
                linenoiseHistoryReload(levecomd_name(history_table[SHTP_LEVE], history_level[ONLY_LEVEL_VALUE(level_type)]));
                printf("[debug] shel_stat->run_level:%08X level_type:%08X\n", shel_stat->run_level, level_type);
                shel_stat->run_level = level_type;
            }
        }
    }
    // printf("[debug]2 shell_status_bzl, shell_mode:%d run_level:%08X\n", shel_stat->shell_mode, shel_stat->run_level);
    return shel_stat->shell_mode;
}

//

int finish_method_bzl(osev_command *oscmd, shel_resu *resu) {
    if (ATTRI_MAJOR & oscmd->comd_attrib) {
        if (finish_method(oscmd, resu)) {
            ocliePrintError("method finish error!", 0);
            return -1;
        }
    } else if (ATTRI_EXTEND & oscmd->comd_attrib) {
        if (finish_extend(oscmd, resu)) {
            ocliePrintError("extend finish error!", 0);
            return -1;
        }
    } else {
        ocliePrintError("finish attribute error!", 0);
        return -1;
    }
    //
    return 0x00;
}

//

int finish_cline_bzl(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *line_stri, uint32 shell_mode, uint32 run_level) {
    static char cline_txt[LARGE_TEXT_SIZE];
    if ('\0' == line_stri[0x00]) return 0x02;
    strcat(cline_txt, line_stri);
    //
    if (parse_command_conte(comd_stri, cline_txt, shell_mode))
        return 0x01;
    //
    int conti_valu = 0x00;
    int inde = 0x00;
    for (; '\0' != comd_stri[inde][0x00] && !conti_valu; inde++) {
        conti_valu |= finis_cline(comd_stri[inde], shell_mode, run_level);
        printf("conti_valu:%d\n", conti_valu);
    }
    switch (conti_valu) {
        case 0x00:
        case -1:
            MKZERO(cline_txt);
            break;
        case 0x01:
            if ('\0' != comd_stri[inde][0x00]) {
                MKZERO(cline_txt);
                conti_valu = -1;
            }
            break;
        case 0x02:
        default:
            break;
    }
    //
    return conti_valu;
}

//

char *initi_prompt_bzl(uint32 shell_mode) {
    return cmode_tab[shell_mode];
}

//

char *blank_prompt_bzl(char *prompt, shel_stat_t *shel_stat) {
    switch (shel_stat->shell_mode) {
        case SHTP_CLIE:
        case SHTP_OSEV:
            prompt = multi_blank_tab[0x00];
            break;
        case SHTP_LEVE:
            switch (ONLY_LEVEL_VALUE(shel_stat->run_level)) {
                case LEVE_ONE:
                case LEVE_THRE:
                    prompt = multi_blank_tab[0x01];
                    break;
                case LEVE_TWOP:
                case LEVE_FOUP:
                    prompt = multi_blank_tab[0x02];
                    break;
            }
            break;
    }
    //
    return prompt;
}

//

char *prepa_prompt_bzl(char *prompt, shel_stat_t *shel_stat) {
    // printf("1 prepa_prompt_bzl, prompt:|%s|, shell_mode:|%d|, run_level:|%08X|\n", prompt, _last_shel_stat_.shell_mode, _last_shel_stat_.run_level);
    if (SHTP_LEVE == shel_stat->shell_mode) {
        if ((_last_shel_stat_.run_level != shel_stat->run_level) || (_last_shel_stat_.shell_mode != shel_stat->shell_mode))
            prompt = prompt_level(prompt, shel_stat->run_level);
        if (_leve_defa_obje_.changed) {
            prompt = prompt_level(prompt, shel_stat->run_level);
            _leve_defa_obje_.changed = 0x00;
        }
    } else if (_last_shel_stat_.shell_mode != shel_stat->shell_mode) prompt = cmode_tab[shel_stat->shell_mode];
    // printf("2 prepa_prompt_bzl, prompt:|%s|, shell_mode:|%d|, run_level:|%08X|\n", prompt, shel_stat->shell_mode, shel_stat->run_level);
    return prompt;
}

