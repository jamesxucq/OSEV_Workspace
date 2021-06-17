#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_macro.h"
#include "stri_utili.h"
#include "xml_utili.h"


//

char *get_attval(char *value, char *attrib) {
    char dupstr[MIN_TEXT_LEN];
    strcpy(dupstr, value);
    //
    char *toksp = strstr(dupstr, attrib);
    if (!toksp) return NULL;
    toksp = strchr(toksp, '=');
    if (!toksp) return NULL;
    toksp = strchr(toksp, '"');
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, '"');
    if (!toksp) return NULL;
    //
    strzcpy(value, toksp, tokep - toksp);
    return value;
}

//

char *get_attval2(char *value1, char *value2, char *attrib1, char *attrib2) {
    char dupstr[MIN_TEXT_LEN];
    strcpy(dupstr, value1);
    //
    char *toksp = strstr(dupstr, attrib1);
    if (!toksp) return NULL;
    toksp = strchr(toksp, '=');
    if (!toksp) return NULL;
    toksp = strchr(toksp, '"');
    if (!toksp) return NULL;
    char *tokep = strchr(toksp + 0x01, '"');
    if (!toksp) return NULL;
    strzcpy(value1, toksp, tokep - toksp);
    //
    toksp = strstr(tokep + 0x01, attrib2);
    if (!toksp) return NULL;
    toksp = strchr(toksp, '=');
    if (!toksp) return NULL;
    toksp = strchr(toksp, '"');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '"');
    if (!toksp) return NULL;
    strzcpy(value2, toksp, tokep - toksp);
    //
    return value1;
}