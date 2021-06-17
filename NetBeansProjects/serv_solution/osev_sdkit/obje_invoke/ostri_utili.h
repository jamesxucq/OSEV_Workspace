
/* 
 * File:   ostri_utili.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 3:39
 */

#ifndef OSTRI_UTILI_H
#define OSTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct varia_type {
        char name[PARAM_LENGTH];
        char type[PARAM_LENGTH];
    };

    //
    char *data_node(char *conte, char *data);
    char *argu_node(char *conte, char *data);
    char *parse_data(char *data, char *conte);
    char *parse_clasn(char *clasn, char *clas_decl);
    char *pass_clasn(char *clas_decl);
    char *parse_space(char *clasn, char *metnm, char *space);
    char *parse_space_ex(char *metnm, char *space);
    char *pass_space(char *meth_txt);
    char *parse_head(char *ointe_type, char *meth_ointe, char *meth_iinte, char *meth_txt);
    int parse_retype(char *retyp_valu, char *ointe_type);
    int parse_ohead(char *meth_ointe, char *decla);
    int parse_ihead(char *meth_iinte, char *meth_txt);
    int parse_chead(char *const_type, char *meth_txt);

    //
    void parse_body(char *meth_body, char *meth_txt);
    int parse_class_actu(char *actu_head, char *clas_decl, char *meth_name);
    char *parse_tok(char *node_str, int *nod_type, char *body_txt);
    int parse_meth_head(char form_data[PARAM_NUMB][PARAM_LENGTH], char *meth_txt);
    int parse_class_meth(char actu_data[PARAM_NUMB][PARAM_LENGTH], char *actu_head);
    //
    char *parse_void(char *param);
    char *parse_ointe(char *data_type, char *param);
    char *parse_ointe_ex(char *ointe_data, char *param);
    char *parse_ointe_decla(char *data_type, char *param);

    //
    int parse_class_data(char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *clas_decl);
    int parse_class_data_ex(char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *clas_decl);

    //
    // -1:error 0x00:normal 0x01:const
#define METHO_NORMA_TYPE    0x00
#define METHO_CONST_TYPE    0x01
    int chk_meth_type(char *clas_decl, char *metnm);

    //
    char *parse_iinte(char *data_type, struct varia_type vtype[CDATNO_NUMB], char *param);
    char *conte_node(char *clas, char *meth, char *paras, char *data);

    //
    char *node_line(char *node_cont, char *conte);
    int check_decla(char *conte);
    int parse_decla(char *type, char vari[PARAM_NUMB][PARAM_LENGTH], char *valu, char *decla);

    //
#define PARA_ARRA 0x0001
#define PARA_DEFA 0x0002
#define PARA_NUMB 0x0100
#define PARA_BYTE 0x0200
#define PARA_CHAR 0x0400

#define PARA_COLU_SIZE 0x04

    typedef struct {
        char name[PARAM_LENGTH];
        char type[PARAM_LENGTH];
        char arra[PARAM_LENGTH];
        char defa[PARAM_LENGTH];
        unsigned int attri;
    } para_node;

    unsigned int split_para_colu(char para_arra[PARA_COLU_SIZE][PARAM_LENGTH], char *data);
    int parse_para_colu(para_node *pano, char para_arra[PARA_COLU_SIZE][PARAM_LENGTH]);

#ifdef __cplusplus
}
#endif

#endif /* OSTRI_UTILI_H */

