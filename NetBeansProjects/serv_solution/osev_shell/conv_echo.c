#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "parse_command.h"
#include "conv_echo.h"
#include "clie_obje.h"

//
#define LEVE_OBJE_TOK "odb"
#define OBJE_CREAT_TOK "create"

// test:test(33); tvtv:create(33);

char *echo_creat_eobje_exte(char *obje_iden, char *comd_meth, char *line_stri) {
    char paras_str[LARGE_TEXT_SIZE];
    if (!analy_const_eobje_exte(paras_str, line_stri)) return NULL;
    //
     printf("echo_creat_eobje_exte, FIX ME!\n");
    char *last_str = lscpy(line_stri, _leve_defa_obje_.obje_iden);
    last_str = lccpy(last_str, ':');
    char *echo_tok = last_str = lscpy(last_str, OBJE_CREAT_TOK);
    printf("echo_creat_eobje, line_stri:|%s|\n", line_stri);
    last_str = lccpy(last_str, '(');
    last_str = lscpy(last_str, paras_str);
    last_str = lscpy(last_str, ");");
    //
    lscpy(obje_iden, _leve_defa_obje_.obje_iden);
    lscpy(comd_meth, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

// test:test(33) > tvtv; => tvtv:create(33);

char *echo_creat_eobje_redi(char *obje_iden, char *comd_meth, char *line_stri) {
    char redi_obje[OBJE_LENGTH];
    char paras_str[LARGE_TEXT_SIZE];
    if (!analy_const_eobje_redi(redi_obje, paras_str, line_stri)) return NULL;
    //
    char *last_str = lscpy(line_stri, redi_obje);
    last_str = lccpy(last_str, ':');
    char *echo_tok = last_str = lscpy(last_str, OBJE_CREAT_TOK);
    printf("echo_creat_eobje, line_stri:|%s|\n", line_stri);
    last_str = lccpy(last_str, '(');
    last_str = lscpy(last_str, paras_str);
    last_str = lscpy(last_str, ");");
    //
    lscpy(obje_iden, redi_obje);
    lscpy(comd_meth, OBJE_CREAT_TOK);
    //
    return echo_tok;
}


// rive:rive("tvtv", "test") > odb; => odb:create("tvtv", "rive", "test");

char *echo_creat_cobje(char *obje_iden, char *comd_meth, char *line_stri) {
    char redi_obje[OBJE_LENGTH];
    char paras_str[LARGE_TEXT_SIZE];
    printf("line_stri:|%s| obje_iden:|%s|\n", line_stri, obje_iden);
    if (!analy_const_cobje(redi_obje, paras_str, line_stri, obje_iden)) return NULL;
    //
    printf("echo_creat_cobje, redi_obje:|%s| paras_str:|%s|\n", redi_obje, paras_str);
    char *last_str = lscpy(line_stri, redi_obje);
    last_str = lccpy(last_str, ':');
    char *echo_tok = last_str = lscpy(last_str, OBJE_CREAT_TOK);
    // printf("const_str:|%s|\n", const_str);
    last_str = lccpy(last_str, '(');
    last_str = lscpy(last_str, paras_str);
    last_str = lscpy(last_str, ");");
    //
    lscpy(obje_iden, redi_obje);
    lscpy(comd_meth, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

//
// ;ttt; => odb:create("xxx; ttt;");

char *echo_creat_metho_exte(char *obje_iden, char *comd_meth, char *line_stri) {
    char line_txt[LARGE_TEXT_SIZE];
    strcpy(line_txt, line_stri);
    char *last_str = lscpy(line_stri, LEVE_OBJE_TOK);
    last_str = lccpy(last_str, ':');
    char *echo_tok = last_str = lscpy(last_str, OBJE_CREAT_TOK);
    printf("echo_creat_metho, line_stri:|%s|\n", line_stri);
    last_str = lscpy(last_str, "(\"");
    last_str = lscpy(last_str, obje_iden);
    last_str = lscpy(last_str, line_txt);
    last_str = lscpy(last_str, "\");");
    //
    lscpy(obje_iden, LEVE_OBJE_TOK);
    lscpy(comd_meth, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

// xxx; ttt; => odb:create("xxx; ttt;");

char *echo_creat_metho(char *obje_iden, char *comd_meth, char *line_stri) {
    char line_txt[LARGE_TEXT_SIZE];
    strcpy(line_txt, line_stri);
    char *last_str = lscpy(line_stri, LEVE_OBJE_TOK);
    last_str = lccpy(last_str, ':');
    char *echo_tok = last_str = lscpy(last_str, OBJE_CREAT_TOK);
    printf("echo_creat_metho, line_stri:|%s|\n", line_stri);
    last_str = lscpy(last_str, "(\"");
    last_str = lscpy(last_str, line_txt);
    last_str = lscpy(last_str, "\");");
    //
    lscpy(obje_iden, LEVE_OBJE_TOK);
    lscpy(comd_meth, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

// xxx; ttt; => odb:create("xxx; ttt;");

char *echo_creat_class(char *obje_iden, char *comd_meth, char *line_stri) {
    char line_txt[LARGE_TEXT_SIZE];
    strcpy(line_txt, line_stri);
    char *last_str = lscpy(line_stri, LEVE_OBJE_TOK);
    last_str = lccpy(last_str, ':');
    char *echo_tok = last_str = lscpy(last_str, OBJE_CREAT_TOK);
    printf("echo_creat_metho, line_stri:|%s|\n", line_stri);
    last_str = lscpy(last_str, "(\"");
    last_str = lscpy(last_str, line_txt);
    last_str = lscpy(last_str, "\");");
    //
    lscpy(obje_iden, LEVE_OBJE_TOK);
    lscpy(comd_meth, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

//
