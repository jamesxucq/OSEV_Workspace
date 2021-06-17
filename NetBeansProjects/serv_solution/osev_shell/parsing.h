
#ifndef PARSING_H
#define PARSING_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "parse_command.h"

int paras_parsing(char *paras_line, char **paras, char *line_txt);

int finis_cline(char *line_stri, uint32 shell_mode, uint32 run_level);

int parse_command_conte(char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE], char *cline_txt, uint32 shell_mode);

#ifdef __cplusplus
}
#endif

#endif /* PARSING_H */

