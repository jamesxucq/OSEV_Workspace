#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commo_header.h"

#include "conattr.h"
#include "contain.h"
#include "cona_utili.h"
#include "cona_list.h"
#include "osev_struct.h"

//

contain *creat_conta_obje(char *osdb, char *cont_name, unsigned int stora_type) {
    char data_type[CLASS_LENGTH];
    osv_oid_t oid;
    if (find_cattr(&oid, data_type, cont_name, osdb)) return NULL;
    //
    contain *conta;
    conta = (contain *) malloc(sizeof (contain));
    if (!conta) return NULL;
    //
    memcpy(&conta->oid, &oid, sizeof (osv_oid_t));
    strcpy(conta->osdb_name, osdb);
    strcpy(conta->data_type, data_type);
    strcpy(conta->cont_name, cont_name);
    conta->stora_ha = _storage_ha_[stora_type];
    //
    return conta;
}

//

int qload_conta_obje(struct cono_list *clist) {
    cont_list *colist;
    struct cono_list *clistmp;
    for (clistmp = clist; clistmp; clistmp = clistmp->next) {
        _LOG_DEBUG("qload_conta_obje:%s", clistmp->_osdb_);
        colist = load_cattr_osdb(clistmp->_osdb_);
        inser_conta_list(&clistmp->cono_valu.conda, colist);
        dele_colst(colist);
    }
    //
    return 0x00;
}

//

struct vcha_node {
    const char *text;
    char value;
};

#define TVALU_CHAE(VALUE, TABLE, TEXT) { \
    struct vcha_node *item; \
    for(item = (struct vcha_node *)TABLE; item->text; ++item) \
        if(!strcasecmp(TEXT, item->text)) break; \
    VALUE = item->value; \
}

// int8_t uint8_t int16_t uint16_t int32_t uint32_t int64_t uint64_t char stri

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

static char *conve_types(char *types, char *data, char *slen) {
    char *last_str = types;
    //
    if ((!strcmp("char", data) || !strcmp("byte", data)) && slen[0x00]) last_str = lscpy(last_str, slen);
    TVALU_CHAE(last_str[0x00], types_value_tab, data)
            (++last_str)[0x00] = '\0';
    //
    return last_str;
}

static char *conve_columns(char *columns, char *data) {
    char *last_str = lccpy(columns, ',');
    last_str = lscpy(last_str, data);
    return last_str;
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

static int parse_data_styl(char *type, char *valu, char *size, char *data) {
    if (!split_type_valu(type, valu, data)) return -1;
    // printf("1 type:|%s| valu:|%s|\n", type, valu);
    parse_valu(valu);
    blank_decode(valu);
    //
    parse_type(size, type);
    blank_decode(size);
    blank_decode(type);
    // printf("2 type:|%s| valu:|%s| size:|%s|\n", type, valu, size);
    return 0x00;
}
//

static int creat_columns_types(char *types, char *columns, char data[CDATNO_NUMB][PARAM_LENGTH]) {
    char type[PARAM_LENGTH], valu[PARAM_LENGTH], size[PARAM_LENGTH];
    char *last_type = types;
    char *last_colu = columns;
    //
    int inde;
    for (inde = 0x00; '\0' != data[inde][0x00]; inde++) {
        if (parse_data_styl(type, valu, size, data[inde])) return -1;
        // printf("clas_data[inde]:|%s|\n", data[inde]);
        last_type = conve_types(last_type, type, size);
        last_colu = conve_columns(last_colu, valu);
    }
    return 0x00;
}

// "key_format=3t,value_format=SSS,columns=(id,name,address,phone)"

static char *conte_columns_types(char *forma, char *types, char *columns) {
    char *last_str = lscpy(forma, "key_format=r,value_format=");
    last_str = lscpy(last_str, types);
    last_str = lscpy(last_str, ",columns=(stoid");
    last_str = lscpy(last_str, columns);
    last_str = lccpy(last_str, ')');
    //
    return forma;
}

int conve_conta_types(char *forma_types, char clas_data[CDATNO_NUMB][PARAM_LENGTH]) {
    char types[TYPES_LENGTH];
    char columns[COLUMN_LENGTH];
    //
    creat_columns_types(types, columns, clas_data);
    conte_columns_types(forma_types, types, columns);
    // printf("forma_types:%s\n", forma_types);
    return 0x00;
}