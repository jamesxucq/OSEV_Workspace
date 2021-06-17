#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>

#include "utility/strptime.h"
#include "stri_utili.h"

//

char *escpy(char * dest, const char * src) {
    if (!dest) return NULL;
    register char *d = dest;
    register char *s = (char *) src;
    while ((*d++ = *s)) s++;
    return s;
}

//

char *lsprif(char *dest, const char *format, ...) {
    va_list arg;
    int done;
    //
    if (!dest) return NULL;
    va_start(arg, format);
    done = vsprintf(dest, format, arg);
    va_end(arg);
    if (0x00 > done) return NULL;
    //
    return dest + done;
}

char *lscpy(char * dest, const char * src) {
    if (!dest) return NULL;
    register char *d = dest;
    register const char *s = src;
    while ((*d = *s++)) d++;
    return d;
}

char *lsncpy(char *dest, const char *src, size_t n) {
    char c;
    //
    if (!dest) return NULL;
    if (n >= 4) {
        size_t n4 = n >> 2;
        for (;;) {
            c = *src++;
            *dest = c;
            if (c == '\0') break;
            dest++;
            c = *src++;
            *dest = c;
            if (c == '\0') break;
            dest++;
            c = *src++;
            *dest = c;
            if (c == '\0') break;
            dest++;
            c = *src++;
            *dest = c;
            if (c == '\0') break;
            dest++;
            if (--n4 == 0) goto last_chars;
        }
        return dest;
    }
last_chars:
    n &= 3;
    if (n == 0) {
        *dest = '\0';
        return dest;
    }
    for (;;) {
        c = *src++;
        *dest = c;
        if (c == '\0') break;
        dest++;
        if (--n == 0) {
            *dest = '\0';
            return dest;
        }
    }
    //
    return dest;
}

char *lszcpy(char *dest, const char *source, size_t count) {
    while (count && (*dest++ = *source++)) count--; /* copy string */
    dest[0x00] = '\0';
    return (dest);
}

char *lscat(char * dest, const char * src) {
    if (!dest) return NULL;
    return lscpy(dest + strlen(dest), src);
}

char *lccpy(char * dest, const char src) {
    if (!dest) return NULL;
    dest[0x00] = src;
    (++dest)[0x00] = '\0';
    return dest;
}

char *lccat(char * dest, const char src) {
    if (!dest) return NULL;
    dest += strlen(dest);
    dest[0x00] = src;
    (++dest)[0x00] = '\0';
    return dest;
}

char *lsncat(char *dest, const char *src, size_t n) {
    if (!dest) return NULL;
    char *destptr = dest + strlen(dest);
    for (; n > 0 && (*destptr = *src) != '\0'; src++, destptr++, n--);
    if (n == 0) *destptr = '\0';
    return destptr;
}

//

char *strsplit(char *str, const char *delim) {
    char *toksp;
    static char *tokep;
    //
    if (!str) {
        if (!tokep) return NULL;
        toksp = tokep + strlen(delim);
    } else toksp = str;
    //
    tokep = strstr(toksp, delim);
    if (tokep) *tokep = '\0';
    //
    return toksp;
}

inline char *utc_time_text(time_t utctime) { // Wed, 15 Nov 1995 04:58:08 GMT
    static char timestr[TIME_LENGTH];
    struct tm *utctm;
    //
    if (!utctime) utctime = time(NULL);
    utctm = gmtime(&utctime);
    if (!strftime(timestr, TIME_LENGTH, "%a, %d %b %Y %H:%M:%S %Z", utctm)) return NULL;
    //
    return timestr;
}

inline time_t utc_time_value(char *timestr) { // Wed, 15 Nov 1995 04:58:08 GMT
    struct tm utctm;
    //
    if (!timestr) return 0;
    memset(&utctm, '\0', sizeof (struct tm));
    _strptime(&utctm, timestr);
    time_t calender = _mktime(&utctm);
    //
    return calender;
}

char *random_seion_id() {
    static char rand_str[MIN_TEXT_LEN];
    static unsigned int tatol;
    snprintf(rand_str, MIN_TEXT_LEN, "%d-%u-%d", getpid(), (uint32) time(NULL), ++tatol);
    return rand_str;
}

char *random_valid() {
    static char rand_str[MIN_TEXT_LEN];
    static long int last_seed;
    char code_array[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    //
    if (!last_seed) last_seed = time(NULL);
    int tatol;
    for (tatol = 0; tatol < 20; tatol++) {
        srandom((unsigned int) last_seed);
        last_seed = random();
        rand_str[tatol] = code_array[last_seed % 62];
    }
    rand_str[tatol] = '\0';
    //
    return rand_str;
}

char *random_accesskey() {
    static char rand_str[MIN_TEXT_LEN];
    static long int last_seed;
    char code_array[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    //
    if (!last_seed) last_seed = time(NULL);
    int tatol;
    for (tatol = 0; tatol < 20; tatol++) {
        srandom((unsigned int) last_seed);
        last_seed = random();
        rand_str[tatol] = code_array[last_seed % 62];
    }
    rand_str[tatol] = '\0';
    //
    return rand_str;
}

void saddr_split(serv_addr *saddr, const char *addr_txt) {
    char *toke = NULL;
    memset(saddr, '\0', sizeof (serv_addr));
    toke = strchr(addr_txt, ':');
    if (toke) {
        strncpy(saddr->sin_addr, addr_txt, toke - addr_txt);
        saddr->sin_port = atoi(++toke);
    } else strcpy(saddr->sin_addr, addr_txt);
}

char *name_value(char **name, char *str, const char delim) {
    char *toksp;
    static char *tokep;
    //
    if (!str) {
        if (!tokep) return NULL;
        toksp = tokep + 1;
    } else toksp = str;
    //
    tokep = strchr(toksp, delim);
    if (tokep) *tokep = '\0';
    //
    if (name) *name = toksp;
    char *value = strchr(toksp, '=');
    if (value) {
        *value = '\0';
        ++value;
    } else value = toksp;
    //
    return value;
}

inline char *next_dirpath(char *path, char *subdir) {
    static char *toke, *toksp;
    static char fullpath[MAX_PATH * 3];
    char dirpath[MAX_PATH * 3];
    //
    if (!subdir) {
        if (!toke) return NULL;
    } else toksp = toke = subdir;
    toke = strchr(++toke, '/');
    //
    strcpy(fullpath, path);
    if (toke) {
        strncpy(dirpath, toksp, toke - toksp);
        strcat(fullpath, dirpath);
    } else strcat(fullpath, toksp);
    //
    return fullpath;
}

char *bakup_folder(time_t bak_time) { // Nov_15_1995_GMT
    static char folder[TIME_LENGTH];
    struct tm *utctm;
    //
    if (!bak_time) bak_time = time(NULL);
    utctm = gmtime(&bak_time);
    if (!strftime(folder, TIME_LENGTH, "%b_%d_%Y_%Z", utctm)) return NULL;
    //
    return folder;
}

char *strlchr(const char *str) {
    char *char_ptr;
    unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;
    //
    for (char_ptr = (char *) str; ((unsigned long int) char_ptr & (sizeof (longword) - 1)) != 0; ++char_ptr) {
        if (*char_ptr == '\0')
            return (char_ptr - 1);
    }
    //
    longword_ptr = (unsigned long int *) char_ptr;
    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof (longword) > 4) {
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }
    if (sizeof (longword) > 8) abort();
    //
    for (;;) {
        longword = *longword_ptr++;
        if (((longword - lomagic) & ~longword & himagic) != 0) {
            char *cp = (char *) (longword_ptr - 1);
            //
            if (cp[0x00] == 0)
                return (cp - 1);
            if (cp[1] == 0)
                return cp;
            if (cp[2] == 0)
                return (cp + 1);
            if (cp[3] == 0)
                return (cp + 2);
            if (sizeof (longword) > 4) {
                if (cp[4] == 0)
                    return (cp + 3);
                if (cp[5] == 0)
                    return (cp + 4);
                if (cp[6] == 0)
                    return (cp + 5);
                if (cp[7] == 0)
                    return (cp + 6);
            }
        }
    }
}

char *strend(const char *str) {
    char *char_ptr;
    unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;
    //
    for (char_ptr = (char *) str; ((unsigned long int) char_ptr & (sizeof (longword) - 1)) != 0; ++char_ptr) {
        if (*char_ptr == '\0')
            return char_ptr;
    }
    //
    longword_ptr = (unsigned long int *) char_ptr;
    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof (longword) > 4) {
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }
    if (sizeof (longword) > 8) abort();
    //
    for (;;) {
        longword = *longword_ptr++;
        if (((longword - lomagic) & ~longword & himagic) != 0) {
            char *cp = (char *) (longword_ptr - 1);
            //
            if (cp[0x00] == 0)
                return cp;
            if (cp[1] == 0)
                return (cp + 1);
            if (cp[2] == 0)
                return (cp + 2);
            if (cp[3] == 0)
                return (cp + 3);
            if (sizeof (longword) > 4) {
                if (cp[4] == 0)
                    return (cp + 4);
                if (cp[5] == 0)
                    return (cp + 5);
                if (cp[6] == 0)
                    return (cp + 6);
                if (cp[7] == 0)
                    return (cp + 7);
            }
        }
    }
}

char *strzcpy(char *dest, const char *source, size_t count) {
    char *start = dest;
    while (count && (*dest++ = *source++)) count--; /* copy string */
    if (count) /* pad out with zeroes */
        while (--count) *dest++ = '\0';
    else *dest = '\0';
    return (start);
}

//

char *kill_blank(char *stri) {
    char *toke;
    for (toke = stri; '\0' != toke[0x00]; ++toke) {
        if (' ' != toke[0x00]) return toke;
    }
    return NULL;
}

char *kill_inval(char *stri) {
    char *toke;
    for (toke = stri; '\0' != toke[0x00]; ++toke) {
        if (' ' != toke[0x00] && '\n' != toke[0x00]) return toke;
    }
    return NULL;
}


//

char *straln(char *str) {
    for (; '\0' != str[0x00]; str++) {
        if (isalnum(str[0x00])) return str;
    }
    return NULL;
}

char *stralp(char *str) {
    for (; '\0' != str[0x00]; str++) {
        if (isalpha(str[0x00])) return str;
    }
    return NULL;
}

char *strdig(char *str) {
    for (; '\0' != str[0x00]; str++) {
        if (isdigit(str[0x00])) return str;
    }
    return NULL;
}

char *strpar(char *str) {
    for (; '\0' != str[0x00]; str++) {
        if ('"' == str[0x00] || isalnum(str[0x00])) return str;
    }
    return NULL;
}

//

char *blank_decode(char *stri) {
    char *toksp, *tokdp;
    if (!stri) return NULL;
    //
    if (' ' == stri[0x00]) {
        tokdp = toksp = stri;
        for (toksp++; '\0' != toksp[0x00] && ' ' == toksp[0x00]; toksp++);
        for (; '\0' != toksp[0x00] && ' ' != toksp[0x00]; toksp++)
            *tokdp++ = *toksp;
    } else {
        tokdp = stri;
        for (tokdp++; '\0' != tokdp[0x00] && ' ' != tokdp[0x00]; tokdp++);
    }
    tokdp[0x00] = '\0';
    //
    return stri;
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

//
// -1:error 0x00:objeid 0x01:predicate / condition 0x02:"*"
#define PREDICA_TOK "!=<>&|"
#define WILDCARD_TOK '*'
#define PRED_AND_TOK "AND"
#define PRED_OR_TOK "OR"
#define PRED_NOT_TOK "NOT"

int check_predi_type(char *para_str) {
    printf("check_predi_type, para_str:|%s|\n", para_str);
    if (WILDCARD_TOK == para_str[0x00] && '\0' == para_str[0x01]) return PREDI_TYPE_TRAVE;
    if (strpbrk(para_str, PREDICA_TOK)) return PREDI_TYPE_CONDI;
    //
    char *toke = para_str;
    for (; '\0' != toke[0x00]; toke++) {
        for (; ' ' == toke[0x00]; toke++);
        if ('"' == toke[0x00]) {
            toke++;
            for (; '\0' != toke[0x00] && '"' != toke[0x00]; toke++);
            continue;
        }
        if (!strncmp(PRED_AND_TOK, toke, 0x03) || !strncmp(PRED_OR_TOK, toke, 0x02) || !strncmp(PRED_NOT_TOK, toke, 0x03))
            return PREDI_TYPE_CONDI;
        for (; '\0' != toke[0x00] && ' ' != toke[0x00]; toke++);
    }
    //
    return PREDI_TYPE_OBJID;
}

//

int query_source_numb(char *source) {
    int source_numb = 0x00;
    if ('\0' != source[0x00]) source_numb++;
    char *toke = source;
    while ((toke = strchr(toke, ','))) source_numb++;
    //
    return source_numb;
}

int query_source_coten(char quer_conta[SOUR_COTE][OBJE_LENGTH], char *source) {
    char *toksp = source, *tokep;
    int inde = 0x00;
    for (; SOUR_COTE > inde && '\0' != toksp[0x00]; inde++) {
        for (; ' ' == toksp[0x00] || ',' == toksp[0x00]; toksp++);
        tokep = toksp;
        for (; ' ' != tokep[0x00] && ',' != tokep[0x00]; tokep++);
        strzcpy(quer_conta[inde], toksp, tokep - toksp);
        toksp = tokep + 0x01;
    }
    MKZERO(quer_conta[inde]);
    //
    return inde;
}

//

char *qstrch(const char * stri, int ch) {
    while (*stri && *stri != (char) ch) {
        if ('\\' == *stri) stri++;
        else if ('"' == *stri) {
            for (stri++; '"' != *stri; stri++)
                if ('\\' == *stri) stri++;
        }
        stri++;
    }
    if (*stri == (char) ch) return ((char *) stri);
    return (NULL);
}

char *qstrst(const char * str1, const char * str2) {
    char *cp = (char *) str1;
    char *s1, *s2;
    //
    if (!*str2) return ((char *) str1);
    while (*cp) {
        if ('\\' == *cp) cp++;
        else if ('"' == *cp) {
            for (cp++; '"' != *cp; cp++)
                if ('\\' == *cp) cp++;
        } else {
            s1 = cp;
            s2 = (char *) str2;
            while (*s1 && *s2 && !(*s1 - *s2)) s1++, s2++;
            if (!*s2) return (cp);
        }
        cp++;
    }
    //
    return (NULL);
}

//

int ostcmp(const char *p1, const char *p2) {
    if (!p2) return -1;
    //
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;
    //
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    //
    return c1 - c2;
}

//

char *strupr(char *str) {
    char *toke = str;
    for (; toke[0x00]; toke++) {
        if (toke[0x00] >= 'a' && toke[0x00] <= 'z')
            toke[0x00] ^= 0x20;
    }
    //
    return str;
}

char *strlow(char *str) {
    char *toke = str;
    for (; toke[0x00]; toke++) {
        if (toke[0x00] >= 'A' && toke[0x00] <= 'Z')
            toke[0x00] ^= 0x20;
    }
    //
    return str;
}

void expand_tail(char **stri, char *posi) {
    stri[0x00] = (char *) strend(posi);
    ++(stri[0x00]);
    stri[0x01] = NULL;
}

//

char *inser_head(char *data, int slen, int hlen) {
    char *posi_sta = data + slen;
    char *posi_end = posi_sta + hlen;
    for (; data <= posi_sta; posi_sta--, posi_end--)
        posi_end[0x00] = posi_sta[0x00];
    return data;
}