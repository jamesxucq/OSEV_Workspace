#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>

#include "string_utility.h"

//
char *strzcpy(char *dest, const char *source, size_t count) {
    char *start = dest;
    while (count && (*dest++ = *source++)) count--; /* copy string */
    if (count) /* pad out with zeroes */
        while (--count) *dest++ = '\0';
    else *dest = '\0';
    return (start);
}

//
char *lscpy(char * dest, const char * src) {
    if (!dest) return NULL;
    register char *d = dest;
    register const char *s = src;
    while ((*d = *s++)) d++;
    return d;
}

char *lccpy(char * dest, const char src) {
    if (!dest) return NULL;
    dest[0x00] = src;
    (++dest)[0x00] = '\0';
    return dest;
}

//
char *kill_blank(char *stri) {
    char *toke;
    for (toke = stri; '\0' != toke[0x00]; ++toke) {
        if (' ' != toke[0x00]) return toke;
    }
    return NULL;
}

//

char *quote_decode(char *quostr) {
    char *toksp, *tokdp;
    if (!quostr) return NULL;
    //
    toksp = quostr;
    for (; '\0' != toksp[0x00]; toksp++) {
        if ('\\' == toksp[0x00]) toksp++;
        else if ('"' == toksp[0x00]) {
            tokdp = toksp;
            toksp++;
            while ('\0' != toksp[0x00]) {
                if ('\\' == toksp[0x00]) {
                    tokdp[0x00] = toksp[0x00];
                    toksp++;
                    tokdp++;
                } else if ('"' == toksp[0x00]) break;
                //
                tokdp[0x00] = toksp[0x00];
                toksp++;
                tokdp++;
            }
            tokdp[0x00] = '\0';
            break;
        }
    }
    //
    return quostr;
}
