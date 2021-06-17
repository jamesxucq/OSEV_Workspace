
/* 
 * File:   osev_macro.h
 * Author: Administrator
 *
 * Created on 2018.3.29, AM 9:08
 */

#ifndef OSEV_MACRO_H
#define OSEV_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

//
#ifndef EVD_SOCKET_BUFF
#define EVD_SOCKET_BUFF                 0x2000  // 8K
#endif

    //
#define XML_LENGTH                    0x2000  // 8K
#define ATTRIB_LENGTH                 512
#define ELEMEN_LENGTH                 512
    //
#define ADVAN_OBJE_SIZE               0x4000  // 16K
#define RSBUF_LENGTH                  0x2000  // 8K
#define LARGE_TEXT_SIZE               0x2000  // 8K
#define TEXT_LENGTH                   2048
#define LINE_LENGTH                   1024

    //
#define MAX_TEXT_LEN  512
#define MID_TEXT_LEN  128
#define MIN_TEXT_LEN  64


#define TIME_LENGTH             32
#define PASWD_LENGTH            32
#define SALT_LENGTH             16
#define KEY_LENGTH              16
#define USERN_LENGTH            32
#define VALID_TEXT_LENGTH       33
#define PLAIN_VALID_LENGTH      USERN_LENGTH + PASWD_LENGTH + 0x01

#define _USERN_LENGTH_          128
#define GROUPN_LENGTH           128
#define SERVN_LENGTH            256
#define TIME_LENGTH             32

    //
#define METH_NAME_LEN           128
#define PACKAGE_LEN             128

    //
#define OSEV_LENGTH             128
#define OSDB_LENGTH             OSEV_LENGTH
#define ACTION_KEY_LENGTH       USERN_LENGTH + OSDB_LENGTH
#define CLASS_LENGTH            128
#define OBJE_LENGTH             128
#define METH_NUMB               128
#define METH_LENGTH             128
#define TYPE_LENGTH             32
#define PARAM_NUMB              32
#define PARAM_LENGTH            128
#define PSTYL_LENGTH            1024
#define PARA_TYPE_LEN           64
#define MAX_OSDB_NUMB           128
#define CDATNO_NUMB             1024
#define CNODE_LENGTH            1024

    //
#define CONTA_LENGTH           128
#define TABLE_LENGTH           128
#define TYPES_LENGTH           1024
#define COLUMN_LENGTH          0x1000  // 4K
#define HAND_LENGTH            256

    //
#define CONF_LENGTH            2048
#define SPACE_NUMB             32
#define OBJE_CONTE_LEN         0x1000  // 4K


    //

#define OSEV_DEFAULT_VALUE  "osev"
#define OSDB_DEFAULT_VALUE  "odb"
#define OSEV_ADMIN_VALUE    "admin"

    //
#define SOUR_COTE         64
    
#ifdef __cplusplus
}
#endif

#endif /* OSEV_MACRO_H */

