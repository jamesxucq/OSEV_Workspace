
/* 
 * File:   conv_stri.h
 * Author: James Xu
 *
 * Created on 2017.6.27, PM 3:30
 */

#ifndef CONV_STRI_H
#define CONV_STRI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum {
        rtyp_void,
        rtyp_char,
        rtyp_ucha,
        rtyp_shor,
        rtyp_usho,
        rtyp_int,
        rtyp_uint,
        rtyp_long,
        rtyp_ulon,
        rtyp_llon,
        rtyp_ullo,
        rtyp_chap
    } caller_type;

    //
    int chk_meth_type(char *clas_decl, char *metnm);

    //
    char *pass_space(char *meth_txt);
    int parse_chead(char *const_type, char *meth_txt);
    int parse_ihead(char *meth_iinte, char *meth_txt);
    char *parse_space_ex(char *metnm, char *space);
    char *argu_node(char *conte, char *data);
    char *parse_data(char *data, char *conte);
    char *pass_clasn(char *clas_decl);
    char *data_node(char *conte, char *data);

    //
    int parse_class_actu(char *actu_head, char *clas_decl, char *meth_name);
    int parse_class_meth(char actu_data[PARAM_NUMB][PARAM_LENGTH], char *actu_head);

    //
    char *parse_void(char *param);
    char *parse_ointe_ex(char *ointe_data, char *param);
    char *parse_space(char *clasn, char *metnm, char *space);

    //
    char *parse_head(char *ointe_type, char *meth_ointe, char *meth_iinte, char *meth_txt);
    int parse_retype(char *retyp_valu, char *ointe_type);
    void parse_body(char *meth_body, char *meth_txt);

    //
    int parse_class_data(char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *clas_decl);
    int parse_class_data_ex(char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *clas_decl);

    //
    char *parse_tok(char *node_str, int *nod_type, char *body_txt);
    int parse_meth_head(char form_data[PARAM_NUMB][PARAM_LENGTH], char *meth_txt);

    //
    int check_decla(char *conte);
    char *node_line(char *node_cont, char *conte);
    int parse_decla(char *type, char vari[PARAM_NUMB][PARAM_LENGTH], char *valu, char *decla);

#ifdef __cplusplus
}
#endif

#endif /* CONV_STRI_H */

