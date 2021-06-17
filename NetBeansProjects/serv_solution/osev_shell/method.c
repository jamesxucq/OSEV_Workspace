
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "clie_obje.h"
#include "prepa_prompt.h"
#include "method.h"
#include "defau_utili.h"
#include "conv_utili.h"

//

static int conve_osev_stat(char *obje_iden, unsigned int mvalu, char **paras, char *sline) {
    int hand_valu = 0x00;
    //
    switch (mvalu) {
        case stat_echo:
            hand_valu = defva_stat_echo(paras, obje_iden, sline);
            if (hand_valu) return -1;
            hand_valu = sconv_echo_styl(paras, obje_iden);
            break;
        case stat_open:
            hand_valu = defva_stat_open(paras, obje_iden, sline);
            if (hand_valu) return -1;
            hand_valu = sconv_open_styl(paras, obje_iden);
            break;
        case stat_close:
            quote_decode(paras[0x00]);
            hand_valu = sconv_close_styl(paras, obje_iden, sline);
            break;
        case stat_status:
            quote_decode(paras[0x00]);
            defva_stat_statu(paras, sline);
            hand_valu = sconv_statu_para(paras);
            if (hand_valu) return -1;
            hand_valu = sconv_statu_styl(paras, obje_iden);
            break;
        case stat_stati:
            quote_decode(paras[0x00]);
            defva_stat_stati(paras, sline);
            hand_valu = sconv_stati_para(paras);
            if (hand_valu) return -1;
            hand_valu = sconv_stati_styl(paras, obje_iden);
            break;
        default:
            break;
    }
    //
    return hand_valu;
}

//

static int conve_osev_priv(char *obje_iden, unsigned int mvalu, char **paras) {
    int hand_valu = 0x00;
    //
    switch (mvalu) {
        case priv_list:
            pconv_list_para(paras);
            break;
        case priv_role:
            quote_decode(paras[0x02]);
            quote_decode(paras[0x03]);
            defva_priv_role(paras, obje_iden);
            hand_valu = pconv_role_para(paras, obje_iden);
            break;
        case priv_user:
            quote_decode(paras[0x01]);
            quote_decode(paras[0x02]);
            pconv_user_para(paras);
            break;
        default:
            break;
    }
    //
    return hand_valu;
}

//

static int conve_osdb_leve(uint32 run_level, unsigned int mvalu, char **paras) {
    int hand_valu = 0x00;
    //
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LEVE_ONE:
            // hand_valu = 
            break;
        case LEVE_TWOP:
            // hand_valu = 
            break;
        case LEVE_THRE:
            // hand_valu = 
            break;
        case LEVE_FOUP:
            hand_valu = lconv_foup_para(mvalu, paras);
            break;
        default:
            break;
    }
    //
    return hand_valu;
}

//

int check_osev_use(char **paras) {
    char **toke = paras;
    int inde = 0x00;
    for (; toke[0x00]; toke++) inde++;
    if (0x01 != inde && 0x03 != inde) return -1;
    return 0x00;
}

//
// 0:ok -1:err

int prepare_method(osev_command *oscmd, uint32 shell_mode, uint32 run_level) {
    int hand_valu = 0x00;
    //
    switch (oscmd->comd_valu) {
        case comd_conne:
            break;
        case comd_use:
            hand_valu = check_osev_use(oscmd->paras);
            break;
        case comd_stat:
            hand_valu = conve_osev_stat(oscmd->obje_iden, oscmd->meth_valu, oscmd->paras, oscmd->paras_line);
            break;
        case comd_priv:
            hand_valu = conve_osev_priv(oscmd->obje_iden, oscmd->meth_valu, oscmd->paras);
            break;
        case comd_leve:
            if (SHTP_LEVE == shell_mode) hand_valu = conve_osdb_leve(run_level, oscmd->meth_valu, oscmd->paras);
            break;
        default:
            break;
    }
    // printf("[debug]handle_method hand_valu:%d\n", hand_valu);
    return hand_valu;
}

//
//

#define BUFF_SIZE                        0x2000

static void print_stre(int stre, uint64 clen) {
    char buffer[BUFF_SIZE];
    lseek64(stre, 0x00, SEEK_SET);
    uint64 elen = 0x00;
    int rlen;
    for (; clen > elen; elen += rlen) {
        rlen = read(stre, buffer, BUFF_SIZE);
        if (!rlen) break;
        buffer[rlen] = '\0';
        printf(buffer);
    }
}

static int clie_finis(shel_resu *resu, char *command) {
    if (!strcasecmp(command, "clie:help")) {
        printf(OCLIE_TABLE"help ...\n");
    } else if (!strcasecmp(command, "clie:version")) {
        printf(OCLIE_TABLE"version ...\n");
    } else if (!strcasecmp(command, "clie:about")) {
        printf(OCLIE_TABLE"about ...\n");
    } else {
        if (resu->resu_type) {
            printf("clie stre respon:\n");
            print_stre(resu->res_fde, resu->res_len);
            printf("\n");
        } else {
            resu->resu_data[resu->res_len] = '\0';
            printf("clie memo respon:\n%s\n", resu->resu_data);
        }
    }
    //
    return 0x00;
}

static int stat_finis(shel_resu *resu, unsigned int mvalu) {
    char oid_stri[OID_LINE_LEN];
    //
    switch (mvalu) {
        case stat_echo:
        case stat_open:
            printf("respon oid:|%s|\n", oidstr(oid_stri, (osv_oid_t *) resu->resu_data));
            break;
        default:
            if (resu->resu_type) {
                printf("stat stre respon:\n");
                print_stre(resu->res_fde, resu->res_len);
                printf("\n");
            } else {
                resu->resu_data[resu->res_len] = '\0';
                printf("stat memo respon:\n%s\n", resu->resu_data);
            }
            break;
    }
    //
    return 0x00;
}

static int priv_finis(shel_resu *resu, unsigned int mvalu) {
    if (resu->resu_type) {
        printf("priv stre respon:\n");
        print_stre(resu->res_fde, resu->res_len);
        printf("\n");
    } else {
        resu->resu_data[resu->res_len] = '\0';
        printf("priv memo respon:\n%s\n", resu->resu_data);
    }
    //
    return 0x00;
}

static int leve_finis(shel_resu *resu) {
    if (resu->resu_type) {
        printf("leve stre respon:\n");
        print_stre(resu->res_fde, resu->res_len);
        printf("\n");
    } else {
        resu->resu_data[resu->res_len] = '\0';
        printf("leve memo respon:\n%s\n", resu->resu_data);
    }
    //
    return 0x00;
}

// 0:ok -1:err

int finish_method(osev_command *oscmd, shel_resu *resu) {
    int hand_valu = 0x00;
    //
    switch (oscmd->comd_valu) {
        case comd_conne:
            break;
        case comd_clie:
            clie_finis(resu, oscmd->comd_meth);
            break;
        case comd_stat:
            stat_finis(resu, oscmd->meth_valu);
            break;
        case comd_priv:
            priv_finis(resu, oscmd->meth_valu);
            break;
        case comd_leve:
            leve_finis(resu);
            break;
        default:
            break;
    }
    // printf("finish_method hand_valu:%d\n", hand_valu);
    return hand_valu;
}

//

static int echo_finis(shel_resu *resu) {
    if (resu->resu_type) {
        printf("echo stre respon:\n");
        print_stre(resu->res_fde, resu->res_len);
        printf("\n");
    } else {
        resu->resu_data[resu->res_len] = '\0';
        printf("echo memo respon:\n%s\n", resu->resu_data);
    }
    //
    return 0x00;
}

static int load_finis(shel_resu *resu) {
    if (resu->resu_type) {
        printf("load stre respon:\n");
        print_stre(resu->res_fde, resu->res_len);
        printf("\n");
    } else {
        resu->resu_data[resu->res_len] = '\0';
        printf("load memo respon:\n%s\n", resu->resu_data);
    }
    //
    return 0x00;
}

static int save_finis(shel_resu *resu) {
    if (resu->resu_type) {
        printf("save stre respon:\n");
        print_stre(resu->res_fde, resu->res_len);
        printf("\n");
    } else {
        resu->resu_data[resu->res_len] = '\0';
        printf("save memo respon:\n%s\n", resu->resu_data);
    }
    //
    return 0x00;
}

static int conv_finis(shel_resu *resu) {
    if (resu->resu_type) {
        printf("conv stre respon:\n");
        print_stre(resu->res_fde, resu->res_len);
        printf("\n");
    } else {
        resu->resu_data[resu->res_len] = '\0';
        printf("conv memo respon:\n%s\n", resu->resu_data);
    }
    //
    return 0x00;
}

static int prtyp_finis(shel_resu *resu) {
    if (resu->resu_type) {
        printf("pretty stre respon:\n");
        print_stre(resu->res_fde, resu->res_len);
        printf("\n");
    } else {
        resu->resu_data[resu->res_len] = '\0';
        printf("pretty memo respon:\n%s\n", resu->resu_data);
    }
    //
    return 0x00;
}

//

int finish_extend(osev_command *oscmd, shel_resu *resu) {
    int hand_valu = 0x00;
    //
    switch (oscmd->comd_valu) {
        case come_list:
            echo_finis(resu);
            break;
        case come_load:
            load_finis(resu);
            break;
        case come_save:
            save_finis(resu);
            break;
        case come_conv:
            conv_finis(resu);
            break;
        case come_pret:
            prtyp_finis(resu);
            break;
        default:
            break;
    }
    // printf("finish_method hand_valu:%d\n", hand_valu);
    return hand_valu;
}