

/* 
 * File:   paras_style.h
 * Author: James Xu
 *
 * Created on 2017.5.18, PM2:29
 */

#ifndef PARAS_STYLE_H
#define PARAS_STYLE_H

#include "commo_macro.h"
#include "stri_utili.h"

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
        unsigned short data;
    } ushort_entry;

    typedef struct {
        uchar notyp;
        int data;
    } int_entry;

    typedef struct {
        uchar notyp;
        unsigned int data;
    } uint_entry;

    typedef struct {
        uchar notyp;
        long data;
    } long_entry;

    typedef struct {
        uchar notyp;
        unsigned long data;
    } ulong_entry;

    typedef struct {
        uchar notyp;
        unsigned short colen; // content length
        char data[0x00];
    } stri_entry;

    typedef struct {
        uchar notyp;
        unsigned short colen; // content length
        char data[0x00];
    } obje_entry;

#pragma pack()

    //
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

    unsigned short encode_dist(char *pscon, char **paras);

    //
#define PSTY_CHAR_ELEN   sizeof(byte_entry)
    char *pstyl_char(char *nvalu, char *pscon);
    char *pstyl_uchar(unsigned char *nvalu, char *pscon);
#define PSTY_SHORT_ELEN   sizeof(short_entry)
    char *pstyl_short(short *nvalu, char *pscon);
    char *pstyl_ushort(unsigned short *nvalu, char *pscon);
#define PSTY_INT_ELEN   sizeof(int_entry)
    char *pstyl_int(int *nvalu, char *pscon);
    char *pstyl_uint(unsigned int *nvalu, char *pscon);
#define PSTY_LONG_ELEN   sizeof(long_entry)
    char *pstyl_long(long *nvalu, char *pscon);
    char *pstyl_ulong(unsigned long *nvalu, char *pscon);
#define PSTY_STRI_ELEN(pscon)   sizeof(stri_entry) + ((stri_entry *) pscon)->colen
    char *pstyl_stri(char *nvalu, char *pscon);
#define PSTY_OBJE_ELEN(pscon)   sizeof(obje_entry) + ((obje_entry *) pscon)->colen
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
    char *stri_pstyl_ex(char *pscon, char *nvalu, unsigned short colen);

#ifdef __cplusplus
}
#endif

#endif /* PARAS_STYLE_H */

