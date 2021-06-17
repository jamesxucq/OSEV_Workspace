#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "epcla.h"

//

static char *metho_decla(char *nspac, char *clas_data) {
    char *tokep, *toksp;
    //
    toksp = strchr(clas_data, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(nspac, clas_data, toksp - clas_data);
    //
    tokep = strchr(tokep + 0x01, ';');
    if (!tokep) return NULL;
    return tokep + 0x01;
}

static int check_nspac(char *metnm[METH_NUMB], int posi, char *nspac) {
    int inde = 0x00;
    for (; posi > inde; inde++) {
        if (!strcmp(nspac, metnm[inde])) return 0x01;
    }
    //
    return 0x00;
}

int parse_method(char *meth_line, char *metnm[METH_NUMB], char *clas_data) {
    char *tokep, *toksp;
    char nspac[METH_LENGTH];
// printf("pm clas_data:%s\n", clas_data);
    char *last_str = meth_line;
    int inde = 0x00;
    if (!(toksp = kill_inval(clas_data))) return -1;
    tokep = metho_decla(nspac, toksp);
    while (tokep) {
        if (!check_nspac(metnm, inde, nspac)) {
            lscpy_o(metnm[inde], nspac, last_str);
// printf("metnm[%d]:%s\n", inde, metnm[inde]);
            inde++;
        }
        if (!(toksp = kill_inval(tokep))) return -1;
        tokep = metho_decla(nspac, toksp);
    }
    metnm[inde] = NULL;
// printf("metnm[%d]:%s\n", inde, metnm[inde]);
    return 0x00;
}