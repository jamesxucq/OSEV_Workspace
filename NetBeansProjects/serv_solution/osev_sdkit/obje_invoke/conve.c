#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "ostri_utili.h"
#include "conv_utili.h"
#include "echo_clang.h"
#include "conve.h"

//


#define INIT_PARSE_METHO(metho) \
    MKZERO(metho.clasn); MKZERO(metho.metnm); \
    MKZERO(metho.ointe_type); MKZERO(metho.meth_ointe); \
    MKZERO(metho.param_type); MKZERO(metho.meth_iinte); \
    MKZERO(metho.meth_body);

//
//

static char *conv_rive_clan(char *clang_str, char *clas_decl) {
    char clasn[CLASS_LENGTH];
    char clas_data[CDATNO_NUMB][PARAM_LENGTH];
    colum colu_data[CDATNO_NUMB];
    printf("conv clas_decl:%s\n", clas_decl);
    parse_class_data(clasn, clas_data, clas_decl);
    conv_clas_boso(colu_data, clas_data);
    //
    char *last_str = build_bound_txt(clang_str, clasn, colu_data);
    last_str = build_solve_txt(last_str, clasn, colu_data);
    return last_str;
}

static char *conv_class_clan(char *clang_str, char *clas_decl) {
    char clasn[CLASS_LENGTH];
    char clas_data[CDATNO_NUMB][PARAM_LENGTH];
    // printf("clas_decl:%s\n", clas_decl);
    parse_class_data(clasn, clas_data, clas_decl);
    if (conv_clas_decl(clas_data)) return NULL;
    // printf("clasn:%s\n", clasn);
    char *last_str = echo_dhead_txt(clang_str);
    last_str = build_class_txt(last_str, clasn, clas_data);
    // disable by james 20210508
    // last_str = build_sobje_txt(last_str, clasn);
    last_str = build_osize_txt(last_str, clasn);
    //
    return last_str;
}

char *conve_class_clang(char *clang_txt, char *clas_decl) {
    char *last_str = conv_class_clan(clang_txt, clas_decl);
    if (!last_str) return NULL;
    last_str = conv_rive_clan(last_str, clas_decl);
    if (!last_str) return NULL;
    printf("clang_txt:\n%s\n", clang_txt);
    return last_str;
}

//

static int parse_meth_data(parse_metho *metho, char *meth_txt) {
    char *last_str = parse_space(metho->clasn, metho->metnm, meth_txt);
    if (!last_str) return -1;
    // printf("clasn:%s\n", metho->clasn);
    // printf("meth_name:%s\n", metho->metnm);
    last_str = parse_head(metho->ointe_type, metho->meth_ointe, metho->meth_iinte, last_str);
    if (!last_str) return -1;
    parse_retype(metho->retyp_valu, metho->ointe_type);
    // printf("ointe_type:%s\n", metho->ointe_type);
    // printf("meth_ointe:%s\n", metho->meth_ointe);
    // printf("meth_iinte:%s\n", metho->meth_iinte);
    parse_body(metho->meth_body, last_str);
    // printf("meth_body:%s\n", metho->meth_body);
    return 0x00;
}

//

static int conve_param_norm(char *meth_body, char form_data[PARAM_NUMB][PARAM_LENGTH], char actu_data[PARAM_NUMB][PARAM_LENGTH]) {
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    // printf("conve_param_norm\n");
    char *last_str = body_str;
    char *last_body = meth_body;
    strcpy(body_str, meth_body);
    //
    int inde, nod_type;
    while (last_str && '\0' != last_str[0x00]) {
        // printf("-------- last_str:%s\n", last_str);
        last_str = parse_tok(node_str, &nod_type, last_str);
        // printf("nod_type:%d node_str:%s\n", nod_type, node_str);
        if (!nod_type) {
            for (inde = 0x00; '\0' != form_data[inde][0x00]; inde++) {
                if (!strcmp(node_str, form_data[inde])) {
                    // printf("node_str:%s\n", node_str);
                    char *last_nod = lscpy(node_str, "this->");
                    lscpy(last_nod, actu_data[inde]);
                    // printf("node_str:%s actu_data[inde]:%s\n", node_str, actu_data[inde]);
                    break;
                }
            }
        }
        last_body = lscpy(last_body, node_str);
    }
    //
    return 0x00;
}

static int conve_param_cons(char *meth_body, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char body_str[LARGE_TEXT_SIZE];
    char node_str[LINE_LENGTH];
    // printf("conve_param_cons\n");
    char *last_str = body_str;
    char *last_body = meth_body;
    strcpy(body_str, meth_body);
    //
    int inde, nod_type;
    while (last_str && '\0' != last_str[0x00]) {
        // printf("-------- last_str:%s\n", last_str);
        last_str = parse_tok(node_str, &nod_type, last_str);
        // printf("nod_type:%d node_str:%s\n", nod_type, node_str);
        if (!nod_type) {
            for (inde = 0x00; '\0' != clas_data[inde][0x00]; inde++) {
                if (!strcmp(node_str, clas_data[inde])) {
                    // printf("node_str:%s\n", node_str);
                    char *last_nod = lscpy(node_str, "this->");
                    lscpy(last_nod, clas_data[inde]);
                    // printf("node_str:%s clas_data[inde]:%s\n", node_str, clas_data[inde]);
                    break;
                }
            }
        }
        last_body = lscpy(last_body, node_str);
    }
    //
    return 0x00;
}

//

static int conve_body_decla(char *meth_body) {
    char body_cont[LARGE_TEXT_SIZE];
    char node_cont[LINE_LENGTH];
    char line_cont[LINE_LENGTH];
    // printf("conve_body_decla\n");
    strcpy(body_cont, meth_body);
    char *last_str = body_cont;
    char *last_body = meth_body;
    //
    MKZERO(line_cont);
    while ('\0' != last_str[0x00]) {
        last_str = node_line(node_cont, last_str);
        // printf("node_cont:%s\n", node_cont);
        if (check_decla(node_cont)) {
            conv_decla(line_cont, node_cont);
            // printf("line_cont:%s\n", line_cont);
            last_body = lscpy(last_body, line_cont);
            MKZERO(line_cont);
        } else last_body = lscpy(last_body, node_cont);
    }
    //
    return 0x00;
}

//

static int conve_meth_head(char *meth_ointe, char *clasn) {
    // printf("clasn:%s\n", clasn);
    build_ointe_simple(meth_ointe, clasn);
    // build_ointe_comple(meth_ointe, clasn, ointe_data);
    // printf("meth_ointe:%s\n", meth_ointe);
    return 0x00;
}

static int conve_body_norm(char *meth_body, char form_data[PARAM_NUMB][PARAM_LENGTH], char actu_data[PARAM_NUMB][PARAM_LENGTH]) {
    // printf("meth_body:%s\n", meth_body);
    conve_param_norm(meth_body, form_data, actu_data);
    conve_body_decla(meth_body);
    // printf("meth_body:%s\n", meth_body);
    return 0x00;
}

static int conve_body_cons(char *meth_body, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    // printf("meth_body:%s\n", meth_body);
    conve_param_cons(meth_body, clas_data);
    conve_body_decla(meth_body);
    // printf("meth_body:%s\n", meth_body);
    return 0x00;
}

//

static char *conv_metho_norma(char *clang_str, char *meth_txt, char *clas_decl) {
    parse_metho metho;
    INIT_PARSE_METHO(metho)
    if (parse_meth_data(&metho, meth_txt)) return NULL;
    char actu_head[METH_LENGTH];
    if (parse_class_actu(actu_head, clas_decl, metho.metnm)) return NULL;
    //
    if (conv_ointe_type(metho.param_type, metho.meth_ointe)) return NULL;
    char form_data[PARAM_NUMB][PARAM_LENGTH];
    char actu_data[PARAM_NUMB][PARAM_LENGTH];
    if (parse_meth_head(form_data, metho.meth_iinte)) return NULL;
    if (parse_class_meth(actu_data, actu_head)) return NULL;
    //
    if (conve_meth_head(metho.meth_ointe, metho.clasn)) return NULL;
    if (conve_body_norm(metho.meth_body, form_data, actu_data)) return NULL;
    char *last_str = build_metho_txt(clang_str, &metho);
    //
    return last_str;
}

static char *conv_metho_const(char *clang_str, char *meth_txt, char *clas_decl) {
    parse_metho metho;
    INIT_PARSE_METHO(metho)
    if (parse_meth_data(&metho, meth_txt)) return NULL;
    //
    if (conv_ointe_type(metho.param_type, metho.meth_ointe)) return NULL;
    char clas_data[CDATNO_NUMB][PARAM_LENGTH];
    if (parse_class_data_ex(clas_data, clas_decl)) return NULL;
    conv_clas_cons(clas_data);
    //
    if (conve_meth_head(metho.meth_ointe, metho.clasn)) return NULL;
    if (conve_body_cons(metho.meth_body, clas_data)) return NULL;
    char *last_str = build_const_txt(clang_str, &metho);
    //
    return last_str;
}

//

static char *conv_ointe_parse(char *clang_str, char *meth_txt) {
    parse_metho metho;
    INIT_PARSE_METHO(metho)
            //
    if (parse_meth_data(&metho, meth_txt)) return NULL;
    char ointe_data[PARAM_NUMB][PARAM_LENGTH];
    char ointe_para[PARAM_NUMB][PARAM_LENGTH];
    if (conv_ointe_data(ointe_data, ointe_para, metho.param_type, metho.meth_ointe)) return NULL;
    //
    char *last_str = echo_ohead_txt(clang_str);
    last_str = build_retyp_txt(last_str, &metho);
    last_str = build_spara_txt(last_str, ointe_data);
    last_str = build_parse_txt(last_str, &metho, ointe_para);
    return last_str;
}

//

static char *conv_class_ext(char *clang_str, char *clas_decl) {
    char clasn[CLASS_LENGTH];
    char clas_data[CDATNO_NUMB][PARAM_LENGTH];
    // printf("clas_decl:%s\n", clas_decl);
    parse_class_data(clasn, clas_data, clas_decl);
    conv_clas_decl(clas_data);
    // printf("clasn:%s\n", clasn);
    char *last_str = build_class_txt(clang_str, clasn, clas_data);
    return last_str;
}

//

char *conve_advan_clang(char *clang_txt, char *meth_defin, char *clas_decl, int meth_type) {
    // printf("cac clas_decl:%s\n", clas_decl);
    // printf("meth_defin:%s\n", meth_defin);
    if (valid_metho(meth_defin, clas_decl, meth_type)) return NULL;
    // printf("valid_metho passed!\n");
    //
    char *last_str = conv_ointe_parse(clang_txt, meth_defin);
    if (!last_str) return NULL;
    last_str = conv_class_ext(last_str, clas_decl);
    if (!last_str) return NULL;
    if (meth_type) {
        last_str = conv_metho_const(last_str, meth_defin, clas_decl);
        if (!last_str) return NULL;
    } else {
        last_str = conv_metho_norma(last_str, meth_defin, clas_decl);
        if (!last_str) return NULL;
    }
    printf("clang_txt:%s\n", clang_txt);
    //
    return last_str;
}

//

char *conve_handle_name(char *handn, char *mepan, char *meth_txt) {
    parse_metho metho;
    INIT_PARSE_METHO(metho)
            //
    if (parse_meth_data(&metho, meth_txt)) return NULL;
    if (conv_ointe_type(metho.param_type, metho.meth_ointe)) return NULL;
    build_handle_txt(handn, &metho);
    build_mepaty_txt(mepan, &metho);
    //
    return handn;
}
