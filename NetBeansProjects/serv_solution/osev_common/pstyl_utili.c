
#include "pstyl_utili.h"


//

unsigned short encode_stri(char *pscon, char **paras) {
    char *last_str = pscon;
    char **paras_tok = paras;
    //
    unsigned short len_valu = 0x00;
    for (; paras_tok[0x00]; paras_tok++)
        stri_pasty(last_str, len_valu, paras_tok[0x00])
        //
        return len_valu;
}

unsigned short encode_obje(char *pscon, char **paras, int obje_len) {
    char *last_str = pscon;
    char **paras_tok = paras;
    //
    unsigned short len_valu = 0x00;
    for (; paras_tok[0x00]; paras_tok++) {
        obje_pasty(last_str, len_valu, paras_tok[0x00], obje_len)
    }
    //
    return len_valu;
}

//

char *parse_stri(char *data_line, char **paras, char *requ_data) {
    char *last_str = data_line;
    char nval_cont[PARAM_LENGTH];
    char *parse_tok = pstyl_stri(nval_cont, requ_data);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    lscpy_o(paras[0x00], nval_cont, last_str);
    paras[0x01] = NULL;
    //
    return last_str;
}

char *parse_text(char *data_line, char **paras, char *requ_data) {
    char *last_str = data_line;
    char nval_cont[LARGE_TEXT_SIZE];
    char *parse_tok = pstyl_stri(nval_cont, requ_data);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    lscpy_o(paras[0x00], nval_cont, last_str);
    paras[0x01] = NULL;
    //
    return last_str;
}

#define UINT32_LEN  0x04

char *parse_uint32(char *data_line, char **paras, char *requ_data) {
    char *last_str = data_line;
    char nval_cont[UINT32_LEN];
    char *parse_tok = pstyl_uint((unsigned int *) nval_cont, requ_data);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    lmcpy_o(paras[0x00], nval_cont, UINT32_LEN, last_str);
    paras[0x01] = NULL;
    //
    return last_str;
}

char *parse_obje(char *data_line, char **paras, char *requ_data) {
    char *last_str = data_line;
    char nval_cont[OBJE_CONTE_LEN];
    unsigned short enlen;
    char *parse_tok = pstyl_obje(nval_cont, &enlen, requ_data);
    if (!parse_tok) {
        paras[0x00] = NULL;
        return NULL;
    }
    lmcpy_o(paras[0x00], nval_cont, enlen, last_str);
    paras[0x01] = NULL;
    //
    return last_str;
}

//

char *decode_string(char *data_line, char **paras, char *requ_data, int req_len) {
    char *last_str = data_line;
    char nval_cont[PARAM_LENGTH], *parse_tok = requ_data;
    int parse_len = 0x00;
    unsigned short enlen;
    int inde = 0x00;
    for (; req_len > parse_len; parse_len += enlen, inde++) {
        parse_tok = pstyl_stri_ex(nval_cont, &enlen, parse_tok);
        if (!parse_tok) {
            paras[inde] = NULL;
            return NULL;
        }
        lscpy_o(paras[inde], nval_cont, last_str);
        // printf("dstri:%s parse_len:%d enlen:%d req_len:%d\n", nval_cont, parse_len, enlen, req_len);
    }
    paras[inde] = NULL;
    //
    return last_str;
}

//

char *decode_general(char *data_line, char **paras, char *requ_data, int req_len) {
    char *last_str = data_line;
    char *parse_tok = requ_data;
    int parse_len = 0x00;
    unsigned short enlen;
    int inde = 0x00;
    for (; req_len > parse_len; parse_len += enlen, inde++) {
        switch (((uchar *) parse_tok)[0x00]) {
            case noty_byte:
            case noty_ubyte:
                // printf("decode_pstyle byte\n");
                lmcpy_o(paras[inde], &((byte_entry *) parse_tok)->data, sizeof (char), last_str);
                enlen = sizeof (byte_entry);
                break;
            case noty_short:
            case noty_ushort:
                lmcpy_o(paras[inde], &((short_entry *) parse_tok)->data, sizeof (short), last_str);
                // printf("decode_pstyle short\n");
                enlen = sizeof (short_entry);
                break;
            case noty_int:
            case noty_uint:
                // printf("decode_pstyle int\n");
                lmcpy_o(paras[inde], &((int_entry *) parse_tok)->data, sizeof (int), last_str);
                enlen = sizeof (int_entry);
                break;
            case noty_long:
            case noty_ulong:
                // printf("decode_pstyle long\n");
                lmcpy_o(paras[inde], &((long_entry *) parse_tok)->data, sizeof (long), last_str);
                enlen = sizeof (long_entry);
                break;
            case noty_stri:
                // printf("decode_pstyle stri\n");
                lszcpy_o(paras[inde], ((stri_entry *) parse_tok)->data, ((stri_entry *) parse_tok)->colen, last_str);
                enlen = sizeof (stri_entry) + ((stri_entry *) parse_tok)->colen;
                break;
            case noty_obje:
                // printf("decode_pstyle obje\n");
                lmcpy_o(paras[inde], ((obje_entry *) parse_tok)->data, ((obje_entry *) parse_tok)->colen, last_str);
                enlen = sizeof (obje_entry) + ((obje_entry *) parse_tok)->colen;
                break;
            default:
                // printf("decode_pstyle unknow\n");
                enlen = (unsigned short) - 1;
                break;
        }
        parse_tok += enlen;
        // printf("enlen:%u\n", enlen);
    }
    paras[inde] = NULL;
    //
    return last_str;
}

//

char *decode_object(char *data_line, char **paras, char *requ_data, int req_len) {
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
        lmcpy_o(paras[inde], para_cont, enlen, last_str);
        // printf("enlen:%u\n", enlen);
    }
    paras[inde] = NULL;
    //
    return last_str;
}

