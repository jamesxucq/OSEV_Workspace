
#include "commo_header.h"
#include "estr_utili.h"

//

char *build_const_handn(char *handn, char *clasn, char **paras) {
    char *last_str = lscpy(handn, clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, clasn);
    last_str = lccpy(last_str, '_');
    //
    char *valu;
    for (valu = paras[0x00]; NULL != valu; valu = (++paras)[0x00]) {
        printf("build_const_handn valu:|%d|\n", (int) valu[0x00]);
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

char *build_qcons_handn(char *handn, char *clasn, char *metnm, char **paras) {
    char *last_str = lscpy(handn, clasn);
    last_str = lccpy(last_str, '_');
    last_str = lscpy(last_str, metnm);
    last_str = lccpy(last_str, '_');
    //
    char *valu;
    for (valu = paras[0x00]; NULL != valu; valu = (++paras)[0x00]) {
        printf("build_qcons_handn valu:|%d|\n", (int)valu[0x00]);
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
