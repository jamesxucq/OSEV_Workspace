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

#pragma pack(1)

typedef struct {
    uchar notyp;
    char data;
} byte_entry;

typedef struct {
    uchar notyp;
    uchar data;
} ubyte_entry;

typedef struct {
    uchar notyp;
    short data;
} short_entry;

typedef struct {
    uchar notyp;
    ushort data;
} ushort_entry;

typedef struct {
    uchar notyp;
    int data;
} int_entry;

typedef struct {
    uchar notyp;
    uint data;
} uint_entry;

typedef struct {
    uchar notyp;
    long data;
} long_entry;

typedef struct {
    uchar notyp;
    ulong data;
} ulong_entry;

#pragma pack()

static nodetyp check_nodetyp(char *stri) {
    nodetyp notyp = noty_inval;
    //
    printf("check_nodetyp stri:|%s| ", stri);
    char *valu = stri;
    if (isdigit(valu[0x00])) {
        for (; isdigit(valu[0x00]); valu++);
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
                    notyp = noty_inval;
                    break;
            }
        } else notyp = noty_int;
    } else if (isalpha(valu[0x00]) || '"' == valu[0x00]) notyp = noty_stri;
    else if (noty_obje == valu[0x00]) notyp = noty_obje;
    else notyp = noty_inval;
    //
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
    pscon += sizeof(int_entry); \
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

#define stri_pasty(pscon, lenval, svalu) { \
    ((stri_entry *) pscon)->notyp = (uchar) noty_stri; \
    unsigned short colen = (unsigned short)strlen(svalu); \
    ((stri_entry *) pscon)->colen = colen; \
    memcpy(((stri_entry *) pscon)->data, svalu, colen); \
    pscon = ((stri_entry *) pscon)->data + colen; \
    lenval += (colen + sizeof(stri_entry)); \
}

#define obje_pasty(pscon, lenval, svalu, enlen) { \
    ((obje_entry *) pscon)->notyp = (uchar) noty_obje; \
    ((obje_entry *) pscon)->colen = (unsigned short)enlen; \
    memcpy(((obje_entry *) pscon)->data, svalu, enlen); \
    pscon = ((obje_entry *) pscon)->data + enlen; \
    lenval += (enlen + sizeof(stri_entry)); \
}

//

unsigned short creat_obje_size(char *pscon) {
    if (noty_obje != ((obje_entry *) pscon)->notyp) return 0x00;
    return ((obje_entry *) pscon)->colen + sizeof (obje_entry);
}

unsigned short encode_pstyle(char *pscon, char **paras) {
    char *last_str = pscon;
    char **paras_tok = paras;
    //
    int obje_size = 0x00;
    unsigned short lenValue = 0x00;
    for (; paras_tok[0x00]; paras_tok++) {
        nodetyp notyp = check_nodetyp(paras_tok[0x00]);
        switch (notyp) {
            case noty_byte:
                byte_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (char) + sizeof (uchar));
                break;
            case noty_ubyte:
                ubyte_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (unsigned char) + sizeof (uchar));
                break;
            case noty_short:
                short_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (short) + sizeof (uchar));
                break;
            case noty_ushort:
                ushort_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (unsigned short) + sizeof (uchar));
                break;
            case noty_int:
                int_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (int) + sizeof (uchar));
                break;
            case noty_uint:
                uint_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (unsigned int) + sizeof (uchar));
                break;
            case noty_long:
                long_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (long) + sizeof (uchar));
                break;
            case noty_ulong:
                ulong_pasty(last_str, paras_tok[0x00])
                lenValue += (sizeof (unsigned long) + sizeof (uchar));
                break;
            case noty_stri:
                stri_pasty(last_str, lenValue, paras_tok[0x00])
                break;
            case noty_obje:
                obje_size = creat_obje_size(paras_tok[0x00]);
                obje_pasty(last_str, lenValue, paras_tok[0x00], obje_size)
                break;
            case noty_inval:
            default:
                lenValue = ((unsigned short) - 1);
                break;
        }
    }
    //
    return lenValue;
}

//

unsigned short encode_stri(char *pscon, char **paras) {
    char *last_str = pscon;
    char **paras_tok = paras;
    //
    unsigned short lenValue = 0x00;
    for (; paras_tok[0x00]; paras_tok++) {
        stri_pasty(last_str, lenValue, paras_tok[0x00])
    }
        //
    return lenValue;
}

unsigned short encode_obje(char *pscon, char **paras, int obje_len) {
    char *last_str = pscon;
    char **paras_tok = paras;
    //
    unsigned short lenValue = 0x00;
    for (; paras_tok[0x00]; paras_tok++) {
        obje_pasty(last_str, lenValue, paras_tok[0x00], obje_len)
    }
    //
    return lenValue;
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
    *colen = clen;
    return ((obje_entry *) pscon)->data + clen;
}
//

char *pstyl_stri_ex(char *nvalu, unsigned short *enlen, char *pscon) {
    if (noty_stri != ((stri_entry *) pscon)->notyp) return NULL;
    unsigned short colen = ((stri_entry *) pscon)->colen;
    memcpy(nvalu, ((stri_entry *) pscon)->data, colen);
    nvalu[colen] = '\0';
    *enlen = sizeof (stri_entry) + colen;
    return ((stri_entry *) pscon)->data + colen;
}

//

char *pstyl_obje_ex(void *nvalu, unsigned short *enlen, char *pscon) {
    if (noty_obje != ((obje_entry *) pscon)->notyp) return NULL;
    unsigned short colen = ((obje_entry *) pscon)->colen;
    memcpy(nvalu, pscon, sizeof (obje_entry) + colen);
    *enlen = sizeof (obje_entry) + colen;
    return ((obje_entry *) pscon)->data + colen;
}

//

char *decode_pstyle(unsigned short *enlen, char *pscon) {
    unsigned short colen = 0x00;
    //
    switch (((uchar *) pscon)[0x00]) {
        case noty_byte:
        case noty_ubyte:
            *enlen = colen = sizeof (byte_entry);
            break;
        case noty_short:
        case noty_ushort:
            *enlen = colen = sizeof (short_entry);
            break;
        case noty_int:
        case noty_uint:
            *enlen = colen = sizeof (int_entry);
            break;
        case noty_long:
        case noty_ulong:
            *enlen = colen = sizeof (long_entry);
            break;
        case noty_stri:
            *enlen = colen = sizeof (stri_entry) + ((stri_entry *) pscon)->colen;
        case noty_obje:
            *enlen = colen = sizeof (obje_entry) + ((obje_entry *) pscon)->colen;
            break;
        default:
            *enlen = 0x00;
            break;
    }
    //
    return pscon + colen;
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
    *colen = ((obje_entry *) pscon)->colen;
    return ((obje_entry *) pscon)->data;
}

char *decode_obje(char *data_line, char **paras, char *requ_data, int req_len) {
    char *last_str = data_line;
    char *para_cont, *parse_tok = requ_data;
    int parse_len = 0x00;
    unsigned short enlen;
    int inde = 0x00;
    for (; req_len > parse_len; parse_len += enlen, inde++) {
        para_cont = parse_tok;
        parse_tok = decode_pstyle(&enlen, parse_tok);
        if (!parse_tok) {
            paras[inde] = NULL;
            return NULL;
        }
        lmcpy_s(paras[inde], para_cont, enlen, last_str);
        // printf("obje_creat:%s\n", para_cont);
    }
    paras[inde] = NULL;
    //
    return last_str;
}