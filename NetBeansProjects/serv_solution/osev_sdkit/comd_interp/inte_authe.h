
/* 
 * File:   inte_authe.h
 * Author: James Xu
 *
 * Created on 2017.5.23, AM9:59
 */

#ifndef INTE_AUTHE_H
#define INTE_AUTHE_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    enum authe_type {
        AUTH_OSEV,
        AUTH_OSDB,
    };

    //
    char *parse_authen(char *data_line, char **paras, char *requ_data);

    //
#define APARA_USER_NAME     0x00
#define APARA_REQU_VALID    0x01
#define APARA_REQU_SALT     0x02
#define APARA_PARAM_POS     0x03
#define APARA_OSEV_OSDB     0x03
#define APARA_ACTION_KEY    0x04
int hand_authen(prod_data *sresp, session *seion, seion_ctrl *sctrl, inte_value *inval);
int hand_noauth(prod_data *sresp, session *seion, seion_ctrl *sctrl, inte_value *inval);


#ifdef __cplusplus
}
#endif

#endif /* INTE_AUTHE_H */

