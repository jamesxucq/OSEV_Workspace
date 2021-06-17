#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "ostri_utili.h"
#include "conv_utili.h"
// #include "echo_clang.h"


/*
test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>
test:tst<(void)int> {return 0x00;}
test:tpp<(void)int, (x int)> {return 0x01;}
test:test<(void)int> {return x;}
 */

// -1:error 0x00:inn_out 0x01:inn 0x02:out

static int parse_inner_metho(char *metnm, char *inner_metho, char *meth_txt) {
    char *last_str = parse_space_ex(metnm, meth_txt);
    if (!last_str) return -1;
    int ioitype = parse_ihead(inner_metho, last_str);
    // printf("pim ioitype:%d inner_metho:%s\n", ioitype, inner_metho);
    return ioitype;
}

// -1:error 0x00:ok

static int parse_const_metho(char *const_type, char *meth_txt) {
    char *last_str = pass_space(meth_txt);
    if (!last_str) return -1;
    if (parse_chead(const_type, last_str)) return -1;
    // printf("pim ioitype:%d inner_metho:%s\n", ioitype, inner_metho);
    return 0x00;
}

//

int parse_class_meta(struct varia_type vtype[CDATNO_NUMB], char *clas_decl) {
    char *token, *toked;
    token = clas_decl;
    //
    char node_conte[CNODE_LENGTH];
    char paras[PARAM_LENGTH];
    int inde = 0x00;
    while ((token = data_node(node_conte, token))) {
        // printf("node_conte:%s\n", node_conte);
        for (toked = node_conte; toked; inde++) {
            toked = parse_data(paras, toked);
            conv_vari_type(vtype[inde].name, vtype[inde].type, paras);
            // printf("name:%s type:%s\n", vtype[inde].name, vtype[inde].type);
        }
    }
    MKZERO(vtype[inde].name);
    MKZERO(vtype[inde].type);
    //
    return 0x00;
}

static int parse_clas_data(struct varia_type vtype[CDATNO_NUMB], char *clas_decl) {
    char *token, *toked;
    token = pass_clasn(clas_decl);
    if (!token) return -1;
    //
    char node_conte[CNODE_LENGTH];
    char paras[PARAM_LENGTH];
    int inde = 0x00;
    while ((token = data_node(node_conte, token))) {
        // printf("node_conte:%s\n", node_conte);
        for (toked = node_conte; toked; inde++) {
            toked = parse_data(paras, toked);
            conv_vari_type(vtype[inde].name, vtype[inde].type, paras);
            // printf("name:%s type:%s\n", vtype[inde].name, vtype[inde].type);
        }
    }
    MKZERO(vtype[inde].name);
    MKZERO(vtype[inde].type);
    //
    return 0x00;
}

static int parse_inner_type(char inner_type[PARAM_NUMB][PARAM_LENGTH], char *inner_metho) {
    char node_conte[CNODE_LENGTH];
    argu_node(node_conte, inner_metho);
    // printf("pit node_conte:%s\n", node_conte);
    char paras[PARAM_LENGTH];
    char *token;
    int inde = 0x00;
    for (token = node_conte; token;) {
        token = parse_data(paras, token);
        // printf("pit paras:%s\n", paras);
        conv_inne_type(inner_type[inde++], paras);
        // printf("inner_type[inde++]:%s\n", inner_type[inde - 0x01]);
    }
    MKZERO(inner_type[inde]);
    //
    return 0x00;
}

//
#define TVALU_VARIAE(TVALU, TABLE, TEXT) { \
    int tind = 0x00; \
    for(; '\0' != TABLE[tind].name[0x00]; ++tind) \
        if(!strcmp(TEXT, TABLE[tind].name)) break; \
    strcpy(TVALU, TABLE[tind].type); \
}

static int parse_clas_metho(char meth_data[PARAM_NUMB][PARAM_LENGTH], struct varia_type vtype[CDATNO_NUMB], char *clas_decl, char *metnm) {
    char actu_head[METH_LENGTH];
    if (parse_class_actu(actu_head, clas_decl, metnm)) return -1;
    char actu_data[PARAM_NUMB][PARAM_LENGTH];
    if (parse_class_meth(actu_data, actu_head)) return -1;
    //
    int inde = 0x00;
    for (; '\0' != actu_data[inde][0x00]; inde++) {
        // printf("inde:%d \n", inde);
        TVALU_VARIAE(meth_data[inde], vtype, actu_data[inde])
                // printf("actu_data:|%s| meth_data:|%s|\n", actu_data[inde], meth_data[inde]);
    }
    MKZERO(meth_data[inde]);
    //
    return 0x00;
}

static int check_inner_type(char inner_metho[PARAM_NUMB][PARAM_LENGTH], char meth_data[PARAM_NUMB][PARAM_LENGTH]) {
    int inde = 0x00;
    for (; PARAM_NUMB > inde; inde++) {
        // printf("cit inde:%d ", inde);
        // printf("inner_metho:|%s| meth_data:|%s|\n", inner_metho[inde], meth_data[inde]);
        if ('\0' == inner_metho[inde][0x00] || '\0' == meth_data[inde][0x00]) {
            if ('\0' != inner_metho[inde][0x00] || '\0' != meth_data[inde][0x00]) return -1;
            break;
        }
        if (strcmp(inner_metho[inde], meth_data[inde])) return -1;
    }
    //
    printf("cit pass check!\n");
    return 0x00;
}

//
#define CONST_TYPE_TOK "int"
#define check_const_type(const_type) strcmp(CONST_TYPE_TOK, const_type)

// check inner invoke argument data type

int valid_metho(char *meth_txt, char *clas_decl, int meth_type) {
    char coin_metho[METH_LENGTH];
    char metnm[METH_LENGTH];
    // printf("meth_type:%d\n", meth_type);
    if (meth_type) {
        if (parse_const_metho(coin_metho, meth_txt)) return -1;
        // printf("11111, coin_metho:|%s|\n", coin_metho);
        if (check_const_type(coin_metho)) return -1;
        // printf("22222\n");
    } else { // -1:error 0x00:inn_out 0x01:inn 0x02:out
        int iotype = parse_inner_metho(metnm, coin_metho, meth_txt);
        if ((-1 == iotype) || (0x01 == iotype)) return -1;
        // printf("iotype:%d metnm:%s inner_metho:%s\n", iotype, metnm, coin_metho);
        // check the outside invoke
        char inner_type[PARAM_NUMB][PARAM_LENGTH];
        parse_inner_type(inner_type, coin_metho);
        // check inner invoke argum
        struct varia_type clas_data[CDATNO_NUMB];
        char meth_data[PARAM_NUMB][PARAM_LENGTH];
        parse_clas_data(clas_data, clas_decl);
        parse_clas_metho(meth_data, clas_data, clas_decl, metnm);
        if (check_inner_type(inner_type, meth_data)) return -1;
    }
    //
    return 0x00;
}

//

char *conv_decla(char *data, char *conte) {
    char type[PARAM_LENGTH], valu[PARAM_LENGTH];
    char vari[PARAM_NUMB][PARAM_LENGTH];
    int decla_type = parse_decla(type, vari, valu, conte);
    //
    char *last_str = data;
    int inde = 0x00;
    if (0x01 == decla_type) {
        last_str = lscpy(last_str, type);
        if ('\0' != vari[inde][0x00]) {
            last_str = lccpy(last_str, ' ');
            last_str = lscpy(last_str, vari[inde]);
            inde++;
        }
        for (; '\0' != vari[inde][0x00]; inde++) {
            last_str = lscpy(last_str, ", ");
            last_str = lscpy(last_str, vari[inde]);
        }
        last_str = lscpy(last_str, ";\n");
    } else if (0x02 == decla_type) {
        last_str = lscpy(last_str, type);
        if ('\0' != vari[inde][0x00]) {
            last_str = lccpy(last_str, ' ');
            last_str = lscpy(last_str, vari[inde]);
            last_str = lccpy(last_str, '[');
            last_str = lscpy(last_str, valu);
            last_str = lccpy(last_str, ']');
            inde++;
        }
        for (; '\0' != vari[inde][0x00]; inde++) {
            last_str = lscpy(last_str, ", ");
            last_str = lscpy(last_str, vari[inde]);
            last_str = lccpy(last_str, '[');
            last_str = lscpy(last_str, valu);
            last_str = lccpy(last_str, ']');
        }
        last_str = lscpy(last_str, ";\n");
    } else return NULL;
    //
    return data;
}

//

struct vstr_node {
    const char *text;
    char *value;
};

/*
 static const struct vcha_node types_value_tab[] = {
    // extend
    {"short", 'h'},
    {"int", 'i'},
    {"uint", 'I'},
    {"long", 'l'},
    {"long long", 'q'},
    // base
    {"int8", 'b'},
    {"uint8", 'B'},
    {"int16", 'h'},
    {"uint16", 'H'},
    {"int32", 'i'},
    {"uint32", 'I'},
    {"int64", 'q'},
    {"uint64", 'Q'},
    {"byte", 's'},
    {"char", 'S'},
    //
    {NULL, 'x'}
};
 */

static const struct vstr_node vtyp_valu_tab[] = {
    {"short", "short"},
    {"int", "int"},
    {"uint", "uint32_t"},
    {"long", "long"},
    {"long long", "long long"},
    //
    {"int8", "int8_t"},
    {"uint8", "uint8_t"},
    {"int16", "int16_t"},
    {"uint16", "uint16_t"},
    {"int32", "int32_t"},
    {"uint32", "uint32_t"},
    {"int64", "int64_t"},
    {"uint64", "uint64_t"},
    {"byte", "char"},
    {"char", "char"},
    {NULL, NULL}
};

#define TVALU_STREP(VALUE, TABLE, TEXT) { \
    struct vstr_node *item; \
    for(item = (struct vstr_node *)TABLE; item->text; ++item) \
        if(!strcasecmp(TEXT, item->text)) break; \
    VALUE = item->value; \
}

//

#define ASSI_BYTE_TOK "memcpy" 
#define ASSI_CHAR_TOK "strcpy"

//

void p_para_node(para_node *pano) {
    printf("name:|%s|", pano->name);
    printf(" type:|%s|", pano->type);
    if (PARA_ARRA & pano->attri)printf(" arra:|%s|", pano->arra);
    if (PARA_DEFA & pano->attri) printf(" defa:|%s|", pano->defa);
    printf(" attri:|%08x|\n", pano->attri);
}

static void build_para_text(char *para, char *pars, para_node *pano, char *tok) {
    char *value;
    TVALU_STREP(value, vtyp_valu_tab, pano->type)
            char *last_str = lscpy(para, value);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, pano->name);
    if (PARA_ARRA & pano->attri) lsprif(last_str, "[%s]", pano->arra);
    // printf("paras, [0]:|%d| [1]:|%d|\n", *((int *) (paras[0x00] + 0x01)), ((int *) (paras[0x01] + 0x01))[0x00]);
    if (PARA_DEFA & pano->attri) {
        if (PARA_NUMB & pano->attri) {
            last_str = lscpy(pars, pano->name);
            lsprif(last_str, " = ((%s*)(%s[0x00]+0x01))[0x00];", value, tok);
        } else if (PARA_BYTE & pano->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_BYTE_TOK, pano->name);
            lsprif(last_str, ", %s[0x00], %s);", tok, pano->arra);
        } else if (PARA_CHAR & pano->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_CHAR_TOK, pano->name);
            lsprif(last_str, ", %s[0x00]);", tok);
        }
    } else {
        if (PARA_NUMB & pano->attri) {
            last_str = lscpy(pars, pano->name);
            lsprif(last_str, " = ((%s*)(%s[0x00]+0x01))[0x00];", value, tok);
        } else if (PARA_BYTE & pano->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_BYTE_TOK, pano->name);
            lsprif(last_str, ", %s[0x00], %s);", tok, pano->arra);
        } else if (PARA_CHAR & pano->attri) {
            last_str = lsprif(pars, "%s(%s", ASSI_CHAR_TOK, pano->name);
            lsprif(last_str, ", %s[0x00]);", tok);
        }
    }
}

static int conv_oint_para(para_node *pano, char *conte) {
    char para_arra[PARA_COLU_SIZE][PARAM_LENGTH];
    pano->attri = split_para_colu(para_arra, conte);
    if (parse_para_colu(pano, para_arra)) return -1;
    p_para_node(pano);
    //
    return 0x00;
}

//
// test:tpp<(void)int, (x int)>

int conv_inne_type(char *dtype, char *conte) {
    // printf("bd conte:|%s| ", conte);
    char *toke = strchr(conte, ' ');
    if (toke) {
        for (; '\0' != toke[0x00] && ' ' == toke[0x00]; toke++);
        strcpy(dtype, toke);
    }
    // printf("dtype:|%s| \n", dtype);
    return 0x00;
}

// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>

int conv_vari_type(char *varia, char *vtype, char *conte) {
    // printf("bp conte:|%s| ", conte);
    char *toke = strchr(conte, '=');
    if (toke) {
        for (; conte != toke && ' ' == toke[-1]; toke--);
        strzcpy(varia, conte, toke - conte);
        toke++;
        for (; '\0' != toke[0x00] && ' ' == toke[0x00]; toke++);
        toke = strchr(toke, ' ');
        for (; '\0' != toke[0x00] && ' ' == toke[0x00]; toke++);
        strcpy(vtype, toke);
    } else {
        toke = strchr(conte, ' ');
        if (!toke) return -1;
        strzcpy(varia, conte, toke - conte);
        for (; '\0' != toke[0x00] && ' ' == toke[0x00]; toke++);
        strcpy(vtype, toke);
    }
    // printf("varia:|%s| vtype:|%s| \n", varia, vtype);
    return 0x00;
}

//
// ax=8 int => int ax
// ax char(16) => int ax[16]]

static char *split_type_valu(char *type, char *valu, char *conte) {
    char *toke = strlchr(conte);
    //
    if (')' == toke[0x00]) {
        for (; conte != toke && '(' != toke[0x00]; toke--);
        if (conte == toke) return NULL;
        for (toke--; conte != toke && ' ' == toke[0x00]; toke--);
    }
    for (; conte != toke && ' ' != toke[0x00]; toke--);
    if (conte == toke) return NULL;
    strzcpy(valu, conte, toke - conte);
    strcpy(type, ++toke);
    //
    return conte;
}

static void conte_type_valu(char *conte, char *type, char *valu, char *size) {
    char *last_str = lscpy(conte, type);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, valu);
    if (size[0x00]) {
        last_str = lccpy(last_str, '[');
        last_str = lscpy(last_str, size);
        lccpy(last_str, ']');
    }
}

static void parse_valu(char *valu) {
    char *toke = strchr(valu, '=');
    if (toke) toke[0x00] = '\0';
}

static void parse_type(char *size, char *type) {
    char *toksp = strchr(type, '(');
    if (toksp) {
        MKZERO(toksp);
        char *tokep = strchr(++toksp, ')');
        strzcpy(size, toksp, tokep - toksp);
    } else MKZERO(size);
}

// "CHAR" "STRI"

static int8_t check_type(char *data_type) {
    if (!strcasecmp(data_type, "char")) return COLU_CHAR;
    if (!strcasecmp(data_type, "byte")) return COLU_BYTE;
    return COLU_NUMB;
}

/*
 static const struct vcha_node types_value_tab[] = {
    // extend
    {"short", 'h'},
    {"int", 'i'},
    {"uint", 'I'},
    {"long", 'l'},
    {"long long", 'q'},
    // base
    {"int8", 'b'},
    {"uint8", 'B'},
    {"int16", 'h'},
    {"uint16", 'H'},
    {"int32", 'i'},
    {"uint32", 'I'},
    {"int64", 'q'},
    {"uint64", 'Q'},
    {"byte", 's'},
    {"char", 'S'},
    //
    {NULL, 'x'}
};
 */
//
static const struct vstr_node vtoke_valu_tab[] = {
    {"short", "short int"},
    {"int", "int"},
    {"uint", "unsigned int"},
    {"long", "long"},
    {"long long", "long long"},
//
    {"int8", "signed char"},
    {"uint8", "unsigned char"},
    {"int16", "short int"},
    {"uint16", "unsigned short int"},
    {"int32", "int"},
    {"uint32", "unsigned int"},
    {"int64", "long long int"},
    {"uint64", "unsigned long long int"},
    {"byte", "char"},
    {"char", "char"},
    {NULL, NULL}
};

#define TVALU_STRIE(VALUE, TABLE, TEXT) { \
    struct vstr_node *item; \
    for(item = (struct vstr_node *)TABLE; item->text; ++item) \
        if(!strcasecmp(TEXT, item->text)) { \
            strcpy(VALUE, item->value); \
            break; \
        } \
}

static int conv_data_styl_decl(char *data) {
    char type[PARAM_LENGTH], valu[PARAM_LENGTH];
    char size[PARAM_LENGTH];
    //
    if (!split_type_valu(type, valu, data)) return -1;
    parse_valu(valu);
    // printf("1 type:|%s| valu:|%s|\n", type, valu);
    parse_type(size, type);
    TVALU_STRIE(type, vtoke_valu_tab, type)
    // printf("2 type:|%s| valu:|%s| size:|%s|\n", type, valu, size);
    conte_type_valu(data, type, valu, size);
    //
    return 0x00;
}

//

int conv_clas_decl(char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    int inde = 0x00;
    for (; '\0' != clas_data[inde][0x00]; inde++) {
        // printf("1 clas_data[inde]:|%s|\n", clas_data[inde]);
        if (conv_data_styl_decl(clas_data[inde])) return -1;
        // printf("2 clas_data[inde]:|%s|\n", clas_data[inde]);
    }
    return 0x00;
}

// test<[xx=8 int, ax int], [cx int] auto, tst(xx), tpp(ax)>

static int conv_data_styl_cons(char *data) {
    // printf("bp conte:|%s| ", conte);
    char *toke = strchr(data, '=');
    if (toke) {
        for (; data != toke && ' ' == toke[-1]; toke--);
        MKZERO(toke);
    } else {
        toke = strchr(data, ' ');
        if (!toke) return -1;
        MKZERO(toke);
    }
    // printf("varia:|%s| vtype:|%s| \n", varia, vtype);
    return 0x00;
}

int conv_clas_cons(char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    int inde = 0x00;
    for (; '\0' != clas_data[inde][0x00]; inde++) {
        conv_data_styl_cons(clas_data[inde]);
        // printf("clas_data[inde]:%s\n", clas_data[inde]);
    }
    return 0x00;
}

//

void p_colum(colum *colu_data) {
    colum *cdata;
    printf("p_colum xxxxxxx\n");
    for (cdata = colu_data; COLU_END != cdata->type; cdata++) {
        printf("cdata->name:%s size:%s type:%d\n", cdata->name, cdata->size, cdata->type);
    }
}

int conv_clas_boso(colum *colu_data, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char data_type[PARAM_LENGTH];
    colum *cdata;
    int inde = 0x00;
    for (cdata = colu_data; '\0' != clas_data[inde][0x00]; cdata++, inde++) {
        if (!split_type_valu(data_type, cdata->name, clas_data[inde])) return -1;
        parse_valu(cdata->name);
        // printf("1 type:|%s| cdata->name:|%s|\n", data_type, cdata->name);
        parse_type(cdata->size, data_type);
        cdata->type = check_type(data_type);
        // printf("clas_data[inde]:%s\n", clas_data[inde]);
        // printf("cdata->name:%s size:%s type:%d\n", cdata->name, cdata->size, cdata->type);
    }
    cdata->type = COLU_END;
    // p_colum(colu_data);
    return 0x00;
}

//
#define VOID_TOK "vo"
#define echo_void(vtype) lscpy(vtype, VOID_TOK);

//

struct vcha_node {
    const char *text;
    char value;
};

#define TVALU_CHAC(VALUE, TABLE, TEXT) { \
    struct vcha_node *item; \
    for(item = (struct vcha_node *)TABLE; item->text; ++item) \
        if(!strcasecmp(TEXT, item->text)) break; \
    VALUE = lccpy(VALUE, item->value); \
}

static const struct vcha_node types_value_tab[] = {
    // extend
    {"short", 'h'},
    {"int", 'i'},
    {"uint", 'I'},
    {"long", 'l'},
    {"long long", 'q'},
    // base
    {"int8", 'b'},
    {"uint8", 'B'},
    {"int16", 'h'},
    {"uint16", 'H'},
    {"int32", 'i'},
    {"uint32", 'I'},
    {"int64", 'q'},
    {"uint64", 'Q'},
    {"byte", 's'},
    {"char", 'S'},
    //
    {NULL, 'x'}
};
//

static char *type_stri(char *parat, char *data_type) {
    char *last_str = parat;
    if (strchr(data_type, '&')) last_str = lccpy(last_str, 'R');
    TVALU_CHAC(last_str, types_value_tab, data_type)
    return last_str;
}

int conv_ointe_type(char *parat, char *meth_txt) {
    char data_type[PARA_TYPE_LEN] = {"\0"};
    char *toke = parat;
    char *last_str;
    // printf("meth_txt:%s\n", meth_txt);
    int inde = 0x00;
    if ((last_str = parse_void(meth_txt))) {
        last_str = parse_ointe(data_type, last_str);
        for (; last_str && (PARAM_NUMB >= inde); inde++) {
            // printf("last_str:%s\n", last_str);
            toke = type_stri(toke, data_type);
            // printf("data_type:|%s| parat:|%s|\n", data_type, parat);
            last_str = parse_ointe(data_type, last_str);
        }
    } else echo_void(parat);
    //
    return 0x00;
}

int conv_ointe_type_decl(char *parat, char *paras) {
    char data_type[PARA_TYPE_LEN] = {"\0"};
    char *toke = parat;
    char *last_str;
    // printf("meth_txt:%s\n", meth_txt);
    int inde = 0x00;
    if ((last_str = parse_void(paras))) {
        for (; last_str && ('\0' != last_str[0x00]) && (PARAM_NUMB >= inde); inde++) {
            // printf("last_str:%s\n", last_str);
            last_str = parse_ointe_decla(data_type, last_str);
            // printf("ointe_data[inde]:%s\n", ointe_data[inde]);
            toke = type_stri(toke, data_type);
            // printf("data_type:|%s| parat:|%s|\n", data_type, parat);
        }
    } else echo_void(parat);
    //
    return 0x00;
}

//
#define PARA_TOK    "valu"

int conv_ointe_data(char ointe_data[PARAM_NUMB][PARAM_LENGTH], char ointe_para[PARAM_NUMB][PARAM_LENGTH], char *parat, char *meth_ointe) {
    para_node pano;
    char *toke = parat;
    char *last_str;
    // printf("parat:|%s|\n", parat);
    // printf("meth_ointe:|%s|\n", meth_ointe);
    char conte[PARAM_LENGTH];
    int inde = 0x00;
    if ((last_str = parse_void(meth_ointe))) {
        for (; ('\0' != last_str[0x00]) && (PARAM_NUMB >= inde); inde++) {
            // printf("last_str:%s\n", last_str);
            last_str = parse_ointe_ex(conte, last_str);
            if (!last_str) break;
            // printf("ex ointe_data:|%s|\n", conte);
            conv_oint_para(&pano, conte);
            build_para_text(ointe_data[inde], ointe_para[inde], &pano, PARA_TOK);
            // printf("+++ conve_para para:|%s| pars:|%s| data:|%s|\n", para, pars, data);
            // printf("ointe_data[inde]:%s\n", ointe_data[inde]);
            toke = type_stri(toke, pano.type);
            // printf("ex pano.type:|%s| parat:|%s|\n", pano.type, parat);
        }
    } else echo_void(parat);
    MKZERO(ointe_data[inde]);
    MKZERO(ointe_para[inde]);
    //
    return 0x00;
}

//

char *conv_decla_vtype(char *vtype, char *decla) {
    char meth_ointe[METH_LENGTH];
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int ioitype = parse_ohead(meth_ointe, decla);
    if ((-1 == ioitype) || (0x01 == ioitype)) return NULL;
    conv_ointe_type(vtype, meth_ointe);
    //
    return vtype;
}

//

char *conv_iinte_type(char *parat, struct varia_type vtype[CDATNO_NUMB], char *paras) {
    char data_type[PARA_TYPE_LEN] = {"\0"};
    char *last_str;
    char *toke = parat;
    //
    int inde = 0x00;
    if ((last_str = parse_void(paras))) {
        for (; last_str && ('\0' != last_str[0x00]) && (PARAM_NUMB >= inde); inde++) {
            // printf("last_str:%s\n", last_str);
            last_str = parse_iinte(data_type, vtype, last_str);
            // printf("ointe_data[inde]:%s\n", ointe_data[inde]);
            toke = type_stri(toke, data_type);
            // printf("data_type:|%s| parat:|%s|\n", data_type, parat);
        }
    } else echo_void(parat);
    //
    return parat;
}