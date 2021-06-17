
#include "commo_header.h"
#include "prepa_prompt.h"
#include "parse_command.h"
#include "clie_obje.h"

#include "prepa_check.h"

//

static int prchk_leve(osev_command *oscmd, uint32 run_level) {
    int leve_valu = 0x00;
    printf("prchk_leve comd_conte:%s:%s run_level:%08X\n", oscmd->obje_iden, oscmd->comd_meth, run_level);
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LEVE_ONE:
            if (LEVEL_EXTEND_SPACE & run_level) {
                printf("obje_iden:%s:%s\n", _leve_defa_obje_.obje_iden, oscmd->obje_iden);
                if (strcmp(_leve_defa_obje_.obje_iden, oscmd->obje_iden)) leve_valu = -1;
            }
            break;
        case LEVE_TWOP:
        case LEVE_THRE:
        case LEVE_FOUP:
            break;
        default:
            leve_valu = -1;
            break;
    }
    //
    printf("check_leve meth_valu:%d reserved:%d leve_valu:%d\n", oscmd->meth_valu, oscmd->reserved, leve_valu);
    return leve_valu;
}

//
static command leve_ctype_tab[] = {
    comd_quit,
    comd_level,
    comd_leve,
    -1
};

int prepa_check(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    int chk_valu = -1;
    command *comd_valu;
    //
    switch (shell_mode) {
        case SHTP_CLIE:
        case SHTP_OSEV:
            chk_valu = 0x00;
            break;
        case SHTP_LEVE:
            for (comd_valu = leve_ctype_tab; -1 != comd_valu[0x00]; ++comd_valu) {
                if (comd_valu[0x00] == oscmd->comd_valu) {
                    chk_valu = 0x00;
                    if (comd_leve == oscmd->comd_valu) chk_valu = prchk_leve(oscmd, run_level);
                    break;
                }
            }
            break;
        default:
            chk_valu = -1;
            break;
    }
    printf("[debug]prepa_check chk_valu:%d\n", chk_valu);
    return chk_valu;
}