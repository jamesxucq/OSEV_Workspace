
/* 
 * File:   pstyl_utili.h
 * Author: James Xu
 *
 * Created on 2018.3.16, PM 1:46
 */

#ifndef PSTYL_UTILI_H
#define PSTYL_UTILI_H

#include "paras_style.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    unsigned short encode_stri(char *pscon, char **paras);
    unsigned short encode_obje(char *pscon, char **paras, int obje_len);

    //
    char *parse_stri(char *data_line, char **paras, char *requ_data);
    char *parse_text(char *data_line, char **paras, char *requ_data);
    char *parse_uint32(char *data_line, char **paras, char *requ_data);
    char *parse_obje(char *data_line, char **paras, char *requ_data);

    //
    char *decode_string(char *data_line, char **paras, char *requ_data, int req_len);
    char *decode_general(char *data_line, char **paras, char *requ_data, int req_len);
    char *decode_object(char *data_line, char **paras, char *requ_data, int req_len);

    //
#define memcpy_o(dest, src, coun) { \
    dest[0x00] = '\a'; \
    ((unsigned short*) (dest + 0x01))[0x00] = coun; \
    memcpy(dest + 0x03, src, coun); \
}

#ifdef __cplusplus
}
#endif

#endif /* PSTYL_UTILI_H */

