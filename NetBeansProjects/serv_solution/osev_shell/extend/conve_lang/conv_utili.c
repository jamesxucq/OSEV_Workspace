
#include "conv_stri.h"
#include "pars_utili.h"
#include "conv_utili.h"

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

//
//

struct varia_type {
    char name[PARAM_LENGTH];
    char type[PARAM_LENGTH];
};

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
#define CONST_TYPE_TOK "int"
#define check_const_type(const_type) strcmp(CONST_TYPE_TOK, const_type)

// check inner invoke argument data type

//

struct vchi_node {
    const char *text;
    char *value;
    int type;
};

static const struct vchi_node vari_valu_tab[] = {
    {"int", "int", 0x00},
    {"unsigned int", "uint", 0x00},
    {"short", "short", 0x00},
    {"unsigned short", "ushort", 0x00},
    {"long", "long", 0x00},
    {"unsigned long", "ulong", 0x00},
    {"char", "char", 0x00},
    {"unsigned char", "uchar", 0x00},
    {"float", "float", 0x00},
    {"unsigned float", "ufloat", 0x00},
    {"double", "double", 0x00},
    {"unsigned double", "udouble", 0x00},
    {"char []", "strcpy", 0x01},
    {"char *", "strcpy", 0x01},
    {NULL, NULL, -1}
};

#define TVALU_STINE(VALUE, TYPE, TABLE, TEXT) { \
    struct vchi_node *item; \
    for(item = (struct vchi_node *)TABLE; item->text; ++item) \
        if(!strcasecmp(TEXT, item->text)) break; \
    VALUE = item->value; \
    TYPE = item->type;\
}

int conv_oint_para(char *para, char *data) {
    char *value;
    int type;
    char *tokep = strchr(data, ' ');
    char *last_str = lscpy(para, tokep + 0x01);
    TVALU_STINE(value, type, vari_valu_tab, para)
    printf("+++ conve_para para:|%s| value:|%s| type:|%d|\n", para, value, type);
    last_str = lccpy(last_str, ' ');
    lszcpy(last_str, data, tokep - data);
    //
    printf("+++ conve_para para:|%s| data:|%s|\n", para, data);
    return 0x00;
}

//
// #define PARA_TOK    "valu"

int conv_ointe_data(char ointe_data[PARAM_NUMB][PARAM_LENGTH], char *meth_ointe) {
    char *last_str;
    printf("meth_ointe:|%s|\n", meth_ointe);
    char conte[PARAM_LENGTH];
    int inde = 0x00;
    if ((last_str = parse_void(meth_ointe))) {
        for (; ('\0' != last_str[0x00]) && (PARAM_NUMB >= inde); inde++) {
            // printf("last_str:%s\n", last_str);
            last_str = parse_ointe_ex(conte, last_str);
            if (!last_str) return -1;
            // printf("ex ointe_data:|%s|\n", conte);
            conv_oint_para(ointe_data[inde], conte);
            // printf("ointe_data[inde]:%s\n", ointe_data[inde]);
        }
    }
    MKZERO(ointe_data[inde]);
    //
    return 0x00;
}

//

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
    strcpy(type, toke);
    strzcpy(valu, conte, toke - conte);
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

//

struct vstr_node {
    const char *text;
    char *value;
};

//
static const struct vstr_node vtoke_valu_tab[] = {
    {"int8", "signed char"},
    {"uint8", "unsigned char"},
    {"int16", "short int"},
    {"uint16", "unsigned short int"},
    {"int32", "int"},
    {"uint32", "unsigned int"},
    {"int64", "long long int"},
    {"uint64", "unsigned long long int"},
    {"byte", "char"},
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
    // printf("1 type:|%s| valu:|%s|\n", type, valu);
    parse_valu(valu);
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
        if (conv_data_styl_decl(clas_data[inde])) return -1;
        // printf("clas_data[inde]:%s\n", clas_data[inde]);
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
        printf("clas_data[inde]:|%s|\n", clas_data[inde]);
    }
    return 0x00;
}

//

/*
char *conv_decla(char *data, char *node_str) {
    char conte[LARGE_TEXT_SIZE];
    strcpy(conte, data);
    char *last_str = lscpy(data, node_str);
    last_str = lccpy(last_str, ' ');
    last_str = lscpy(last_str, conte);
    // printf("++++++ data:%s\n", data);
    return last_str;
}
 */

//
#define VOID_TOK "vo"
#define echo_void(vtype) lscpy(vtype, VOID_TOK);

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
