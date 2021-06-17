
#include "stri_utili.h"

#include "extend/list.h"
#include "extend/load.h"
#include "extend/save.h"
#include "extend/conve.h"
#include "extend/pretty.h"

#include "clie_obje.h"
#include "parse_command.h"
#include "extend.h"

//

int extend_command(osev_command *oscmd, shel_resu *resu) {
    int hand_valu = 0x00;
    char osev_osdb[OSEV_LENGTH];
    //
    switch (oscmd->comd_valu) {
        case come_inval:
            printf("extend invalid\n");
            break;
        case come_list:
            printf("extend list, resu_type:%d res_len:%llu style_str:%s\n",
                    resu->resu_type,
                    resu->res_len,
                    oscmd->paras[0x00]);
            hand_valu = hand_list(oscmd->paras, resu);
            break;
        case come_load:
            hand_valu = hand_load(oscmd->paras, resu);
            printf("extend load, resu_type:%d res_len:%llu file_name:%s\n",
                    resu->resu_type,
                    resu->res_len,
                    oscmd->paras[0x00]);
            break;
        case come_save:
            printf("extend save, resu_type:%d res_len:%llu file_name:%s\n",
                    resu->resu_type,
                    resu->res_len,
                    oscmd->paras[0x00]);
            hand_valu = hand_save(oscmd->paras, resu);
            break;
        case come_conv:
            printf("extend convert, resu_type:%d res_len:%llu file_name:%s comp_type:%s\n",
                    resu->resu_type,
                    resu->res_len,
                    oscmd->paras[0x00],
                    oscmd->paras[0x01]);
            if (get_osev_osdb(osev_osdb))
                hand_valu = hand_conver(oscmd->paras, resu, osev_osdb);
            break;
        case come_pret:
            printf("extend pretty, resu_type:%d res_len:%llu style_str:%s\n",
                    resu->resu_type,
                    resu->res_len,
                    oscmd->paras[0x00]);
            hand_valu = hand_pretty(oscmd->paras, resu);
            break;
        default:
            break;
    }
    //
    return hand_valu;
}