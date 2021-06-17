#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "./conve_lang/conv_gcc_cpp.h"
#include "conve.h"

//

static char *lastp_array(char **parae) {
    char *last_str = NULL;
    char **lastp_tok = parae;
    for (; lastp_tok[0x00]; lastp_tok++)
        last_str = lastp_tok[0x00];
    //
    return last_str;
}

//
#define COMP_GCC_TOK "GCC"
#define COMP_MSVC_TOK "MSVC"
#define COMP_JAVAC_TOK "JAVAC"

// -1:error 0x00:unknow 0x01:class 0x02:conta

static int build_compi_type(char **parae) {
    char *last_str = lastp_array(parae);
    if (!last_str) return -1;
    // printf("last_str:%s\n", last_str);
    if (!strcmp(COMP_GCC_TOK, last_str)) return 0x01;
    if (!strcmp(COMP_MSVC_TOK, last_str)) return 0x02;
    if (!strcmp(COMP_JAVAC_TOK, last_str)) return 0x03;
    //
    return 0x00;
}

//


//
// "GCC" "MSVC" "JAVAC"
// odb:echo()|extend:convert(GCC); // fix me
// odb:echo()|extend:convert(MSVC); // fix me
// odb:echo()|extend:convert(JAVAC); // fix me
// 0x00:OK -1:error

int hand_conver(char **parae, shel_resu *resu, char *osdb) {
    int conv_valu = 0x00;
    //
    int comp_type = build_compi_type(parae);
    switch (comp_type) {
        case 0x00:
            conv_valu = -1;
            break;
        case 0x01:
            conv_valu = conve_gcc_cpp(parae, resu, osdb);
            break;
        case 0x02:
            printf("fix me: MSVC\n");
            conv_valu = -1;
            break;
        case 0x03:
            printf("fix me: JAVAC\n");
            conv_valu = -1;
            break;
        case -1:
        default:
            conv_valu = -1;
            break;
    }
    //
    return conv_valu;
}