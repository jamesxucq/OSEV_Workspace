
#ifndef COMMO_MACRO_H
#define COMMO_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

    //
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef OFF_T
#define OFF_T off_t
#endif

    //
    typedef unsigned char BYTE;

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef int32
#define int32 int
#endif

#ifndef int64
#define int64 long long
#endif

#ifndef uint16
#define uint16 unsigned short
#endif

#ifndef uint32
#define uint32 unsigned int
#endif

#ifndef uint64
#define uint64 unsigned long long
#endif

    //
#define POW2N_MOD(nua, nub)  (nua & (nub - 0x01)) // x=2^n a=b%x-->a=b&(x-1)

#define FCLOSE_SAFETY(fptr) if(fptr) fclose(fptr);
#define DELETE_SAFETY(mptr) if(mptr) free(mptr);

#define MKZERO(TEXT) TEXT[0x00] = '\0'
#define MKNONE(PONI) PONI = NULL

#define s_strlen(str) (sizeof(str) - 0x01)

    //
#ifndef CALLBACK
#define CALLBACK
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef LDECLTYPE
#define LDECLTYPE(x) __typeof(x)
#endif

    //
#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef MAX_HOST_LEN
#define MAX_HOST_LEN 256
#endif

#ifndef PATH_LEN
#define PATH_LEN 128
#endif

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN 1024
#endif

    //
#define INVA_POIN_VALU ((void *) - 1)
#define INVA_UINT_VALU ((unsigned int)-1)
#define INVA_ULONG_VALU ((unsigned long long)-1)

    //

#ifdef __cplusplus
}
#endif

#endif /* COMMO_MACRO_H */

