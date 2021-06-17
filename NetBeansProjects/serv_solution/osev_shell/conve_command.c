
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stri_utili.h"
#include "prepa_prompt.h"
#include "conve_command.h"
#include "defau_utili.h"
#include "conv_echo.h"
#include "clie_obje.h"

//

/*
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
 */

// test:test(777, "first");
// test:test(333, "second") > mycon;

char *conve_command(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    // printf("---------- conve start\n");
    // print_oscmd(oscmd);
    char *line_stri = oscmd->coline;
    char *conve_tok = NULL;
    //
    if (SHTP_LEVE == shell_mode) {
        switch (ONLY_LEVEL_VALUE(run_level)) {
            case LEVE_ONE:
                if (!creat_class_metho(oscmd->obje_iden, oscmd->comd_meth)) {
                    if ((LEVEL_EXTEND_SPACE & run_level) && !have_defa_obje(line_stri)) {
                        conve_tok = echo_creat_metho_exte(oscmd->obje_iden, oscmd->comd_meth, line_stri);
                    } else conve_tok = echo_creat_metho(oscmd->obje_iden, oscmd->comd_meth, line_stri);
                }
                break;
            case LEVE_TWOP:
                if (!creat_class_metho(oscmd->obje_iden, oscmd->comd_meth))
                    conve_tok = echo_creat_class(oscmd->obje_iden, oscmd->comd_meth, line_stri);
                break;
            case LEVE_THRE:
                if (LEVEL_EXTEND_SPACE & run_level) {
                    if (!is_creat_obje(oscmd->obje_iden, oscmd->comd_meth))
                        conve_tok = echo_creat_eobje_exte(oscmd->obje_iden, oscmd->comd_meth, line_stri);
                } else if (!check_redirect_obje(line_stri)) {
                    if (!is_creat_obje(oscmd->obje_iden, oscmd->comd_meth))
                        conve_tok = echo_creat_eobje_redi(oscmd->obje_iden, oscmd->comd_meth, line_stri);
                }
                break;
            case LEVE_FOUP:
                if (!check_redirect_obje(line_stri)) {
                    if (!is_creat_obje(oscmd->obje_iden, oscmd->comd_meth))
                        conve_tok = echo_creat_cobje(oscmd->obje_iden, oscmd->comd_meth, line_stri);
                }
                break;
        }
    }
    printf("---------- conve end\n");
    // print_oscmd(oscmd);
    return conve_tok;
}


//
