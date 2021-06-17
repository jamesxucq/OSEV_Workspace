#include <stdio.h>

#include "stri_utili.h"
#include "parse_command.h"
#include "defau_utili.h"

//

int defva_stat_echo(char **paras, char *obje_iden, char *sline) {
    if (strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        if (paras[0x00]) return -1;
        else {
            paras[0x00] = sline;
            char *last_str = lccpy(sline, '\"');
            last_str = lscpy(last_str, obje_iden);
            lccpy(last_str, '\"');
            paras[0x01] = NULL;
        }
    }
    //
    return 0x00;
}

void defva_stat_statu(char **paras, char *sline) {
    if (!paras[0x00]) {
        char *last_str = sline;
        lscpy_o(paras[0x00], "AUTH", last_str);
        lscpy_o(paras[0x01], "STAT", last_str);
        paras[0x02] = NULL;
    }
}

void defva_stat_stati(char **paras, char *sline) {
    if (!paras[0x00]) {
        paras[0x00] = sline;
        lscpy(sline, "ODB");
        paras[0x01] = NULL;
    }
}

//
#define OPEN_DEFAULT_VALUE "12p34p"

int defva_stat_open(char **paras, char *obje_iden, char *sline) {
    if (strcmp(OSEV_DEFAULT_VALUE, obje_iden)) {
        if (!paras[0x00]) {
            paras[0x00] = sline;
            strcpy(sline, OPEN_DEFAULT_VALUE);
            paras[0x01] = NULL;
        }
        if (paras[0x01]) return -1;
    } else {
        if (!paras[0x00]) return -1;
        quote_decode(paras[0x00]);
        if (!strcmp(OSEV_DEFAULT_VALUE, paras[0x00]) || !strcmp(OSDB_DEFAULT_VALUE, paras[0x00]))
            return -1;
        if (!paras[0x01]) {
            expand_tail(paras + 0x01, paras[0x00]);
            strcpy(paras[0x01], OPEN_DEFAULT_VALUE);
        }
    }
    //
    return 0x00;
}


//

#define GRANT_DEFAULT_VALUE "GRANT"
#define REVOKE_DEFAULT_VALUE "REVOKE"

void defva_priv_role(char **paras, char *obje_iden) {
    if (!strcmp(GRANT_DEFAULT_VALUE, paras[0x00]) || !strcmp(REVOKE_DEFAULT_VALUE, paras[0x00])) {
        if (!paras[0x03]) {
            expand_tail(paras + 0x03, paras[0x02]);
            strcpy(paras[0x03], obje_iden);
            char *third = strchr(paras[0x03], ':');
            if (third) third[0x00] = '\0';
            //
            third = paras[0x02];
            paras[0x02] = paras[0x03];
            paras[0x03] = third;
        }
    }
}