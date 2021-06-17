
/* 
 * File:   load.h
 * Author: James Xu
 *
 * Created on 2017420, PM3:53
 */

#ifndef LOAD_H
#define LOAD_H

#include "../clie_struct.h"
#include "../stri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:OK -1:error
    int hand_load(char **parae, shel_resu *resu);


#ifdef __cplusplus
}
#endif

#endif /* LOAD_H */

