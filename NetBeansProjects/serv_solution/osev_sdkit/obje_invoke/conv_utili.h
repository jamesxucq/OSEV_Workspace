
/* 
 * File:   conv_utili.h
 * Author: James Xu
 *
 * Created on 2017.3.13. AM9:54
 */

#ifndef CONV_UTILI_H
#define CONV_UTILI_H

#include "ostri_utili.h"
// #include "echo_clang.h"

#ifdef __cplusplus
extern "C" {
#endif


    //
    int valid_metho(char *meth_txt, char *clas_decl, int meth_type);
    char *conv_decla(char *data, char *conte);
    int conv_inne_type(char *dtype, char *conte);
    int conv_vari_type(char *varia, char *vtype, char *conte);
    int conv_clas_decl(char clas_data[CDATNO_NUMB][PARAM_LENGTH]);
    int conv_clas_cons(char clas_data[CDATNO_NUMB][PARAM_LENGTH]);

    //
#define COLU_END    -1
#define COLU_NUMB   0x00
#define COLU_CHAR   0x01
#define COLU_BYTE   0x02

    typedef struct {
        int8_t type; // 0x00:num 0x01:char 0x02:string -1:end
        char name[PARAM_LENGTH];
        char size[PARAM_LENGTH];
    } colum;

    int conv_clas_boso(colum *colu_data, char clas_data[CDATNO_NUMB][PARAM_LENGTH]);

    //
    int conv_ointe_type(char *parat, char *meth_txt);
    int conv_ointe_type_decl(char *parat, char *paras);
    int conv_ointe_data(char ointe_data[PARAM_NUMB][PARAM_LENGTH], char ointe_para[PARAM_NUMB][PARAM_LENGTH], char *parat, char *meth_ointe);
    char *conv_decla_vtype(char *vtype, char *decla);

    //
    char *conv_iinte_type(char *parat, struct varia_type vtype[CDATNO_NUMB], char *paras);
    int parse_class_meta(struct varia_type vtype[CDATNO_NUMB], char *clas_decl);

#ifdef __cplusplus
}
#endif

#endif /* CONV_UTILI_H */

