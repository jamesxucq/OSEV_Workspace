/* 
 * File:   sha_common.h
 * Author: James Xu
 */

#ifndef SHA_COMMON_H
#define SHA_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef int32
#define int32 int
#endif

#ifndef uint32
#define uint32 unsigned int
#endif

#ifndef uint64
#define uint64 unsigned long long
#endif

#ifndef uchar
#define uchar unsigned char
#endif

//
#define INVA_INDE_VALU ((unsigned int)-1)

    //

#define FILE_EXIST(PATH_NAME) access(PATH_NAME, F_OK)

    //


#ifdef __cplusplus
}
#endif

#endif /* SHA_COMMON_H */

