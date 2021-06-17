
/* 
 * File:   findo.h
 * Author: James Xu
 *
 * Created on 2017.4.11, AM10:01
 */

#ifndef FINDO_H
#define FINDO_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

//
int find_oenti_obje(prod_data *sresp, rive_conne *rvcon, contain *conta, hand_data *handa, char **paras);
int find_oenti_cont(prod_data *sresp, rive_conne *rvcon, contain *dcont, contain *conta, hand_data *handa, char **paras);
int find_oenti_clas(prod_data *sresp, rive_conne *rvcon, contain *conta, hand_data *handa, char **paras);
int find_oenti_decl(prod_data *sresp, rive_conne *rvcon, contain *conta, hand_data *handa, char **paras);


#ifdef __cplusplus
}
#endif

#endif /* FINDO_H */

