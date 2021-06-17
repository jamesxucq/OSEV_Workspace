
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shel_macro.h"
#include "parse_command.h"
#include "prepa_prompt.h"
#include "check_command.h"
#include "clie_obje.h"

//

struct singl_node {
    const char *stri;
    int value;
    int attri;
};


#define SINGLE_VALUE(VALUE, ATTRI, TABLE, STRI) { \
    struct singl_node *item; \
    for(item = (struct singl_node *)TABLE; item->stri; ++item) \
        if(!strcasecmp(STRI, item->stri)) break; \
    VALUE = item->value; \
    ATTRI = item->attri; \
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
        if(!strcasecmp(STR1, item->str1) && !strcasecmp(STR2, item->str2)) break; \
    VALUE = item->value; \
    ATTRI = item->attri; \
}

// "odb:createUser",
// "odb:runLevel",

static struct singl_node lev1_meth_tab[] = {
    {"list", invo_list, ATTRI_MAJOR},
    {"create", invo_creat, ATTRI_MAJOR},
    {"drop", invo_drop, ATTRI_MAJOR},
    {"replace", invo_repla, ATTRI_MAJOR},
    {"integri", invo_integri, ATTRI_MAJOR},
    {"reload", invo_reload, ATTRI_MAJOR},
    {NULL, invo_inval, ATTRI_INVALID}
};

static struct coupl_node lev2p_meth_tab[] = {
    {"odb", "list", coll_list, ATTRI_MAJOR},
    {"odb", "create", coll_creat, ATTRI_MAJOR},
    {"odb", "drop", coll_drop, ATTRI_MAJOR},
    {"odb", "replace", coll_repla, ATTRI_MAJOR},
    {"odb", "integri", coll_integri, ATTRI_MAJOR},
    {"odb", "reload", coll_reload, ATTRI_MAJOR},
    {NULL, NULL, coll_inval, ATTRI_INVALID}
};

//

static struct singl_node lev3_meth_tab[] = {
    {"echo", cons_echo, ATTRI_MAJOR},
    {"create", cons_creat, ATTRI_MAJOR},
    {"drop", cons_drop, ATTRI_MAJOR},
    {"update", cons_updat, ATTRI_MAJOR},
    {"insert", cons_inser, ATTRI_MAJOR},
    {"find", cons_find, ATTRI_MAJOR},
    {"invoke", cons_invok, ATTRI_MAJOR},
    {NULL, cons_inval, ATTRI_INVALID}
};

//

static struct singl_node lev4p_meth_tab[] = {
    {"echo", quer_echo, ATTRI_MAJOR},
    {"create", quer_creat, ATTRI_MAJOR},
    {"drop", quer_drop, ATTRI_MAJOR},
    {"find", quer_find, ATTRI_MAJOR},
    {"update", quer_updat, ATTRI_MAJOR},
    {"insert", quer_inser, ATTRI_MAJOR},
    {"invoke", quer_invok, ATTRI_MAJOR},
    {"factory", quer_facto, ATTRI_MAJOR},
    {NULL, quer_inval, ATTRI_INVALID}
};

// 0:success 0x01:exception

static int check_leve(osev_command *oscmd, uint32 run_level) {
    int leve_valu = 0x00;
    printf("check_leve comd_conte:%s:%s run_level:%08X\n", oscmd->obje_iden, oscmd->comd_meth, run_level);
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LEVE_ONE:
            SINGLE_VALUE(oscmd->meth_valu, oscmd->comd_attrib, lev1_meth_tab, oscmd->comd_meth)
            break;
        case LEVE_TWOP:
            COUPLE_VALUE(oscmd->meth_valu, oscmd->comd_attrib, lev2p_meth_tab, oscmd->obje_iden, oscmd->comd_meth)
            break;
        case LEVE_THRE:
            if (LEVEL_EXTEND_SPACE & run_level) {
                printf("obje_iden:%s:%s\n", _leve_defa_obje_.obje_iden, oscmd->obje_iden);
                if (strcmp(_leve_defa_obje_.obje_iden, oscmd->obje_iden)) leve_valu = -1;
            }
            SINGLE_VALUE(oscmd->meth_valu, oscmd->comd_attrib, lev3_meth_tab, oscmd->comd_meth)
            break;
        case LEVE_FOUP:
            SINGLE_VALUE(oscmd->meth_valu, oscmd->comd_attrib, lev4p_meth_tab, oscmd->comd_meth)
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
/*
    "osev:createUser",
    "osev:runLevel",
    "osev:createRole",
    "osev:grantRolesToUser",
    "osev:updateRole",
    enum statu_comd {
        stat_inval,
        stat_echo,
        stat_open, // start create
        stat_close, // shutdown
        stat_status,
        stat_user,
        stat_role,
        stat_privile,
    };
 */

static struct singl_node osev_mstat_tab[] = {
    {"echo", stat_echo, ATTRI_MAJOR},
    {"open", stat_open, ATTRI_MAJOR},
    {"close", stat_close, ATTRI_MAJOR},
    {"status", stat_status, ATTRI_MAJOR},
    {"stati", stat_stati, ATTRI_MAJOR},
    {NULL, stat_inval, ATTRI_INVALID}
};

//

static struct singl_node osev_mpriv_tab[] = {
    {"list", priv_list, ATTRI_MAJOR},
    {"role", priv_role, ATTRI_MAJOR},
    {"user", priv_user, ATTRI_MAJOR},
    {NULL, priv_inval, ATTRI_INVALID}
};

// 0:success -1:error

static int check_osev(osev_command *oscmd) {
    int osev_valu = 0x00;
    //
    if (comd_stat == oscmd->comd_valu)
        SINGLE_VALUE(oscmd->meth_valu, oscmd->comd_attrib, osev_mstat_tab, oscmd->comd_meth)
    else if (comd_priv == oscmd->comd_valu) {
        if (strcmp(OSEV_PRIVILE_VALUE, oscmd->obje_iden) && strcmp(OSDB_PRIVILE_VALUE, oscmd->obje_iden))
            osev_valu = -1;
        SINGLE_VALUE(oscmd->meth_valu, oscmd->comd_attrib, osev_mpriv_tab, oscmd->comd_meth)
    }
    //      
    return osev_valu;
}

//
static char* clie_comd_tab[] = {
    "clie:help",
    "clie:version",
    "clie:about",
    NULL
};

static int check_clie(osev_command *oscmd) {
    int chk_valu = -1;
    char **comd_stri;
    //
    char comd_conte[PARAM_LENGTH];
    sprintf(comd_conte, "%s:%s", oscmd->obje_iden, oscmd->comd_meth);
    for (comd_stri = clie_comd_tab; comd_stri[0x00]; ++comd_stri) {
        if (!strcasecmp(comd_conte, comd_stri[0x00])) {
            oscmd->meth_valu = -1;
            oscmd->comd_attrib = ATTRI_MAJOR;
            chk_valu = 0x00;
            break;
        }
    }
    //
    return chk_valu;
}

//
static command clie_ctype_tab[] = {
    comd_conne,
    comd_exit,
    comd_bye,
    comd_clie,
    -1
};

static command osev_ctype_tab[] = {
    comd_exit,
    comd_use,
    comd_stat,
    comd_priv,
    comd_quit,
    -1
};

static command leve_ctype_tab[] = {
    comd_quit,
    comd_level,
    comd_leve,
    -1
};

// 0:success -1:error

int check_method(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    int chk_valu = -1;
    command *comd_valu;
    //
    switch (shell_mode) {
        case SHTP_CLIE:
            for (comd_valu = clie_ctype_tab; -1 != comd_valu[0x00]; ++comd_valu) {
                if (comd_valu[0x00] == oscmd->comd_valu) {
                    chk_valu = 0x00;
                    if (comd_clie == oscmd->comd_valu) chk_valu = check_clie(oscmd);
                    break;
                }
            }
            break;
        case SHTP_OSEV:
            for (comd_valu = osev_ctype_tab; -1 != comd_valu[0x00]; ++comd_valu) {
                if (comd_valu[0x00] == oscmd->comd_valu) { // comd_stat, comd_priv,
                    chk_valu = 0x00;
                    if ((comd_stat == oscmd->comd_valu) || (comd_priv == oscmd->comd_valu)) chk_valu = check_osev(oscmd);
                    break;
                }
            }
            break;
        case SHTP_LEVE:
            for (comd_valu = leve_ctype_tab; -1 != comd_valu[0x00]; ++comd_valu) {
                if (comd_valu[0x00] == oscmd->comd_valu) {
                    chk_valu = 0x00;
                    if (comd_leve == oscmd->comd_valu) chk_valu = check_leve(oscmd, run_level);
                    break;
                }
            }
            break;
        default:
            chk_valu = -1;
            break;
    }
    printf("[debug]check_method chk_valu:%d\n", chk_valu);
    return chk_valu;
}

//

static extend_comd lev1_exten_tab[] = {
    come_load,
    come_save,
    come_conv,
    -1
};

static extend_comd lev2p_exten_tab[] = {
    come_list,
    come_load,
    come_save,
    come_conv,
    -1
};

static extend_comd lev3_exten_tab[] = {
    come_load,
    come_save,
    come_pret,
    -1
};

static extend_comd lev4p_exten_tab[] = {
    come_load,
    come_save,
    come_pret,
    -1
};

// 0:success 0x01:exception

static int check_lext(osev_command *oscmd, uint32 run_level) {
    int chk_valu = -1;
    printf("check_lext run_level:%08X\n", run_level);
    printf("check_lext comd_conte:%s:%s\n", oscmd->obje_iden, oscmd->comd_meth);
    extend_comd *cmde_valu;
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LEVE_ONE:
            for (cmde_valu = lev1_exten_tab; -1 != *cmde_valu; ++cmde_valu) {
                if (*cmde_valu == oscmd->comd_valu) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
        case LEVE_TWOP:
            for (cmde_valu = lev2p_exten_tab; -1 != *cmde_valu; ++cmde_valu) {
                if (*cmde_valu == oscmd->comd_valu) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
        case LEVE_THRE:
            for (cmde_valu = lev3_exten_tab; -1 != *cmde_valu; ++cmde_valu) {
                if (*cmde_valu == oscmd->comd_valu) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
        case LEVE_FOUP:
            for (cmde_valu = lev4p_exten_tab; -1 != *cmde_valu; ++cmde_valu) {
                if (*cmde_valu == oscmd->comd_valu) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
    }
    //
    return chk_valu;
}

static extend_comd exten_ctype_tab[] = {
    come_list,
    come_load,
    come_save,
    come_conv,
    come_pret,
    -1
};

// 0:success -1:error

int check_extend(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    int chk_valu = -1;
    //
    extend_comd *cmde_valu;
    if (SHTP_LEVE == shell_mode) {
        for (cmde_valu = exten_ctype_tab; -1 != *cmde_valu; ++cmde_valu) {
            if (*cmde_valu == oscmd->comd_valu) {
                chk_valu = check_lext(oscmd, run_level);
                break;
            }
        }
    }
    // printf("[debug]check_method chk_valu:%d\n", chk_valu);
    return chk_valu;
}
