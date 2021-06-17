
/* 
 * File:   osev_bzl.h
 * Author: James Xu
 *
 * Created on 2017.4.20, AM10:46
 */

#ifndef OSEV_BZL_H
#define OSEV_BZL_H

#include "builtin_command.h"
#include "prepa_prompt.h"
#include "parse_command.h"
#include "parsing.h"
#include "extend.h"
#include "connect.h"
#include "method.h"
#include "execute.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    void completion_caba(const char *buf, linenoiseCompletions *lc);
    extern char* history_table[];

#define LINENOISE_INITIALIZE_BZL(COMPLETION, HISTORY_FILE) \
    linenoiseSetMultiLine(1); \
    linenoiseSetCompletionCallback(COMPLETION); \
    linenoiseHistoryLoad(HISTORY_FILE);

#define LINENOISE_FINALIZE_BZL linenoiseAtExit();

    //
#define OCLIE_HISTORY_ADDI_BZL(LINE_TXT, SHELL_TYPE) \
    char prev_line[LARGE_TEXT_SIZE]; \
    if(SHTP_CLIE == SHELL_TYPE) hide_command(LINE_TXT); \
    if(strcmp(prev_line, LINE_TXT)) { \
        linenoiseHistoryAdd(LINE_TXT); \
        strcpy(prev_line, LINE_TXT); \
        linenoiseFree(LINE_TXT); \
    }

    //
    int creat_shell_bzl();
    void destroy_shell_bzl();

    //
    char *initi_prompt_bzl(uint32 shell_mode);
    char *blank_prompt_bzl(char *prompt, shel_stat_t *shel_stat);
    char *prepa_prompt_bzl(char *prompt, shel_stat_t *shel_stat);

    int valida_command_bzl(osev_command *oscmd, char *comd_stri, shel_stat_t *shel_stat);

    //
#define prepare_method_bzl(oscmd, shel_stat) prepare_method(oscmd, (shel_stat)->shell_mode, (shel_stat)->run_level)

    //
    int method_execute_bzl(shel_resu *resu, shel_stat_t *shel_stat, osev_command *oscmd);
    int finish_method_bzl(osev_command *oscmd, shel_resu *resu);

    //
    extern char* history_dire[];
    extern char* history_level[];
    uint32 shell_status_bzl(shel_stat_t *shel_stat, osev_command *oscmd);

    //
    int finish_cline_bzl(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *line_stri, uint32 shell_mode, uint32 run_level);

    //


#ifdef __cplusplus
}
#endif

#endif /* OSEV_BZL_H */

