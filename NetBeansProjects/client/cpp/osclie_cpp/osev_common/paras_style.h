

/* 
 * File:   paras_style.h
 * Author: Administrator
 *
 * Created on 2017.5.18, PM2:29
 */

#ifndef PARAS_STYLE_H
#define PARAS_STYLE_H

#include "commo_macro.h"
#include "string_utility.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    typedef enum {
        noty_inval,
        noty_byte,
        noty_ubyte,
        noty_short,
        noty_ushort,
        noty_int,
        noty_uint,
        noty_long,
        noty_ulong,
        noty_stri,
        noty_obje
    } nodetyp;

    //
#pragma pack(1)

    typedef struct {
        uchar notyp;
        unsigned short colen; // content length
        char data[0x00];
    } stri_entry;
#pragma pack()

#pragma pack(1)

    typedef struct {
        uchar notyp;
        unsigned short colen; // content length
        char data[0x00];
    } obje_entry;
#pragma pack()

    //

    unsigned short encode_pstyle(char *pscon, char **paras);
    unsigned short encode_stri(char *pscon, char **paras);
    unsigned short encode_obje(char *pscon, char **paras, int obje_len);

    //
#define PSTY_CHAR_ELEN   sizeof(char) + sizeof(obje_entry)
    char *pstyl_char(char *nvalu, char *pscon);
    char *pstyl_uchar(unsigned char *nvalu, char *pscon);
#define PSTY_SHORT_ELEN   sizeof(short) + sizeof(obje_entry)
    char *pstyl_short(short *nvalu, char *pscon);
    char *pstyl_ushort(unsigned short *nvalu, char *pscon);
#define PSTY_INT_ELEN   sizeof(int) + sizeof(obje_entry)
    char *pstyl_int(int *nvalu, char *pscon);
    char *pstyl_uint(unsigned int *nvalu, char *pscon);
#define PSTY_LONG_ELEN   sizeof(long) + sizeof(obje_entry)
    char *pstyl_long(long *nvalu, char *pscon);
    char *pstyl_ulong(unsigned long *nvalu, char *pscon);
#define PSTY_CHAR_ELEN   sizeof(char) + sizeof(obje_entry)
    char *pstyl_stri(char *nvalu, char *pscon);
    char *pstyl_obje(void *nvalu, unsigned short *colen, char *pscon);

    //
    char *pstyl_stri_ex(char *nvalu, unsigned short *enlen, char *pscon);
    char *pstyl_obje_ex(void *nvalu, unsigned short *enlen, char *pscon);
    char *decode_pstyle(unsigned short *enlen, char *pscon);

    //

    char *byte_pstyl(char *pscon, char nvalu);
    char *ubyte_pstyl(char *pscon, unsigned char nvalu);
    char *short_pstyl(char *pscon, short nvalu);
    char *ushort_pstyl(char *pscon, unsigned short nvalu);
    char *int_pstyl(char *pscon, int nvalu);
    char *uint_pstyl(char *pscon, unsigned int nvalu);
    char *long_pstyl(char *pscon, long nvalu);
    char *ulong_pstyl(char *pscon, unsigned long nvalu);
    char *stri_pstyl(char *pscon, char *nvalu);
    char *obje_pstyl(char *pscon, void *nvalu, unsigned short enlen);

    //
    char *pobje_conte(int *colen, char *pscon);
    char *decode_obje(char *data_line, char **paras, char *requ_data, int req_len);
    char *stri_pstyl_ex(char *pscon, char *nvalu, unsigned short colen);

#ifdef __cplusplus
}
#endif

#endif /* PARAS_STYLE_H */

