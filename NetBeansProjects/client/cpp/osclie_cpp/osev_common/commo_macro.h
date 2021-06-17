
/* 
 * File:   commo_macro.h
 * Author: Administrator
 *
 * Created on 2017.9.5
 */

#ifndef COMMO_MACRO_H
#define COMMO_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define MKZERO(TEXT) TEXT[0x00] = '\0'    
    
    //   
#ifndef uchar
#define uchar unsigned char
#endif
    
#ifndef uint32
#define uint32 unsigned int
#endif

#ifndef uint64
#define uint64 unsigned long long
#endif

    //
#define TEXT_LENGTH                   2048
    
    //
#define MAX_TEXT_LEN		512
#define MID_TEXT_LEN		128
#define MIN_TEXT_LEN		64
    
//

#define REQU_DATA_SIZE                0x2000  // 8K
#define RESP_DATA_SIZE                0x2000  // 8K
    
//
    
#define SERVN_LENGTH            256
#define OSEV_LENGTH             128

//
#define CONNE_DATA_LEN                  0x2000  // 8K
#define LARGE_TEXT_SIZE               0x2000  // 8K

//
#define USERN_LENGTH            32
#define PASSWORD_LENGTH         32

    //
#define SPACE_NUMB             32
#define OBJE_LENGTH             128
#define METH_LENGTH             128
#define PARAM_NUMB              32
#define PARAM_LENGTH            128
    
#define OBJE_LENGTH             128
#define OBJE_CONTE_LEN         0x1000  // 4K
    
    //
    
#ifdef __cplusplus
}
#endif

#endif /* COMMO_MACRO_H */

