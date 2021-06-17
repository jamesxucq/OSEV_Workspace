
/* 
 * File:   save.h
 * Author: James Xu
 *
 * Created on 2017.4.20, PM3:53
 */

#ifndef SAVE_H
#define SAVE_H

#include "../clie_struct.h"
#include "../stri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int hand_save(char **parae, shel_resu *resu);

#ifdef __cplusplus
}
#endif

#endif /* SAVE_H */

