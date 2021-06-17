
/* 
 * File:   quer_bzl.h
 * Author: James Xu
 *
 * Created on 2017.1.4, AM 9:22
 */

#ifndef QUER_BZL_H
#define QUER_BZL_H

#include "conattr.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //int querbzl_create(char *data_directory);
    //int querbzl_destroy();

    //

#define creat_conta_bzl(osdb, cont_name, stora_type) creat_conta_obje(osdb, cont_name, stora_type)
#define qload_conta_bzl(clist) qload_conta_obje(clist)


    // conta metadata
#define creat_cattr_bzl(osdb) creat_cattr(osdb)
#define sear_conta_bzl(resu, osdb, cont_name, clas_type) sear_cattr(resu, osdb, cont_name, clas_type)

    //
    int quer_echo_bzl(prod_data *sresp, contain *conta);
    int quer_creat_bzl(rive_conne *rvcon, char *osdb, char **paras);
    int quer_drop_bzl(rive_conne *rvcon, rive_ha *stora_ha, char *osdb, char **paras);

    //

    typedef struct {
        cont_data *conda;
        hand_data *handa;
        hand_data *hando;
        rive_conne *rvcon;
        char **paras;
    } query_data;

#define CREATE_QREQU(COVAL, PARAS) \
        query_data qrequ; \
        qrequ.conda = &((conoda *) COVAL)->conda; \
        qrequ.handa = &((conoda *) COVAL)->handa; \
        qrequ.hando = &((conoda *) COVAL)->hando; \
        qrequ.rvcon = ((conoda *) COVAL)->rvcon; \
        qrequ.paras = PARAS;

    int quer_find_bzl(prod_data *sresp, query_data *qrequ);
    int quer_facto_bzl(prod_data *sresp, query_data *qrequ);
    int quer_invok_bzl(prod_data *sresp, contain *conta, hand_data *hando, rive_conne *rvcon, char **paras);

    //

#ifdef __cplusplus
}
#endif

#endif /* QUER_BZL_H */

