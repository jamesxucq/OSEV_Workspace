
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exptoke.h"


//
struct stui_node {
    const char *text;
    unsigned int value;
};

#define TVALU_STUI(VALUE, TABLE, TEXT) { \
    struct stui_node *item; \
    for(item = (struct stui_node *)TABLE; item->text; ++item) \
        if(!strcasecmp(TEXT, item->text)) break; \
    VALUE = item->value; \
}

//
static const struct stui_node alpha_value_table[] = {
    {"OR", OR_TOKE},
    {"AND", AND_TOKE},
    {"NOT", NOT_TOKE},
    {"IS", IS_TOKE},
    {"MATCH", MATCH_TOKE},
    {"LIKE", LIKE_KW_TOKE},
    {"BETWEEN", BETWEEN_TOKE},
    {"IN", IN_TOKE},
    {"ESCAPE", ESCAPE_TOKE},
    {"CTIME", CTIME_KW_TOKE},
    {"ISNULL", ISNULL_TOKE},
    {"NOTNULL", NOTNULL_TOKE},
    {"BITAND", BITAND_TOKE},
    {"BITOR", BITOR_TOKE},
    {"LSHIFT", LSHIFT_TOKE},
    {"RSHIFT", RSHIFT_TOKE},
    {"CONCAT", CONCAT_TOKE},
    {"COLLATE", COLLATE_TOKE},
    {"BITNOT", BITNOT_TOKE},
    {"ON", ON_TOKE},
    {"JOIN", JOIN_KW_TOKE},
    {"NULL", NULL_TOKE},
    // {"DISTINCT", DISTINCT_TOKE},
    // {"ALL", ALL_TOKE},
    {NULL, ID_TOKE}
};

unsigned int get_alpha_toke(char *toke_stri) {
    unsigned int alpha_toke;
    TVALU_STUI(alpha_toke, alpha_value_table, toke_stri)
    return alpha_toke;
}