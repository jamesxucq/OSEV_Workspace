
/* 
 * File:   prepa_prompt.h
 * Author: James Xu
 *
 * Created on 2016.10.11, PM1:43
 */

#ifndef PREPA_PROMPT_H
#define PREPA_PROMPT_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "clie_struct.h"

    //
#define SHEL_TYPE_EXIT   0xFFFFFFFF
    
    enum shell_type {
        SHTP_CLIE,
        SHTP_OSEV,
        SHTP_LEVE
    };

    enum level_type {
        LEVE_ONE,
        LEVE_TWOP,
        LEVE_THRE,
        LEVE_FOUP
    };

#define LEVEL_EXTEND_SPACE 0x000F0000
#define SET_EXTEND_SPACE(LEVE_CODE) (LEVE_CODE |= 0x000F0000)
#define UNSET_EXTEND_SPACE(LEVE_CODE) (LEVE_CODE &= 0xFFF0FFFF)
#define ONLY_LEVEL_VALUE(LEVE_CODE) (0xFFF0FFFF & LEVE_CODE)
    //
    extern char *cmode_tab[];
    extern char *multi_blank_tab[];

    //
    char *prompt_level(char *prompt, uint32 run_level);


#ifdef __cplusplus
}
#endif

#endif /* PREPA_PROMPT_H */

