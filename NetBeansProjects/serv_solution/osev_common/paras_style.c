#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include "paras_style.h"


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

static nodetyp check_nodetyp(char *stri) {
    nodetyp notyp = noty_inval;
    printf("check_nodetyp stri:|%s| ", stri);
    char *valu = stri;
    if (isdigit(valu[0x00])) {
        for (valu++; isdigit(valu[0x00]); valu++);
        if ('\0' != valu[0x00]) {
            switch (valu[0x00]) {
                case 'b':
                    notyp = noty_byte;
                    break;
                case 'B':
                    notyp = noty_ubyte;
                    break;
                case 'h':
                    notyp = noty_short;
                    break;
                case 'H':
                    notyp = noty_ushort;
                    break;
                case 'i':
                case 'l':
                    notyp = noty_int;
                    break;
                case 'I':
                case 'L':
                    notyp = noty_uint;
                    break;
                case 'q':
                    notyp = noty_long;
                    break;
                case 'Q':
                    notyp = noty_ulong;
                    break;
                default:
                    notyp = noty_stri;
                    break;
            }
        } else notyp = noty_int;
    } else if (isalpha(valu[0x00]) || '"' == valu[0x00]) notyp = noty_stri;
    else if ('\a' == valu[0x00]) notyp = noty_obje;
    else notyp = noty_inval;
    printf("notyp:%d\n", notyp);
    return notyp;
}

// unsigned 
#define byte_pasty(pscon, svalu) { \
    ((byte_entry *) pscon)->notyp = (uchar) noty_byte; \
    ((byte_entry *) pscon)->data = (char)atoi(svalu); \
    pscon += sizeof(byte_entry); \
}

#define ubyte_pasty(pscon, svalu) { \
    ((ubyte_entry *) pscon)->notyp = (uchar) noty_ubyte; \
    ((ubyte_entry *) pscon)->data = (unsigned char)atoi(svalu); \
    pscon += sizeof(ubyte_entry); \
}    

#define short_pasty(pscon, svalu) { \
    ((short_entry *) pscon)->notyp = (uchar) noty_short; \
    ((short_entry *) pscon)->data = (short)atoi(svalu); \
    pscon += sizeof(short_entry); \
}  

#define ushort_pasty(pscon, svalu) { \
    ((ushort_entry *) pscon)->notyp = (uchar) noty_ushort; \
    ((ushort_entry *) pscon)->data = (unsigned short)atoi(svalu); \
    pscon += sizeof(ushort_entry); \
}  

#define int_pasty(pscon, svalu) { \
    ((int_entry *) pscon)->notyp = (uchar) noty_int; \
    ((int_entry *) pscon)->data = (int)atoi(svalu); \
    printf("int_pasty:%d\n", ((int_entry *) pscon)->data); \
    pscon += sizeof (int_entry); \
}

#define uint_pasty(pscon, svalu) { \
    ((uint_entry *) pscon)->notyp = (uchar) noty_uint; \
    ((uint_entry *) pscon)->data = (unsigned int)atoi(svalu); \
    pscon += sizeof(uint_entry); \
}  

#define long_pasty(pscon, svalu) { \
    ((long_entry *) pscon)->notyp = (uchar) noty_long; \
    ((long_entry *) pscon)->data = (long)atoi(svalu); \
    pscon += sizeof(long_entry); \
}  

#define ulong_pasty(pscon, svalu) { \
    ((ulong_entry *) pscon)->notyp = (uchar) noty_ulong; \
    ((ulong_entry *) pscon)->data = (unsigned long)atoi(svalu); \
    pscon += sizeof(ulong_entry); \
}

//

unsigned short creat_obje_size(char *pscon) {
    if (noty_obje != ((obje_entry *) pscon)->notyp) return 0x00;
    return ((obje_entry *) pscon)->colen + sizeof (obje_entry);
}

//

unsigned short encode_dist(char *pscon, char **paras) {
    char *last_str = pscon;
    char **paras_tok = paras;
    //
    unsigned short olen;
    unsigned short len_valu = 0x00;
    for (; paras_tok[0x00]; paras_tok++) {
        nodetyp notyp = check_nodetyp(paras_tok[0x00]);
        switch (notyp) {
            case noty_byte:
                printf("noty_byte\n");
                byte_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (byte_entry);
                break;
            case noty_ubyte:
                printf("noty_ubyte\n");
                ubyte_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (ubyte_entry);
                break;
            case noty_short:
                printf("noty_short\n");
                short_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (short_entry);
                break;
            case noty_ushort:
                printf("noty_ushort\n");
                ushort_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (ushort_entry);
                break;
            case noty_int:
                printf("noty_int\n");
                int_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (int_entry);
                break;
            case noty_uint:
                printf("noty_uint\n");
                uint_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (uint_entry);
                break;
            case noty_long:
                printf("noty_long\n");
                long_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (long_entry);
                break;
            case noty_ulong:
                printf("noty_ulong\n");
                ulong_pasty(last_str, paras_tok[0x00])
                len_valu += sizeof (ulong_entry);
                break;
            case noty_stri:
                printf("noty_stri\n");
                stri_pasty(last_str, len_valu, paras_tok[0x00])
                break;
            case noty_obje:
                printf("noty_obje\n");
                olen = ((unsigned short*) (paras_tok[0x00] + 0x01))[0x00];
                obje_pasty(last_str, len_valu, (paras_tok[0x00] + 0x03), olen)
                break;
            case noty_inval:
            default:
                printf("noty_inval\n");
                len_valu = ((unsigned short) - 1);
                break;
        }
        printf("len_valu:%d\n", len_valu);
    }
    //
    return len_valu;
}

//

char *pstyl_char(char *nvalu, char *pscon) {
    if (noty_byte != ((byte_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((byte_entry *) pscon)->data;
    return pscon + sizeof (byte_entry);
}

char *pstyl_uchar(unsigned char *nvalu, char *pscon) {
    if (noty_ubyte != ((ubyte_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((ubyte_entry *) pscon)->data;
    return pscon + sizeof (ubyte_entry);
}

char *pstyl_short(short *nvalu, char *pscon) {
    if (noty_short != ((short_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((short_entry *) pscon)->data;
    return pscon + sizeof (short_entry);
}

char *pstyl_ushort(unsigned short *nvalu, char *pscon) {
    if (noty_ushort != ((ushort_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((ushort_entry *) pscon)->data;
    return pscon + sizeof (ushort_entry);
}

char *pstyl_int(int *nvalu, char *pscon) {
    if (noty_int != ((int_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((int_entry *) pscon)->data;
    return pscon + sizeof (int_entry);
}

char *pstyl_uint(unsigned int *nvalu, char *pscon) {
    if (noty_uint != ((uint_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((uint_entry *) pscon)->data;
    return pscon + sizeof (uint_entry);
}

char *pstyl_long(long *nvalu, char *pscon) {
    if (noty_long != ((long_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((long_entry *) pscon)->data;
    return pscon + sizeof (long_entry);
}

char *pstyl_ulong(unsigned long *nvalu, char *pscon) {
    if (noty_ulong != ((ulong_entry *) pscon)->notyp) return NULL;
    nvalu[0x00] = ((ulong_entry *) pscon)->data;
    return pscon + sizeof (ulong_entry);
}

char *pstyl_stri(char *nvalu, char *pscon) {
    if (noty_stri != ((stri_entry *) pscon)->notyp) return NULL;
    unsigned short colen = ((stri_entry *) pscon)->colen;
    memcpy(nvalu, ((stri_entry *) pscon)->data, colen);
    nvalu[colen] = '\0';
    return ((stri_entry *) pscon)->data + colen;
}

char *pstyl_obje(void *nvalu, unsigned short *colen, char *pscon) {
    if (noty_obje != ((obje_entry *) pscon)->notyp) return NULL;
    unsigned short clen = ((obje_entry *) pscon)->colen;
    memcpy(nvalu, ((obje_entry *) pscon)->data, clen);
    colen[0x00] = clen;
    return ((obje_entry *) pscon)->data + clen;
}
//

char *pstyl_stri_ex(char *nvalu, unsigned short *enlen, char *pscon) {
    if (noty_stri != ((stri_entry *) pscon)->notyp) return NULL;
    unsigned short colen = ((stri_entry *) pscon)->colen;
    memcpy(nvalu, ((stri_entry *) pscon)->data, colen);
    nvalu[colen] = '\0';
    enlen[0x00] = sizeof (stri_entry) + colen;
    return ((stri_entry *) pscon)->data + colen;
}

//

char *pstyl_obje_ex(void *nvalu, unsigned short *enlen, char *pscon) {
    if (noty_obje != ((obje_entry *) pscon)->notyp) return NULL;
    unsigned short colen = ((obje_entry *) pscon)->colen;
    memcpy(nvalu, pscon, sizeof (obje_entry) + colen);
    enlen[0x00] = sizeof (obje_entry) + colen;
    return ((obje_entry *) pscon)->data + colen;
}

//

char *decode_pstyle(unsigned short *enlen, char *pscon) {
    switch (((uchar *) pscon)[0x00]) {
        case noty_byte:
        case noty_ubyte:
            printf("decode_pstyle byte\n");
            enlen[0x00] = sizeof (byte_entry);
            break;
        case noty_short:
        case noty_ushort:
            printf("decode_pstyle short\n");
            enlen[0x00] = sizeof (short_entry);
            break;
        case noty_int:
        case noty_uint:
            printf("decode_pstyle int\n");
            enlen[0x00] = sizeof (int_entry);
            break;
        case noty_long:
        case noty_ulong:
            printf("decode_pstyle long\n");
            enlen[0x00] = sizeof (long_entry);
            break;
        case noty_stri:
            printf("decode_pstyle stri\n");
            enlen[0x00] = sizeof (stri_entry) + ((stri_entry *) pscon)->colen;
            break;
        case noty_obje:
            printf("decode_pstyle obje\n");
            enlen[0x00] = sizeof (obje_entry) + ((obje_entry *) pscon)->colen;
            break;
        default:
            printf("decode_pstyle unknow\n");
            enlen[0x00] = (unsigned short) - 1;
            break;
    }
    //
    return pscon + enlen[0x00];
}

//

char *byte_pstyl(char *pscon, char nvalu) {
    ((byte_entry *) pscon)->notyp = (uchar) noty_byte;
    ((byte_entry *) pscon)->data = nvalu;
    return pscon + sizeof (byte_entry);
}

char *ubyte_pstyl(char *pscon, unsigned char nvalu) {
    ((ubyte_entry *) pscon)->notyp = (uchar) noty_ubyte;
    ((ubyte_entry *) pscon)->data = nvalu;
    return pscon + sizeof (ubyte_entry);
}

char *short_pstyl(char *pscon, short nvalu) {
    ((short_entry *) pscon)->notyp = (uchar) noty_short;
    ((short_entry *) pscon)->data = nvalu;
    return pscon + sizeof (short_entry);
}

char *ushort_pstyl(char *pscon, unsigned short nvalu) {
    ((ushort_entry *) pscon)->notyp = (uchar) noty_ushort;
    ((ushort_entry *) pscon)->data = nvalu;
    return pscon + sizeof (ushort_entry);
}

char *int_pstyl(char *pscon, int nvalu) {
    ((int_entry *) pscon)->notyp = (uchar) noty_int;
    ((int_entry *) pscon)->data = nvalu;
    return pscon + sizeof (int_entry);
}

char *uint_pstyl(char *pscon, unsigned int nvalu) {
    ((uint_entry *) pscon)->notyp = (uchar) noty_uint;
    ((uint_entry *) pscon)->data = nvalu;
    return pscon + sizeof (uint_entry);
}

char *long_pstyl(char *pscon, long nvalu) {
    ((long_entry *) pscon)->notyp = (uchar) noty_long;
    ((long_entry *) pscon)->data = nvalu;
    return pscon + sizeof (long_entry);
}

char *ulong_pstyl(char *pscon, unsigned long nvalu) {
    ((ulong_entry *) pscon)->notyp = (uchar) noty_ulong;
    ((ulong_entry *) pscon)->data = nvalu;
    return pscon + sizeof (ulong_entry);
}

char *stri_pstyl(char *pscon, char *nvalu) {
    ((stri_entry *) pscon)->notyp = (uchar) noty_stri;
    unsigned short colen = (unsigned short) strlen(nvalu);
    ((stri_entry *) pscon)->colen = colen;
    memcpy(((obje_entry *) pscon)->data, nvalu, colen);
    return ((obje_entry *) pscon)->data + colen;
}

char *obje_pstyl(char *pscon, void *nvalu, unsigned short enlen) {
    memcpy(pscon, nvalu, enlen);
    return pscon + enlen;
}

char *stri_pstyl_ex(char *pscon, char *nvalu, unsigned short colen) {
    ((stri_entry *) pscon)->notyp = (uchar) noty_stri;
    ((stri_entry *) pscon)->colen = colen;
    memcpy(((obje_entry *) pscon)->data, nvalu, colen);
    return ((obje_entry *) pscon)->data + colen;
}

//

char *pobje_conte(int *colen, char *pscon) {
    if (noty_obje != ((obje_entry *) pscon)->notyp) return NULL;
    colen[0x00] = ((obje_entry *) pscon)->colen;
    return ((obje_entry *) pscon)->data;
}
