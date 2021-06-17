
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party.h"
#include "stri_utili.h"
#include "options.h"
#include "clie_struct.h"

#include "osev_bzl.h"
#include "osev_shell.h"


//

int main(int argc, char** argv) {
    creat_runcomd_directory(history_dire[0x00], history_dire[0x01]);
    if (parse_args(argc, argv)) return 0x01;
    //
    LINENOISE_INITIALIZE_BZL(completion_caba, runcomd_name(history_table[0x00]))
    creat_shell_bzl();
    // inital osev driver
    shel_stat_t shel_stat = {SHTP_CLIE, LEVE_FOUP};
    char *line_stri;
    char comd_stri[PARAM_NUMB][LARGE_TEXT_SIZE];
    shel_resu resu;
    int hand_valu = 0x00;
    //
    resu_initial(&resu);
    char *prompt = initi_prompt_bzl(shel_stat.shell_mode);
    while ((line_stri = linenoise(prompt)) != NULL) {
        // printf("[debug]line_stri:%s\n", line_stri);
        hand_valu = finish_cline_bzl(comd_stri, line_stri, shel_stat.shell_mode, shel_stat.run_level);
        OCLIE_HISTORY_ADDI_BZL(line_stri, shel_stat.shell_mode)
        switch (hand_valu) {
            case 0x01:
                // printf("[debug]hand_valu:0x01\n");
                prompt = blank_prompt_bzl(prompt, &shel_stat);
                continue;
            case 0x02:
                // printf("[debug]hand_valu:0x02\n");
                continue;
            case -1:
                ocliePrintError("Syntactic error!", 0);
                continue;
        }
        //
        osev_command oscmd;
        reset_result(&resu);
        int inde = 0x00;
        for (; '\0' != comd_stri[inde][0x00]; inde++) {
            memset(&oscmd, '\0', sizeof (osev_command));
            if ((hand_valu = valida_command_bzl(&oscmd, comd_stri[inde], &shel_stat))) {
                ocliePrintError("Check method error!", 0);
                break;
            }
            // build query method
            if ((hand_valu = prepare_method_bzl(&oscmd, &shel_stat))) {
                ocliePrintError("Prepare method error!", 0);
                break;
            }
            // handle query from osev
            if ((hand_valu = method_execute_bzl(&resu, &shel_stat, &oscmd))) {
                osevPrintError("OSEV Handle exception!", hand_valu);
                break;
            }
            // finish method
            if ((hand_valu = finish_method_bzl(&oscmd, &resu))) {
                ocliePrintError("Method finish error!", 0);
                break;
            }
            ocliePrintError("OK!", 0);
        }
        //
        if (!hand_valu) {
            if (SHEL_TYPE_EXIT == shell_status_bzl(&shel_stat, &oscmd)) {
                ocliePrintError("Bye!", 0);
                break;
            }
            prompt = prepa_prompt_bzl(prompt, &shel_stat);
            // printf("[debug]prompt:%s\n", prompt); 
        }
    }
    //cleanup osev env
    final_result(&resu);
    destroy_shell_bzl();
    LINENOISE_FINALIZE_BZL
            //
    return 0x00;
}


