
/* 
 * File:   echo_clang.h
 * Author: James Xu
 *
 * Created on 2017.3.15, AM10:18
 */

#ifndef ECHO_CLANG_H
#define ECHO_CLANG_H

#include "commo_header.h"
#include "clas_list.h"
#include "conv_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    typedef struct {
        char clasn[CLASS_LENGTH];
        char metnm[METH_LENGTH];
        char ointe_type[TYPE_LENGTH];
        char retyp_valu[TYPE_LENGTH];
        char meth_ointe[METH_LENGTH];
        char param_type[PARA_TYPE_LEN];
        char meth_iinte[METH_LENGTH];
        char meth_body[LARGE_TEXT_SIZE];
    } parse_metho;

    //
    void print_metho(parse_metho *metho);

    //
    char *echo_dhead_txt(char *clang_str);
    char *build_class_txt(char *clang_str, char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH]);
    char *build_osize_txt(char *clang_str, char *clasn);
    char *build_sobje_txt(char *clang_str, char *clasn);
    int build_ointe_simple(char *meth_ointe, char *clasn);
    int build_ointe_comple(char *meth_ointe, char *clasn, char ointe_data[CDATNO_NUMB][PARAM_LENGTH]);

    //
    char *build_metho_txt(char *clang_str, parse_metho *metho);
    char *build_const_txt(char *clang_str, parse_metho *metho);
    char *build_spara_txt(char *clang_str, char ointe_data[PARAM_NUMB][PARAM_LENGTH]);
    char *build_retyp_txt(char *clang_str, parse_metho *metho);
    char *build_parse_txt(char *clang_str, parse_metho *metho, char ointe_para[PARAM_NUMB][PARAM_LENGTH]);
    char *build_handle_txt(char *handle_txt, parse_metho *metho);
    char *build_mepaty_txt(char *mepaty_txt, parse_metho *metho);
    char *echo_ohead_txt(char *clang_str);
    char *build_bound_txt(char *clang_str, char *clasn, colum colu_data[CDATNO_NUMB]);
    char *build_solve_txt(char *clang_str, char *clasn, colum colu_data[CDATNO_NUMB]);

    //
    void echo_class_objid(prod_data *sresp, char *clas_obid);
    void echo_class_attri(prod_data *sresp, char *clas_attr);
    void echo_class_inheri(prod_data *sresp, char *clas_inhe);
    void echo_class_meta(prod_data *sresp, clas_meta *clasm);
    void list_meth_conte(prod_data *sresp, char *metnm, clas_meta *clasm);
    char *echo_imeth_conte(char *advan_txt, char *metnm, char *parat, clas_meta *clasm);

#ifdef __cplusplus
}
#endif

#endif /* ECHO_CLANG_H */

