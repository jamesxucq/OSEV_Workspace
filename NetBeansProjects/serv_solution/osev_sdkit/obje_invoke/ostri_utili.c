#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "ostri_utili.h"

//

char *vari_type_tab[] = {
    "int",
    "short",
    "long",
    "char",
    "float",
    "double",
    NULL
};

//

static int imeth_node(char *toksp, char *tokep) {
    for (tokep--; toksp <= tokep; tokep--) {
        if (' ' == toksp[0x00]) continue;
        if (':' == toksp[0x00]) return 0x01;
        break;
    }
    //
    return 0x00;
}

char *data_node(char *conte, char *data) {
    char *toksp, *tokep;
    do {
        toksp = strchr(data, '[');
        if (!toksp) return NULL;
        tokep = strchr(toksp + 0x01, ']');
        if (!tokep) return NULL;
    } while (imeth_node(data, toksp));
    //
    strzcpy(conte, toksp + 0x01, tokep - toksp - 0x01);
    return tokep + 0x01;
}

char *argu_node(char *conte, char *data) {
    char *toksp = strchr(data, '(');
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return NULL;
    //
    strzcpy(conte, toksp + 0x01, tokep - toksp - 0x01);
    return tokep + 0x01;
}

char *parse_data(char *data, char *conte) {
    char *toksp = conte;
    for (; ' ' == toksp[0x00] || ',' == toksp[0x00]; toksp++);
    char *tokep = strchr(toksp, ',');
    if (tokep) strzcpy(data, toksp, tokep - toksp);
    else strcpy(data, toksp);
    //
    return tokep;
}

//

char *parse_clasn(char *clasn, char *clas_decl) {
    char *toksp = kill_blank(clas_decl);
    if (!toksp) return NULL;
    char *tokep = strpbrk(toksp, " <");
    if (!tokep) return NULL;
    strzcpy(clasn, toksp, tokep - toksp);
    //
    return tokep;
}

char *pass_clasn(char *clas_decl) {
    char *toke = kill_blank(clas_decl);
    if (!toke) return NULL;
    toke = strpbrk(toke, " <");
    if (!toke) return NULL;
    return toke;
}

//

char *parse_space(char *clasn, char *metnm, char *space) {
    char *toksp = kill_blank(space);
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    strzcpy(clasn, toksp, tokep - toksp);
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(metnm, tokep + 0x01, toksp - tokep - 0x01);
    //
    return toksp;
}

char *parse_space_ex(char *metnm, char *space) {
    char *toksp = kill_blank(space);
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) return NULL;
    //
    toksp = strpbrk(tokep + 0x01, " <");
    if (!toksp) return NULL;
    strzcpy(metnm, tokep + 0x01, toksp - tokep - 0x01);
    //
    return toksp;
}

char *pass_space(char *meth_txt) {
    char *toke = strchr(meth_txt, '<');
    if (!toke) return NULL;
    return toke;
}

static char *couple_bracket(char *stri) {
    if (!stri || '(' != stri[0x00]) return NULL;
    char *toke = stri + 0x01;
    //
    for (; '\0' != toke[0x00]; toke++) {
        if ('(' == toke[0x00]) {
            for (toke++; isdigit(toke[0x00]); toke++);
            if (')' != toke[0x00]) return NULL;
        } else if (')' == toke[0x00]) break;
    }
    if ('\0' == toke[0x00]) return NULL;
    //
    return toke;
}

/*
 <(void)int>
 <(x int)>
 <(void)int, (x int)>
 */

// -1:error 0x01:single 0x02:double

static int inte_count(char **last_char, char *meth_inte, char *meth_txt) {
    char *toksp = strchr(meth_txt, '<');
    if (!toksp) return -1;
    char *tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return -1;
    //
    strzcpy(meth_inte, toksp, tokep - toksp + 0x01);
    int inte_numb = 0x00;
    for (toksp = meth_inte; '\0' != toksp[0x00]; toksp++) {
        if ('(' == toksp[0x00]) {
            toksp = couple_bracket(toksp);
            if (!toksp) break;
            inte_numb++;
        }
    }
    //
    if (last_char) *last_char = tokep + 0x01;
    return inte_numb;
}

// -1:error 0x00:inn_out 0x01:inn 0x02:out

static int iointe_type_si(char *meth_inte) {
    char *toksp = strchr(meth_inte, '(');
    if (!toksp) return -1;
    char *tokep = couple_bracket(toksp);
    if (!tokep) return -1;
    //
    int ioitype = 0x01;
    for (tokep++; '\0' != tokep[0x00]; tokep++) {
        if (isalpha(tokep[0x00])) {
            ioitype = 0x02;
            break;
        }
    }
    //
    return ioitype;
}

static int parse_iointe_sii(char *meth_iinte, char *meth_inte, int ioitype) {
    char *toksp, *tokep;
    if (0x01 == ioitype) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        strzcpy(meth_iinte, toksp, tokep - toksp + 0x01);
    }
    //
    return 0x00;
}

static int parse_iointe_sio(char *meth_ointe, char *meth_inte, int ioitype) {
    char *toksp, *tokep;
    if (0x02 == ioitype) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        strzcpy(meth_ointe, toksp, tokep - toksp + 0x01);
    }
    //
    return 0x00;
}

//

static int parse_iointe_sin(char *ointe_type, char *meth_ointe, char *meth_iinte, char *meth_inte, int ioitype) {
    char *toksp, *tokep;
    printf("pis meth_inte:%s\n", meth_inte);
    // 0x01:inn 0x02:out
    if (0x01 == ioitype) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = couple_bracket(toksp);
        if (!tokep) return -1;
        strzcpy(meth_iinte, toksp, tokep - toksp + 0x01);
    } else if (0x02 == ioitype) {
        toksp = strchr(meth_inte, '(');
        if (!toksp) return -1;
        tokep = couple_bracket(toksp);
        if (!tokep) return -1;
        strzcpy(meth_ointe, toksp, tokep - toksp + 0x01);
        //
        toksp = tokep + 0x01;
        for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
        tokep = strpbrk(toksp, " ,>");
        if (!tokep) return -1;
        strzcpy(ointe_type, toksp, tokep - toksp);
    }
    //
    return 0x00;
}

// -1:error 0x00:inn_out 0x01:out_inn

static int iointe_type_do(char *meth_inte) {
    char *toksp = meth_inte;
    int check_times = 0x02;
    int ointe_numb = 0x00;
    int ioitype = 0x00;
    //
    while (check_times--) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        char *tokep = couple_bracket(toksp);
        if (!tokep) return -1;
        //
        char *toknp = ++tokep;
        for (; '\0' != toknp[0x00]; toknp++) {
            if (',' == toknp[0x00]) {
                break;
            } else if (isalpha(toknp[0x00])) {
                ioitype = check_times;
                ointe_numb++;
                break;
            }
        }
        //
        toksp = strchr(toknp, ',');
    }
    //
    return 0x01 == ointe_numb ? ioitype : -1;
}

static int parse_iointe_doi(char *meth_iinte, char *meth_inte, int ioitype) {
    char *tokep, *toksp = meth_inte;
    if (ioitype) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        toksp = strchr(tokep + 0x01, ',');
        if (!toksp) return -1;
    }
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return -1;
    strzcpy(meth_iinte, toksp, tokep - toksp + 0x01);
    //
    return 0x00;
}

//

static int parse_iointe_doo(char *meth_ointe, char *meth_inte, int ioitype) {
    char *tokep, *toksp = meth_inte;
    if (!ioitype) {
        toksp = strchr(toksp, '(');
        if (!toksp) return -1;
        tokep = strchr(toksp + 0x01, ')');
        if (!tokep) return -1;
        toksp = strchr(tokep + 0x01, ',');
        if (!toksp) return -1;
    }
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return -1;
    strzcpy(meth_ointe, toksp, tokep - toksp + 0x01);
    //
    return 0x00;
}

//

static int parse_iointe_don(char *ointe_type, char *meth_ointe, char *meth_iinte, char *meth_inte, int ioitype) {
    char *tokep, *toksp;
    printf("pid meth_inte:%s\n", meth_inte);
    // 0x00:inn_out 0x01:out_inn
    toksp = strchr(meth_inte, '(');
    if (!toksp) return -1;
    tokep = couple_bracket(toksp);
    if (!tokep) return -1;
    if (ioitype) {
        strzcpy(meth_ointe, toksp, tokep - toksp + 0x01);
        //
        toksp = tokep + 0x01;
        for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
        tokep = strpbrk(toksp, " ,");
        if (!tokep) return -1;
        strzcpy(ointe_type, toksp, tokep - toksp);
    } else {
        strzcpy(meth_iinte, toksp, tokep - toksp + 0x01);
    }
    //
    toksp = strchr(toksp + 0x01, ',');
    if (!toksp) return -1;
    //
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    tokep = couple_bracket(toksp);
    if (!tokep) return -1;
    if (ioitype) {
        strzcpy(meth_iinte, toksp, tokep - toksp + 0x01);
    } else {
        strzcpy(meth_ointe, toksp, tokep - toksp + 0x01);
        //
        toksp = tokep + 0x01;
        for (; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
        tokep = strpbrk(toksp, " ,>");
        if (!tokep) return -1;
        strzcpy(ointe_type, toksp, tokep - toksp);
    }
    //
    return 0x00;
}

//

char *parse_head(char *ointe_type, char *meth_ointe, char *meth_iinte, char *meth_txt) {
    // printf("ph meth_txt:%s\n", meth_txt);
    char meth_inte[METH_LENGTH];
    int ioitype = -1;
    char *last_str = NULL;
    //
    int inte_numb = inte_count(&last_str, meth_inte, meth_txt);
    // printf("ph inte_numb:%d\n", inte_numb);
    switch (inte_numb) {
        case 0x01:
            ioitype = iointe_type_si(meth_inte);
            // printf("its ioitype:%d\n", ioitype);
            if (-1 == ioitype) return NULL;
            if (parse_iointe_sin(ointe_type, meth_ointe, meth_iinte, meth_inte, ioitype))
                return NULL;
            break;
        case 0x02:
            ioitype = iointe_type_do(meth_inte);
            // printf("itd ioitype:%d\n", ioitype);
            if (-1 == ioitype) return NULL;
            if (parse_iointe_don(ointe_type, meth_ointe, meth_iinte, meth_inte, ioitype))
                return NULL;
            break;
        default:
            break;
    }
    //
    return last_str;
}

//

struct vint_node {
    const char *text;
    int value;
};

#define TVALU_INTE(VALUE, TABLE, TEXT) { \
    struct vint_node *item; \
    for(item = (struct vint_node *)TABLE; item->text; ++item) \
        if(!strcmp(TEXT, item->text)) break; \
    VALUE = item->value; \
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
static const struct vint_node retype_value_table[] = {
    {"void", rtyp_void},
    {"int", rtyp_int},
    {"uint", rtyp_uint},
    {"long", rtyp_long},
    {"long long", rtyp_llon},
    //
    {"int8", rtyp_char},
    {"uint8", rtyp_ucha},
    {"int16", rtyp_shor},
    {"uint16", rtyp_usho},
    {"int32", rtyp_int},
    {"uint32", rtyp_uint},
    {"int64", rtyp_llon},
    {"uint64", rtyp_ullo},
    {"byte", rtyp_chap},
    {"char", rtyp_chap},
    {NULL, 0}
};

int parse_retype(char *retyp_valu, char *ointe_type) {
    int ointe_valu;
    TVALU_INTE(ointe_valu, retype_value_table, ointe_type)
    sprintf(retyp_valu, "%d", ointe_valu);
    return 0x00;
}

// -1:error 0x00:inn_out 0x01:inn 0x02:out

int parse_ohead(char *meth_ointe, char *decla) {
    // printf("phe meth_txt:%s\n", meth_txt);
    char meth_inte[METH_LENGTH];
    int ioitype = -1;
    //
    int inte_numb = inte_count(NULL, meth_inte, decla);
    // printf("phe inte_numb:%d\n", inte_numb);
    switch (inte_numb) {
        case 0x01:
            ioitype = iointe_type_si(meth_inte);
            // printf("its ioitype:%d\n", ioitype);
            if (-1 == ioitype || 0x01 == ioitype) break;
            parse_iointe_sio(meth_ointe, meth_inte, ioitype);
            break;
        case 0x02:
            ioitype = iointe_type_do(meth_inte);
            // printf("itd ioitype:%d\n", ioitype);
            if (-1 == ioitype) break;
            parse_iointe_doo(meth_ointe, meth_inte, ioitype);
            ioitype = 0x00;
            break;
        default:
            return -1;
            break;
    }
    //
    return ioitype;
}

// -1:error 0x00:inn_out 0x01:inn 0x02:out

int parse_ihead(char *meth_iinte, char *meth_txt) {
    // printf("phe meth_txt:%s\n", meth_txt);
    char meth_inte[METH_LENGTH];
    int ioitype = -1;
    //
    int inte_numb = inte_count(NULL, meth_inte, meth_txt);
    // printf("phe inte_numb:%d\n", inte_numb);
    switch (inte_numb) {
        case 0x01:
            ioitype = iointe_type_si(meth_inte);
            // printf("its ioitype:%d\n", ioitype);
            if (-1 == ioitype || 0x02 == ioitype) break;
            parse_iointe_sii(meth_iinte, meth_inte, ioitype);
            break;
        case 0x02:
            ioitype = iointe_type_do(meth_inte);
            // printf("itd ioitype:%d\n", ioitype);
            if (-1 == ioitype) break;
            parse_iointe_doi(meth_iinte, meth_inte, ioitype);
            ioitype = 0x00;
            break;
        default:
            return -1;
            break;
    }
    //
    return ioitype;
}

//

static int parse_cotype_sio(char *const_type, char *meth_inte, int ioitype) {
    printf("meth_inte:|%s|\n", meth_inte);
    char *toksp, *tokep;
    if (0x02 == ioitype) {
        toksp = strrchr(meth_inte, ')');
        if (!toksp) return -1;
        for (toksp++; ' ' == toksp[0x00]; toksp++);
        tokep = strchr(toksp + 0x01, '>');
        if (!tokep) return -1;
        for (; ' ' == tokep[-1]; tokep--);
        strzcpy(const_type, toksp, tokep - toksp);
    }
    //
    return 0x00;
}

// -1:error 

int parse_chead(char *const_type, char *meth_txt) {
    // printf("ph meth_txt:%s\n", meth_txt);
    char meth_inte[METH_LENGTH];
    if (0x01 != inte_count(NULL, meth_inte, meth_txt)) return -1;
    // -1:error 0x00:inn_out 0x01:inn 0x02:out
    int ioitype = iointe_type_si(meth_inte);
    if (0x02 != ioitype) return -1;
    parse_cotype_sio(const_type, meth_inte, ioitype);
    //
    return 0x00;
}

//

void parse_body(char *meth_body, char *meth_txt) {
    char *toke = strchr(meth_txt, '{');
    if (toke) strcpy(meth_body, toke);
}

//

int parse_class_actu(char *actu_head, char *clas_decl, char *meth_name) {
    // printf("clas_decl:%s\n", clas_decl);
    // printf("meth_name:%s\n", meth_name);
    char *toksp = strstr(clas_decl, meth_name);
    if (!toksp) return -1;
    toksp += strlen(meth_name);
    toksp = strchr(toksp, '(');
    if (!toksp) return -1;
    char *tokep = strchr(toksp, ')');
    if (!tokep) return -1;
    //
    strzcpy(actu_head, toksp, tokep - toksp + 0x01);
    // printf("actu_head:%s\n", actu_head);
    return 0x00;
}

//

char *parse_tok(char *node_str, int *nod_type, char *body_txt) {
    char *last_str = body_txt;
    //
    if (isalpha(last_str[0x00]) || '_' == last_str[0x00]) {
        last_str++;
        for (; isalnum(last_str[0x00]) || '_' == last_str[0x00]; last_str++);
        lszcpy(node_str, body_txt, last_str - body_txt);
        *nod_type = 0x00;
    } else if (isdigit(last_str[0x00])) {
        last_str++;
        for (; isalnum(last_str[0x00]); last_str++);
        lszcpy(node_str, body_txt, last_str - body_txt);
        *nod_type = 0x01;
    } else {
        last_str++;
        for (; !isalnum(last_str[0x00]) && '_' != last_str[0x00]; last_str++) {
            if ('\0' == last_str[0x00]) {
                lszcpy(node_str, body_txt, last_str - body_txt);
                *nod_type = 0x02;
                return NULL;
            }
        }
        lszcpy(node_str, body_txt, last_str - body_txt);
        *nod_type = 0x02;
    }
    //
    return last_str;
}

//

static char *parse_actual(char *actu_data, char *param) {
    char *tokep, *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00]; toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!tokep) return NULL;
    strzcpy(actu_data, toksp, tokep - toksp);
    //
    return tokep + 0x01;
}

static char *parse_formal(char *form_data, char *param) {
    char *tokep, *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00]; toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    tokep = strchr(toksp + 0x01, ' ');
    if (!tokep) return NULL;
    strzcpy(form_data, toksp, tokep - toksp);
    //
    tokep = strchr(tokep + 0x01, ',');
    if (!tokep) return NULL;
    //
    return toksp + 0x01;
}

int parse_meth_head(char form_data[PARAM_NUMB][PARAM_LENGTH], char *meth_txt) {
    char *last_str;
    // printf("meth_txt:%s\n", meth_txt);
    int inde = 0x00;
    if ((last_str = parse_void(meth_txt))) {
        for (; last_str && ('\0' != last_str[0x00]) && (PARAM_NUMB >= inde); inde++) {
            // printf("last_str:%s\n", last_str);
            last_str = parse_formal(form_data[inde], last_str);
            // printf("form_data[inde]:%s\n", form_data[inde]);
        }
    }
    // printf("param_type:%s\n", param_type);
    MKZERO(form_data[inde]);
    //
    return 0x00;
}

int parse_class_meth(char actu_data[PARAM_NUMB][PARAM_LENGTH], char *actu_head) {
    char *last_str;
    // printf("actu_head:%s\n", actu_head);
    int inde = 0x00;
    if ((last_str = parse_void(actu_head))) {
        for (; last_str && ('\0' != last_str[0x00]) && (PARAM_NUMB >= inde); inde++) {
            // printf("last_str:%s\n", last_str);
            last_str = parse_actual(actu_data[inde], last_str);
            // printf("actu_data[inde]:%s\n", actu_data[inde]);
        }
    }
    // printf("inde:%d\n", inde);
    MKZERO(actu_data[inde]);
    //
    return 0x00;
}

//
static osv_str_t PARA_VOID_TOK = osv_stri("void");

char *parse_void(char *param) {
    char *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00]; toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    if (!strncmp(PARA_VOID_TOK.data, toksp, PARA_VOID_TOK.len)) return NULL;
    //
    char *tokep = toksp;
    for (; ',' == tokep[0x00] || ' ' == tokep[0x00]; tokep++) {
        if ('\0' == tokep[0x00] || ')' == tokep[0x00]) return NULL;
        else if (isalnum(tokep[0x00])) break;
    }
    //
    return toksp;
}

//

char *parse_ointe(char *data_type, char *param) {
    // printf("param:|%s|\n", param);
    char *tokep, *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00] || ')' == toksp[0x00] || isdigit(toksp[0x00]); toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    //
    toksp = strchr(toksp + 0x01, ' ');
    if (!toksp) return NULL;
    for (; ' ' == toksp[0x00]; toksp++);
    tokep = strpbrk(toksp + 0x01, ", ()");
    if (!toksp) return NULL;
    strzcpy(data_type, toksp, tokep - toksp);
    //
    return tokep + 0x01;
}

char *parse_ointe_decla(char *data_type, char *param) {
    // printf("param:|%s|\n", param);
    char *tokep, *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00] || ')' == toksp[0x00]; toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    //
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!toksp) return NULL;
    strzcpy(data_type, toksp, tokep - toksp);
    //
    return tokep + 0x01;
}

char *parse_ointe_ex(char *ointe_data, char *param) {
    // printf("ex param:|%s|\n", param);
    char *tokep, *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00] || ')' == toksp[0x00]; toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    tokep = strpbrk(toksp + 0x01, ",)");
    if (!tokep) return NULL;
    strzcpy(ointe_data, toksp, tokep - toksp);
    //
    return tokep + 0x01;
}

//

int parse_class_data(char *clasn, char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *clas_decl) {
    char *token, *toked;
    token = parse_clasn(clasn, clas_decl);
    if (!token) return -1;
    printf("parse_class_data, clasn:|%s|\n", clasn);
    //
    char node_conte[CNODE_LENGTH];
    int inde = 0x00;
    while ((token = data_node(node_conte, token))) {
        // printf("node_conte:%s\n", node_conte);
        for (toked = node_conte; toked;) {
            toked = parse_data(clas_data[inde++], toked);
            // printf("clas_data[inde++]:%s\n", clas_data[inde - 0x01]);
        }
    }
    MKZERO(clas_data[inde]);
    //
    return 0x00;
}

int parse_class_data_ex(char clas_data[CDATNO_NUMB][PARAM_LENGTH], char *clas_decl) {
    char *token, *toked;
    token = pass_clasn(clas_decl);
    if (!token) return -1;
    //
    char node_conte[CNODE_LENGTH];
    int inde = 0x00;
    while ((token = data_node(node_conte, token))) {
        // printf("pcde node_conte:%s\n", node_conte);
        for (toked = node_conte; toked;) {
            toked = parse_data(clas_data[inde++], toked);
            // printf("pcde clas_data[inde++]:%s\n", clas_data[inde - 0x01]);
        }
    }
    MKZERO(clas_data[inde]);
    //
    return 0x00;
}

//

static char *bound_node(char *conte, char *data) {
    char *toksp = kill_blank(data);
    if (!toksp) return NULL;
    if ('<' == toksp[0x00]) toksp = kill_blank(toksp + 0x01);
    for (; '[' == toksp[0x00]; toksp = kill_blank(toksp + 0x01)) {
        for (; ']' != toksp[0x00]; toksp++);
        for (; ',' != toksp[0x00]; toksp++);
    }
    //
    char *tokep = strpbrk(toksp, " (");
    if (!tokep) return NULL;
    strzcpy(conte, toksp, tokep - toksp);
    //
    tokep = strchr(tokep + 0x01, ')');
    if (!tokep) return NULL;
    tokep = strpbrk(tokep + 0x01, ",>");
    if (tokep) tokep++;
    return tokep;
}

// -1:error 0x00:normal 0x01:constructor

int chk_meth_type(char *clas_decl, char *metnm) {
    char clasn[CLASS_LENGTH];
    char *toke = parse_clasn(clasn, clas_decl);
    if (!toke) return -1;
    if (!strcmp(metnm, clasn)) return 0x01;
    //
    printf("check clas_decl:%s metnm:%s\n", clas_decl, metnm);
    char bound[METH_LENGTH];
    while ((toke = bound_node(bound, toke))) {
        printf("bound:%s\n", bound);
        if (!strcmp(metnm, bound)) return 0x00;
    }
    //
    printf("cmt not found:%s\n", metnm);
    return -1;
}

//

static int node_type(char *conte) {
    for (; '\0' != conte[0x00]; conte++) {
        if (' ' == conte[0x00]) continue;
        if ('[' == conte[0x00]) return 0x01;
        break;
    }
    return 0x00;
}

static char *prev_stri(char *data, char *psta) {
    static char pstr[METH_LENGTH];
    for (data--; (psta > data) && (' ' == data[0x00]); data--);
    char *toke = data;
    for (; (psta > toke) && (' ' != toke[0x00] && ',' != toke[0x00]); toke--);
    strzcpy(pstr, toke + 0x01, data - toke);
    return pstr;
}

static char *next_stri(char *nstr, char *paras, char *data) {
    char *toksp = kill_blank(data + 0x01);
    if (!toksp) return NULL;
    char *tokep = strpbrk(toksp + 0x01, " (");
    if (!tokep) return NULL;
    strzcpy(nstr, toksp, tokep - toksp);
    //
    toksp = strchr(tokep, '(');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return NULL;
    strzcpy(paras, toksp, tokep - toksp);
    //
    tokep = strchr(tokep + 0x01, ',');
    if (!tokep) return NULL;
    return tokep + 0x01;
}

static char *nend_type(int *entyp, char *paras, char *data) {
    char *toksp = strchr(data, '(');
    if (!toksp) return NULL;
    char *tokep = strchr(data + 0x01, ')');
    if (!tokep) return NULL;
    strzcpy(paras, toksp, tokep - toksp);
    //
    toksp = strpbrk(tokep + 0x01, ",>");
    if (!toksp) return NULL;
    *entyp = 0x00;
    for (; toksp > tokep; tokep++) {
        if (']' == tokep[0x00]) {
            *entyp = 0x01;
            break;
        }
    }
    //
    if ('>' == toksp[0x00]) return NULL;
    return toksp + 0x01;
}

char *conte_node(char *clas, char *meth, char *paras, char *data) {
    static char clasn[CLASS_LENGTH];
    char *toksp, *tokep;
    //
    if ('\0' == clasn[0x00]) {
        char *toksp = strchr(data, ':');
        if (!toksp) return NULL;
        //
        lscpy(clas, prev_stri(toksp, data));
        if (node_type(toksp)) strcpy(clasn, clas);
        tokep = next_stri(meth, paras, toksp);
    } else {
        lscpy(clas, clasn);
        toksp = kill_blank(data);
        tokep = strpbrk(toksp, " (");
        if (!tokep) return NULL;
        lszcpy(meth, toksp, tokep - toksp);
        //
        int entyp;
        tokep = nend_type(&entyp, paras, tokep);
        if (entyp) MKZERO(clasn);
    }
    //
    return tokep;
}

//
#define TVALU_VARIAE(TVALU, TABLE, TEXT) { \
    int tind = 0x00; \
    for(; '\0' != TABLE[tind].name[0x00]; ++tind) \
        if(!strcmp(TEXT, TABLE[tind].name)) break; \
    strcpy(TVALU, TABLE[tind].type); \
}

char *parse_iinte(char *data_type, struct varia_type vtype[CDATNO_NUMB], char *param) {
    char varia[PARAM_LENGTH];
    // printf("param:|%s|\n", param);
    char *tokep, *toksp = param;
    for (; ',' == toksp[0x00] || ' ' == toksp[0x00] || '(' == toksp[0x00] || ')' == toksp[0x00]; toksp++) {
        if ('\0' == toksp[0x00]) return NULL;
    }
    //
    tokep = strpbrk(toksp + 0x01, ", )");
    if (!toksp) return NULL;
    strzcpy(varia, toksp, tokep - toksp);
    TVALU_VARIAE(data_type, vtype, varia)
            //
    return tokep + 0x01;
}

//

char *node_line(char *node_cont, char *conte) {
    char *last_str = conte;
    //
    for (; '\0' != last_str[0x00]; last_str++) {
        if ('"' == last_str[0x00]) {
            last_str++;
            for (; '\0' != last_str[0x00]; last_str++) {
                if ('\\' == last_str[0x00]) last_str++;
                else if ('"' == last_str[0x00]) break;
            }
        }
        if (';' == last_str[0x00] || '{' == last_str[0x00] || '}' == last_str[0x00]) {
            last_str++;
            break;
        }
    }
    //
    lszcpy(node_cont, conte, last_str - conte);
    return last_str;
}

//

int check_decla(char *conte) {
    char *last_str = strlchr(conte);
    for (; conte != last_str && (';' == last_str[0x00] || ' ' == last_str[0x00]); last_str--);
    if (conte == last_str) return 0x00;
    if (')' == last_str[0x00]) {
        for (; conte != last_str && '(' != last_str[0x00]; last_str--);
        if (conte == last_str) return 0x00;
        for (last_str--; conte != last_str && ' ' == last_str[0x00]; last_str--);
        if (conte == last_str) return 0x00;
    }
    //
    char decla_type[LINE_LENGTH];
    char *toke = last_str;
    for (last_str--; conte != last_str && ' ' != last_str[0x00]; last_str--);
    if (conte == last_str) return 0x00;
    lszcpy(decla_type, last_str + 0x01, toke - last_str);
    // printf("decla_type:%s\n", decla_type);
    //
    int inde;
    for (inde = 0x00; vari_type_tab[inde]; inde++) {
        if (!strcmp(decla_type, vari_type_tab[inde]))
            return 0x01;
    }
    //
    return 0x00;
}

//

int parse_decla(char *type, char vari[PARAM_NUMB][PARAM_LENGTH], char *valu, char *decla) {
    char *last_str = strlchr(decla);
    for (; decla != last_str && (';' == last_str[0x00] || ' ' == last_str[0x00]); last_str--);
    if (decla == last_str) return 0x00;
    //
    char *toke = last_str;
    int decla_type = 0x00;
    if (')' == last_str[0x00]) {
        decla_type = 0x02;
        //
        for (; decla != last_str && '(' != last_str[0x00]; last_str--);
        if (decla == last_str) return 0x00;
        lszcpy(valu, last_str + 0x01, toke - last_str - 0x01);
        for (last_str--; decla != last_str && ' ' == last_str[0x00]; last_str--);
        if (decla == last_str) return 0x00;
    } else decla_type = 0x01;
    //
    toke = last_str;
    for (last_str--; decla != last_str && ' ' != last_str[0x00]; last_str--);
    if (decla == last_str) return 0x00;
    lszcpy(type, last_str + 0x01, toke - last_str);
    // printf("type:|%s| valu:|%s|\n", type, valu);
    //
    int inde = 0x00;
    for (;; inde++) {
        toke = last_str--;
        for (; decla != last_str && ',' != last_str[0x00]; last_str--);
        if (decla == last_str) {
            lszcpy(vari[inde], last_str, toke - last_str);
            // printf("vari[inde]:|%s|\n", vari[inde]);
            break;
        }
        lszcpy(vari[inde], last_str + 0x01, toke - last_str - 0x01);
        // printf("vari[inde]:|%s|\n", vari[inde]);
    }
    MKZERO(vari[++inde]);
    //
    return decla_type;
}


//

unsigned int split_para_colu(char para_arra[PARA_COLU_SIZE][PARAM_LENGTH], char *data) {
    // printf("split_para_colu:|%s|\n", data);
    unsigned int attrib = 0x00;
    //
    char *tokep, *toksp = data;
    int inde = 0x00;
    for (; toksp && '\0' != toksp[0x00] && PARA_COLU_SIZE > inde; inde++) {
        tokep = strpbrk(toksp, " =()");
        if (tokep) {
            switch (tokep[0x00]) {
                case ' ':
                    strzcpy(para_arra[inde], toksp, tokep - toksp);
                    break;
                case '=':
                    if (toksp != tokep) strzcpy(para_arra[inde], toksp, tokep - toksp);
                    attrib |= PARA_DEFA;
                    break;
                case '(':
                case ')':
                    strzcpy(para_arra[inde], toksp, tokep - toksp);
                    attrib |= PARA_ARRA;
                    break;
            }
            toksp = kill_blank(tokep + 0x01);
        } else {
            strcpy(para_arra[inde], toksp);
            toksp = NULL;
        }
        // printf("para_arra[%d]:|%s|\n", inde, para_arra[inde]);
    }
    //
    return attrib;
}


//
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

static const struct vint_node ptyp_valu_tab[] = {
    {"short", PARA_NUMB},
    {"int", PARA_NUMB},
    {"uint", PARA_NUMB},
    {"long", PARA_NUMB},
    {"long long", PARA_NUMB},
    //
    {"int8", PARA_NUMB},
    {"uint8", PARA_NUMB},
    {"int16", PARA_NUMB},
    {"uint16", PARA_NUMB},
    {"int32", PARA_NUMB},
    {"uint32", PARA_NUMB},
    {"int64", PARA_NUMB},
    {"uint64", PARA_NUMB},
    {"byte", PARA_BYTE},
    {"char", PARA_CHAR},
    {NULL, 0x00}
};

#define TVALU_INTO(VALUE, TABLE, TEXT) { \
    struct vint_node *item; \
    for(item = (struct vint_node *)TABLE; item->text; ++item) \
        if(!strcmp(TEXT, item->text)) break; \
    VALUE |= item->value; \
}

int parse_para_colu(para_node *pano, char para_arra[PARA_COLU_SIZE][PARAM_LENGTH]) {
    strcpy(pano->name, para_arra[0x00]);
    if (PARA_DEFA & pano->attri) {
        strcpy(pano->defa, para_arra[0x01]);
        strcpy(pano->type, para_arra[0x02]);
        if (PARA_ARRA & pano->attri) strcpy(pano->arra, para_arra[0x03]);
    } else {
        strcpy(pano->type, para_arra[0x01]);
        if (PARA_ARRA & pano->attri) strcpy(pano->arra, para_arra[0x02]);
    }
    TVALU_INTO(pano->attri, ptyp_valu_tab, pano->type)
    if ((PARA_CHAR & pano->attri) && (PARA_DEFA & pano->attri)) quote_decode(pano->defa);
    //
    return 0x00;
}