
/* 
 * File:   cons_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 2:53
 */

#ifndef CONS_BZL_H
#define CONS_BZL_H

#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //int invobzl_create(char *data_directory);
    //int invobzl_destroy();

    int cons_echo_bzl(prod_data *sresp, contain *conta);
    int cons_creat_bzl(prod_data *sresp, contain *conta, hand_data *hando, rive_conne *rvcon, char **paras);
    int cons_drop_bzl(prod_data *sresp, contain *conta, hand_data *hando, rive_conne *rvcon, char **paras);
    int cons_updat_bzl(prod_data *sresp, contain *conta, hand_data *handa, rive_conne *rvcon, char **paras);
    int cons_inser_bzl(prod_data *sresp, contain *conta, hand_data *handa, rive_conne *rvcon, char **paras);
    // obje:find();
    int cons_find_bzl(prod_data *sresp, contain *conta, hand_data *handa, rive_conne *rvcon, conoda *coval, char **paras);
    //
    int cons_each_bzl(prod_data *sresp, contain *conta, hand_data *hando, rive_conne *rvcon, char **paras);

    //


#ifdef __cplusplus
}
#endif

#endif /* CONS_BZL_H */

