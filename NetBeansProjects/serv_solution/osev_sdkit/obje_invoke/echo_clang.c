
#include "echo_clang.h"
#include "conv_utili.h"

//

void print_metho(parse_metho *metho) {
    printf("clasn:|%s|\n", metho->clasn);
    printf("metnm:|%s|\n", metho->metnm);
    printf("ointe_type:|%s|\n", metho->ointe_type);
    printf("meth_ointe:|%s|\n", metho->meth_ointe);
    printf("param_type:|%s|\n", metho->param_type);
    printf("meth_iinte:|%s|\n", metho->meth_iinte);
    printf("meth_body:|%s|\n", metho->meth_body);
}

//

char *build_class_txt(char *clang_str, char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char *last_str = lscpy(clang_str, "#pragma pack(1)\nstruct ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, " {\n");
    last_str = lscpy(last_str, "osv_oid_i obje_oid;\n");
    int inde;
    for (inde = 0x00; '\0' != clas_data[inde][0x00]; inde++) {
        last_str = lscpy(last_str, clas_data[inde]);
        last_str = lscpy(last_str, ";\n");
    }
    last_str = lscpy(last_str, "};\n#pragma pack() \n");
    //
    return last_str;
}

//

char *build_sobje_txt(char *clang_str, char *clasn) {
    char *last_str = lscpy(clang_str, "struct ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, " _");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "_sobj_; \n");
    //
    return last_str;
}

//

char *build_osize_txt(char *clang_str, char *clasn) {
    char *last_str = lscpy(clang_str, "int _");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, "_size_ = sizeof(struct ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, ");\n");
    //
    return last_str;
}

//

int build_ointe_simple(char *meth_ointe, char *clasn) {
    // printf("conve_ointe_simple\n");
    char *last_str = lscpy(meth_ointe, "(struct ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, " *this)");
    return 0x00;
}

int build_ointe_comple(char *meth_ointe, char *clasn, char ointe_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char *last_str = lscpy(meth_ointe, "(struct ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, " *this");
    // printf("conve_ointe_comple\n");
    int inde = 0x00;
    for (; '\0' != ointe_data[inde][0x00]; inde++) {
        last_str = lscpy(last_str, ", ");
        last_str = lscpy(last_str, ointe_data[inde]);
    }
    last_str = lccpy(last_str, ')');
    //
    return 0x00;
}

//

char *build_metho_txt(char *clang_str, parse_metho *metho) {
    // print_metho(metho); // for test
    char *last_str = lscpy(clang_str, metho->ointe_type);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, metho->clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->metnm);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->param_type);
    last_str = lscpy(last_str, metho->meth_ointe);
    last_str = lscpy(last_str, metho->meth_body);
    last_str = lccpy(last_str, '\n');
    //
    return last_str;
}

char *build_const_txt(char *clang_str, parse_metho *metho) {
    // print_metho(metho); // for test
    char *last_str = lscpy(clang_str, metho->ointe_type);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, metho->clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->metnm);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->param_type);
    last_str = lscpy(last_str, metho->meth_ointe);
    last_str = lscpy(last_str, metho->meth_body);
    last_str = lccpy(last_str, '\n');
    //
    return last_str;
}

//

char *build_retyp_txt(char *clang_str, parse_metho *metho) {
    char *last_str = lscpy(clang_str, "int _");
    last_str = lscpy(last_str, metho->clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->metnm);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->param_type);
    last_str = lscpy(last_str, "_retype_ = ");
    last_str = lscpy(last_str, metho->retyp_valu);
    last_str = lscpy(last_str, ";\n");
    //
    return last_str;
}

//

char *build_spara_txt(char *clang_str, char ointe_data[PARAM_NUMB][PARAM_LENGTH]) {
    char *last_str = lccpy(clang_str, '\n');
    int inde = 0x00;
    for (; '\0' != ointe_data[inde][0x00]; inde++) {
        last_str = lscpy(last_str, "static ");
        last_str = lscpy(last_str, ointe_data[inde]);
        last_str = lscpy(last_str, ";\n");
    }
    //
    return last_str;
}

//
#define PARA_TOK    "valu"

char *build_parse_txt(char *clang_str, parse_metho *metho, char ointe_para[PARAM_NUMB][PARAM_LENGTH]) {
    char *last_str = lscpy(clang_str, "void _parse_");
    last_str = lscpy(last_str, metho->clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->metnm);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->param_type);
    last_str = lccpy(last_str, '_');
    last_str = lsprif(last_str, "(char **paras) {\n");
    if ('\0' != ointe_para[0x00][0x00]) {
        last_str = lsprif(last_str, "char **%s = paras;\n", PARA_TOK);
        last_str = lscpy(last_str, ointe_para[0x00]);
        int inde = 0x00;
        for (inde = 0x01; '\0' != ointe_para[inde][0x00]; inde++) {
            last_str = lsprif(last_str, "++%s;\n", PARA_TOK);
            last_str = lscpy(last_str, ointe_para[inde]);
            last_str = lccpy(last_str, '\n');
        }
    }
    last_str = lscpy(last_str, "}\n");
    //
    return last_str;
}

//

char *build_handle_txt(char *handle_txt, parse_metho *metho) {
    char *last_str = lscpy(handle_txt, metho->clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->metnm);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->param_type);
    //
    return last_str;
}

char *build_mepaty_txt(char *mepaty_txt, parse_metho *metho) {
    char *last_str = lscpy(mepaty_txt, metho->metnm);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metho->param_type);
    //
    return last_str;
}

//

char *build_bound_txt(char *clang_str, char *clasn, colum colu_data[CDATNO_NUMB]) {
    char *last_str = lscpy(clang_str, "void _bind_");
    last_str = lscpy(last_str, clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, "(riv_curso_t *curso, struct ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, " *obje_data) {\n");
    last_str = lscpy(last_str, "curso->set_key(curso, obje_data->obje_oid.stoid);\n");
    last_str = lscpy(last_str, "curso->set_value(curso");
    //
    colum *cdata;
    for (cdata = colu_data; COLU_END != cdata->type; cdata++) {
        last_str = lscpy(last_str, ", obje_data->");
        last_str = lscpy(last_str, cdata->name);
    }
    //
    last_str = lscpy(last_str, ");\n");
    last_str = lscpy(last_str, "}\n");
    //
    return last_str;
}

//
#define BUILD_VNAME(VNAME, TOKE, INDE) lsprif(VNAME, "%s%d", TOKE, INDE);

char *build_solve_txt(char *clang_str, char *clasn, colum colu_data[CDATNO_NUMB]) {
    char *last_str = lscpy(clang_str, "void _solve_");
    last_str = lscpy(last_str, clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, "(struct ");
    last_str = lscpy(last_str, clasn);
    last_str = lscpy(last_str, " *obje_data, riv_curso_t *curso) {\n");
    //
    char vname[PARAM_LENGTH];
    colum *cdata;
    int inde, sexi = 0x00;
    for (cdata = colu_data, inde = 0x00; COLU_END != cdata->type; cdata++, inde++) {
        if ((COLU_CHAR == cdata->type) || (COLU_BYTE == cdata->type)) {
            if (sexi) {
                last_str = lscpy(last_str, ", ");
                BUILD_VNAME(vname, "*dat", inde)
                last_str = lscpy(last_str, vname);
            } else {
                last_str = lscpy(last_str, "char ");
                BUILD_VNAME(vname, "*dat", inde)
                last_str = lscpy(last_str, vname);
                sexi++;
            }
        }
    }
    if (sexi) last_str = lscpy(last_str, ";\n");
    //
    last_str = lscpy(last_str, "curso->get_key(curso, &(obje_data->obje_oid.stoid));\n");
    last_str = lscpy(last_str, "curso->get_value(curso");
    for (cdata = colu_data, inde = 0x00; COLU_END != cdata->type; cdata++, inde++) {
        switch (cdata->type) {
            case COLU_NUMB:
                last_str = lscpy(last_str, ", &obje_data->");
                last_str = lscpy(last_str, cdata->name);
                break;
            case COLU_CHAR:
            case COLU_BYTE:
                BUILD_VNAME(vname, ", &dat", inde)
                last_str = lscpy(last_str, vname);
                break;
            default:
                break;
        }
    }
    last_str = lscpy(last_str, ");\n");
    //
    for (cdata = colu_data, inde = 0x00; COLU_END != cdata->type; cdata++, inde++) {
        if (COLU_BYTE == cdata->type) {
            last_str = lscpy(last_str, "memcpy(");
            last_str = lscpy(last_str, "obje_data->");
            last_str = lscpy(last_str, cdata->name);
            BUILD_VNAME(vname, ", dat", inde)
            last_str = lscpy(last_str, vname);
            last_str = lsprif(last_str, ", %s);\n", cdata->size);
        } else if (COLU_CHAR == cdata->type) {
            last_str = lscpy(last_str, "strcpy(");
            last_str = lscpy(last_str, "obje_data->");
            last_str = lscpy(last_str, cdata->name);
            BUILD_VNAME(vname, ", dat", inde)
            last_str = lscpy(last_str, vname);
            last_str = lscpy(last_str, ");\n");
        }
    }
    //
    last_str = lscpy(last_str, "}\n");
    return last_str;
}

//
#define INCL_SYSTEM_HEAD "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdint.h>\n"
#define INCL_WTIGER_HEAD "#include \"wiredtiger.h\"\n#include \"wiredtiger_ext.h\"\n"
#define INCL_OSVOID_DEFI    "#pragma pack(1) \n \
typedef struct { \n \
unsigned int osev_unique; \n \
unsigned long long stoid; \n \
} osv_oid_i; \n \
#pragma pack() \n" 
#define INCL_WTIGER_DEFI "typedef WT_CURSOR riv_curso_t;\n"

//

char *echo_ohead_txt(char *clang_str) {
    char *last_str = lscpy(clang_str, INCL_SYSTEM_HEAD);
    last_str = lscpy(last_str, INCL_OSVOID_DEFI);
    return last_str;
}

//

char *echo_dhead_txt(char *clang_str) {
    char *last_str = lscpy(clang_str, INCL_SYSTEM_HEAD);
    last_str = lscpy(last_str, INCL_WTIGER_HEAD);
    last_str = lscpy(last_str, INCL_OSVOID_DEFI);
    last_str = lscpy(last_str, INCL_WTIGER_DEFI);
    return last_str;
}

//

void echo_class_objid(prod_data *sresp, char *clas_obid) {
    printf("(sresp->colen)[0x00]:%llu\n", (sresp->colen)[0x00]);
    char *last_str = lscpy((char *) sresp->sebuf + (sresp->colen)[0x00], clas_obid);
    lccpy(last_str, '\n');
    (sresp->colen)[0x00] += strlen((char *) sresp->sebuf);
}

void echo_class_attri(prod_data *sresp, char *clas_attr) {
    char *last_str = lscpy((char *) sresp->sebuf + (sresp->colen)[0x00], clas_attr);
    lccpy(last_str, '\n');
    (sresp->colen)[0x00] += strlen((char *) sresp->sebuf);
}

//

void echo_class_inheri(prod_data *sresp, char *clas_inhe) {
    char *last_str = lscpy((char *) sresp->sebuf + (sresp->colen)[0x00], clas_inhe);
    lccpy(last_str, '\n');
    (sresp->colen)[0x00] += strlen((char *) sresp->sebuf);
}

//

static char *meth_declare(char *decla, char *meth_data) {
    char *toke = strchr(meth_data, '<');
    if (!toke) return NULL;
    toke = strchr(toke + 0x01, '>');
    if (!toke) return NULL;
    char *last_str = lszcpy(decla, meth_data, toke - meth_data + 0x01);
    last_str = lscpy(last_str, ";\n");
    // printf("decla:%s\n", decla);
    return last_str;
}

void echo_class_meta(prod_data *sresp, clas_meta *clasm) {
    char *last_str = lscpy((char *) sresp->sebuf + (sresp->colen)[0x00], clasm->clas_decl);
    last_str = lccpy(last_str, '\n');
    //
    metho *mlistmp = clasm->meth_list;
    while (mlistmp) {
        last_str = meth_declare(last_str, mlistmp->meth_txt);
        mlistmp = mlistmp->next;
    }
    //
    (sresp->colen)[0x00] += strlen((char *) sresp->sebuf);
}

void list_meth_conte(prod_data *sresp, char *metnm, clas_meta *clasm) {
    char *last_str = (char *) sresp->sebuf;
    metho *menod = clasm->meth_list;
    for (; (menod = find_metho(menod, metnm)); menod = menod->next) {
        last_str = lscpy(last_str, menod->meth_txt);
        last_str = lccpy(last_str, '\n');
    }
    (sresp->colen)[0x00] = strlen((char *) sresp->sebuf);
}

char *echo_imeth_conte(char *advan_txt, char *metnm, char *parat, clas_meta *clasm) {
    metho *menod = clasm->meth_list;
    for (; (menod = find_metho(menod, metnm)); menod = menod->next) {
        if (!strcmp(parat, menod->param_type)) {
            strcpy(advan_txt, menod->meth_txt);
            return advan_txt;
        }
    }
    //
    return NULL;
}