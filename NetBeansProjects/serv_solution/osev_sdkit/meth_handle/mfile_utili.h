
/* 
 * File:   file_utili.h
 * Author: James Xu
 *
 * Created on 2017.1.9, PM 5:12
 */

#ifndef MFILE_UTILI_H
#define MFILE_UTILI_H

#include "conoda.h"

#ifdef __cplusplus
extern "C" {
#endif

    int save_clang_file(char *clan_path, char *clang_txt);
    int compi_clang_file(char *obje_path, char *clan_path, BYTE *comp_mesg);

    //
    int open_data_hand(hand_data *handa, char *obje_path, char *clasn);
    int open_meth_hand(hand_data *hando, hand_data *handa, char *clasn, char *obje_path, char *handn);
    int dele_meth_hand(char *obje_path);

    //


#ifdef __cplusplus
}
#endif

#endif /* MFILE_UTILI_H */

