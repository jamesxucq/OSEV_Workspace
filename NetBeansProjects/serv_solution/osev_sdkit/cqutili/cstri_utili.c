#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "commo_header.h"
#include "cstri_utili.h"

//

char *qeach_paras(char *each_line, char **paras, char *para_str) {
    char *last_str = each_line;
    char *tokep, *toksp = strpar(para_str);
    //
    printf("para_str:%s\n", para_str);
    int inde;
    for (inde = 0x00; toksp; inde++) {
        tokep = strpbrk(toksp + 0x01, " ,");
        if (tokep) {
            lszcpy_o(paras[inde], toksp, tokep - toksp, last_str)
            toksp = strpar(tokep + 0x01);
            printf("paras[%d]:%s\n", inde, paras[inde]);
        } else {
            lscpy_o(paras[inde], toksp, last_str)
            toksp = NULL;
            printf("paras[%d]:%s\n", inde, paras[inde]);
        }
    }
    paras[inde] = NULL;
    //
    return each_line;
}

//

char *split_qeach(char *obje_ide, char *meth_str, char *para_str, char *meth_line) {
    char *toksp = kill_blank(meth_line);
    if (!toksp) return NULL;
    char *toknp = strchr(toksp, ':');
    if (!toknp) return NULL;
    char *tokep = strpbrk(toknp, " (");
    if (!tokep) return NULL;
    //
    strzcpy(obje_ide, toksp, toknp - toksp);
    toknp++;
    strzcpy(meth_str, toknp, tokep - toknp);
    MKZERO(para_str);
    if ('(' != tokep[0x00]) {
        tokep = strchr(tokep, '(');
        if (!tokep) return NULL;
    }
    tokep++;
    toksp = qstrch(tokep, ')');
    if (!toksp) return NULL;
    strzcpy(para_str, tokep, toksp - tokep);
    //
    return obje_ide;
}

//

/*
static char *lastp_point(char **paras) {
    char *last_str = NULL;
    for (; paras[0x00]; paras++)
        last_str = paras[0x00];
    //
    return last_str;
}
 */

//
//
//
/*
Format    C Type    Java type    Python type    Notes
x         N/A       N/A          N/A            pad byte, no associated value
b         int8_t    byte         int            signed byte
B         uint8_t   byte         int            unsigned byte
h         int16_t   short        int            signed 16-bit
H         uint16_t  short        int            unsigned 16-bit
i         int32_t   int          int            signed 32-bit
I         uint32_t  int          int            unsigned 32-bit
l         int32_t   int          int            signed 32-bit
L         uint32_t  int          int            unsigned 32-bit
q         int64_t   long         int            signed 64-bit
Q         uint64_t  long         int            unsigned 64-bit
r         uint64_t  long         int            record number
s         char[]    String       str            fixed-length string
S         char[]    String       str            NUL-terminated string
t         uint8_t   byte         int            fixed-length bit field
u         WT_ITEM * byte[]       str            raw byte array
 */

/*
 char *vari_type_tab[] = {
    "int",
    "short",
    "long",
    "char",
    "float",
    "double",
    NULL
};
 */

//

char *build_query_handn(char *handn, char *clasn, char *metnm, char **paras) {
    char *last_str = lscpy(handn, clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metnm);
    last_str = lccpy(last_str, '_');
    //
    char *valu;
    for (valu = paras[0x00]; NULL != valu; valu = (++paras)[0x00]) {
        printf("build_query_handn valu:|%d|\n", (int) valu[0x00]);
        switch (valu[0x00]) {
            case noty_byte:
                last_str = lccpy(last_str, 'b');
                break;
            case noty_ubyte:
                last_str = lccpy(last_str, 'B');
                break;
            case noty_short:
                last_str = lccpy(last_str, 'h');
                break;
            case noty_ushort:
                last_str = lccpy(last_str, 'H');
                break;
            case noty_int:
                last_str = lccpy(last_str, 'i');
                break;
            case noty_uint:
                last_str = lccpy(last_str, 'I');
                break;
            case noty_long:
                last_str = lccpy(last_str, 'q');
                break;
            case noty_ulong:
                last_str = lccpy(last_str, 'Q');
                break;
            case noty_stri:
                last_str = lccpy(last_str, 's');
                break;
            case noty_obje:
                last_str = lccpy(last_str, 'o');
                break;
            case noty_inval:
            default:
                return NULL;
                break;
        }
    }
    //
    return handn;
}

//

char *crea_proj_uri(char *prou, char *contn, char *data) {
    char *last_str = lscpy(prou, "table:");
    last_str = lscpy(last_str, contn);
    last_str = lccpy(last_str, '(');
    last_str = lscpy(last_str, data);
    last_str = lccpy(last_str, ')');
    //
    return prou;
}


//


