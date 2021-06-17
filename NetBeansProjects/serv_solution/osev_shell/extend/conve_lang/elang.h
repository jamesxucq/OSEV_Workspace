
/* 
 * File:   elang.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 3:25
 */

#ifndef ELANG_H
#define ELANG_H

#include "../../clie_struct.h"

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
        // char param_type[PARA_TYPE_LEN];
        char meth_iinte[METH_LENGTH];
        char meth_body[LARGE_TEXT_SIZE];
    } parse_metho;

    //
    int echo_class_conte(shel_resu *resu, char *clang_str, char *clasn, char *osdb);
    int echo_metho_conte(shel_resu *resu, char *clang_str, char *clasn, char *osdb);

    //
    char *build_class_stru(char *clang_str, char *clasn, char *osdb, char clas_data[CDATNO_NUMB][PARAM_LENGTH]);

    //
    int build_ointe_comple(char *meth_ointe, char ointe_data[CDATNO_NUMB][PARAM_LENGTH]);
    char *build_lcon_defin(char *clang_str, char *clasn);
    char *build_const_defin(char *clang_str, parse_metho *metho);
    char *build_metho_defin(char *clang_str, parse_metho *metho);
    char *build_const_decla(char *clang_str, parse_metho *metho);
    char *build_metho_decla(char *clang_str, parse_metho *metho);

    //
    // char *build_sobje_txt(char *clang_str, char *clasn);
    char *build_meta_osize(char *clang_str, char *clasn);
    char *build_meta_seria(char *clang_str, char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH]);
    char *build_meta_deseri(char *clang_str, char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH]);

    //
    char *build_eclas_head(char *clang_str, char *clasn);
    char *build_eclas_tail(char *clang_str);
    char *build_lcon_decla(char *clang_str, char *clasn);
    char *build_eclas_decla(char *clang_str, char clas_data[CDATNO_NUMB][PARAM_LENGTH]);
    char *build_meta_decla(char *clang_str, char *clasn);
#define build_metho_secti(clang_str) lscpy(clang_str, "public: \n");

#ifdef __cplusplus
}
#endif

#endif /* ELANG_H */

