#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "pretty.h"

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

struct vint_node {
    const char chav;
    int value;
};

#define TVALU_INTE(VALUE, TABLE, CHAV) { \
    struct vint_node *item; \
    for(item = (struct vint_node *)TABLE; '\0' != item->chav; ++item) \
        if(item->chav == CHAV) break; \
    VALUE = item->value; \
}

enum data_type {
    byte_typ,
    ubyte_typ,
    shor_typ,
    usho_typ,
    int_typ,
    uint_typ,
    llon_typ,
    ullo_typ,
    obid_typ,
    char_typ,
    none_typ
};

static const struct vint_node types_value_tab[] = {
    {'b', byte_typ}, // int8_t
    {'B', ubyte_typ}, // uint8_t
    {'h', shor_typ}, // int16_t
    {'H', usho_typ}, // uint16_t
    {'i', int_typ}, // int32_t
    {'I', uint_typ}, // uint32_t
    {'q', llon_typ}, // int64_t
    {'Q', ullo_typ}, // uint64_t  
    {'o', obid_typ}, // object_id
    {'O', obid_typ}, // object_id
    {'s', byte_typ}, // byte
    {'S', char_typ}, // char
    {'\0', none_typ} //
};

static char *print_type(int *vtype, int *plen, char *style_str) {
    char len_str[64];
    //
    char *toke = style_str;
    if (isdigit(toke[0x00])) {
        for (; '\0' != toke[0x00] && isdigit(toke[0x00]); toke++);
        strzcpy(len_str, style_str, toke - style_str);
        *plen = atoi(len_str);
    } else *plen = 0x00;
    TVALU_INTE((*vtype), types_value_tab, toke[0x00])
            //
    return toke + 0x01;
}

//

char *print_char(char *result_str, char *value) {
    char char_valu = value[0x00];
    // printf("print_char char_valu:|%d|\n", (int) char_valu);
    char *last_str = lsprif(result_str, "|%d", (int) char_valu);
    return last_str;
}

char *print_ucha(char *result_str, char *value) {
    unsigned char ucha_valu = value[0x00];
    // printf("print_ucha ucha_valu:|%u|\n", (unsigned int) ucha_valu);
    char *last_str = lsprif(result_str, "|%u", (unsigned int) ucha_valu);
    return last_str;
}

char *print_shor(char *result_str, char *value) {
    short *shor_valu = (short *) value;
    // printf("print_shor shor_valu:|%hd|\n", shor_valu[0x00]);
    char *last_str = lsprif(result_str, "|%hd", shor_valu[0x00]);
    return last_str;
}

char *print_usho(char *result_str, char *value) {
    unsigned short *usho_valu = (unsigned short *) value;
    // printf("print_usho usho_valu:|%hu|\n", usho_valu[0x00]);
    char *last_str = lsprif(result_str, "|%hu", usho_valu[0x00]);
    return last_str;
}

char *print_int(char *result_str, char *value) {
    int *int_valu = (int *) value;
    // printf("print_int int_valu:|%d|\n", int_valu[0x00]);
    char *last_str = lsprif(result_str, "|%d", int_valu[0x00]);
    return last_str;
}

char *print_uint(char *result_str, char *value) {
    unsigned int *uint_valu = (unsigned int *) value;
    // printf("print_uint uint_valu:|%u|\n", uint_valu[0x00]);
    char *last_str = lsprif(result_str, "|%u", uint_valu[0x00]);
    return last_str;
}

char *print_llon(char *result_str, char *value) {
    long long *llon_valu = (long long *) value;
    // printf("print_llon llon_valu:|%lld|\n", llon_valu[0x00]);
    char *last_str = lsprif(result_str, "|%lld", llon_valu[0x00]);
    return last_str;
}

char *print_ullo(char *result_str, char *value) {
    unsigned long long *ullo_valu = (unsigned long long *) value;
    // printf("print_ullo ullo_valu:|%llu|\n", ullo_valu[0x00]);
    char *last_str = lsprif(result_str, "|%llu", ullo_valu[0x00]);
    return last_str;
}

static char *oidstr_se(char *oid_stri, she_oid_t *obje_oid) {
    char *toksp = oid_stri;
    char *tokst = ((char *) obje_oid);
    unsigned int inde;
    for (inde = 0x00; inde < OID_BINARY_LEN; inde++) {
        sprintf(toksp, "%02x", (unsigned char) tokst[0x00]);
        toksp += 0x02;
        tokst++;
    }
    oid_stri[24] = '\0';
    return oid_stri;
}

char *print_obid(char *result_str, char *value) {
    char oid_stri[OID_LINE_LEN];
    oidstr_se(oid_stri, (she_oid_t *) value);
    // printf("print_obid oid_stri:|%s|\n", oid_stri);
    char *last_str = lsprif(result_str, "|%s", oid_stri);
    return last_str;
}

char *print_stri(char *result_str, char *value, int len) {
    char *stri_valu = value;
    stri_valu[len] = '\0';
    // printf("print_stri stri_valu:|%s|\n", stri_valu);
    char *last_str = lsprif(result_str, "|%s", stri_valu);
    return last_str;
}

static char *(*print_tab[])(char *, char *) = {
    print_char,
    print_ucha,
    print_shor,
    print_usho,
    print_int,
    print_uint,
    print_llon,
    print_ullo,
    print_obid
};

static int len_vtype_tab[] = {
    0x01,
    0x01,
    0x02,
    0x02,
    0x04,
    0x04,
    0x08,
    0x08,
    0x0c,
    0x00
};

// 0x00:OK -1:error

int hand_pretty(char **parae, shel_resu *resu) {
    char *style_str;
    char query_data[LARGE_TEXT_SIZE];
    //
    if (resu->resu_type) return -1;
    memcpy(query_data, resu->resu_data, resu->res_len);
    char *posi_str = query_data;
    char *last_str = resu->resu_data;
    quote_decode(parae[0x00]);
    //
    int inde = 0x00;
    for (; resu->res_len > (posi_str - query_data); inde++) {
        style_str = parae[0x00];
        int vtype, plen;
        while ('\0' != style_str[0x00]) {
            style_str = print_type(&vtype, &plen, style_str);
            // printf("vtype:%d plen:%d style_str:|%s|\n", vtype, plen, style_str);
            if (char_typ == vtype) {
                last_str = print_stri(last_str, posi_str, plen);
                posi_str += plen;
            } else {
                last_str = print_tab[vtype](last_str, posi_str);
                posi_str += len_vtype_tab[vtype];
            }
        }
        last_str = lscpy(last_str, "|\n");
    }
    last_str = lsprif(last_str, "found %d objectes.\n", inde);
    resu->res_len = strlen(resu->resu_data);
    //
    return 0x00;
}