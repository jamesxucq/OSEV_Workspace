#ifndef STRI_UTILI_H_
#define STRI_UTILI_H_

#include <string.h>
#include <time.h>

#include "logger.h"
#include "commo_macro.h"
#include "osev_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *escpy(char * dest, const char * src);

    //
    char *lsprif(char *dest, const char *format, ...);
    char *lscpy(char * dest, const char * src);
    char *lccpy(char * dest, const char src);
    char *lsncpy(char *dest, const char *src, size_t n);
    char *lszcpy(char *dest, const char *source, size_t count);
    char *lscat(char * dest, const char * src);
    char *lccat(char * dest, const char src);
    char *lsncat(char *dest, const char *src, size_t n);

    //
    char *strsplit(char *str, const char *delim);
#define TEXT_SPLIT(line_txt, str, delim, tokep) { \
    char *toksp; \
    if(str) { \
        toksp = str; \
        tokep = strstr(toksp, delim); \
        if (tokep) *tokep = '\0'; \
        line_txt = toksp; \
    } else line_txt = NULL; \
}
#define SPLIT_TOKEN(line_txt, delim, tokep) { \
    char *toksp; \
    if(tokep) { \
        toksp = tokep + strlen(delim); \
        tokep = strstr(toksp, delim); \
        if (tokep) *tokep = '\0'; \
        line_txt = toksp; \
    } else line_txt = NULL; \
}

    //char *split_value(char *str);
#define SPLIT_VALUE(tval, line_txt) { \
    char *toksp, *tokep; \
    toksp = strchr(line_txt, ' '); \
    if (toksp) *toksp = '\0'; \
    ++toksp; \
    tokep = strrchr(toksp, ' '); \
    if (tokep) *tokep = '\0'; \
    tval = toksp; \
}

    // char *split_line(char *str);
#define SPLIT_LINE(tval, line_txt) { \
    char *toke; \
    toke = strstr(line_txt, ": "); \
    if (toke) *toke = '\0'; \
    tval = toke + 2; \
}

    char *name_value(char **name, char *str, const char delim);

#define APPEND_PATH(APATH, PATH, SUBDIR) \
        sprintf(APATH, "%s%s", PATH, SUBDIR + 1)
#define POOL_PATH(PPATH, PATH, SUBDIR) \
        sprintf(PPATH, "%s/user_pool%s", PATH, SUBDIR)
#define POOL_PATH_EXA(PPATH, PLOCA, PATH) { \
        sprintf(PPATH, "%s/user_pool", PATH); \
        PLOCA = strend(PPATH); \
    }
#define POOL_PATH_EXB(PLOCA, PSDIR, SUBDIR) { \
        strcpy((char *)PLOCA, SUBDIR); \
        PSDIR = strend(PLOCA); \
    }
#define LIST_CACHE(LPATH, PATH, SUBDIR) \
        sprintf(LPATH, "%s/cache%s", PATH, SUBDIR + 1)

    // inline char *last_bakup(char *path, char *subdir, time_t bak_time);
    char *bakup_folder(time_t bak_time);
#define LAST_BAKUP(BAKPATH, PATH, SUBDIR, BAKTIME) \
         sprintf(BAKPATH, "%s/backup/%s%s_%x", PATH, bakup_folder(BAKTIME), strrchr(SUBDIR, '/'), (uint32)BAKTIME)
#define BAKUP_PATH(BAKPATH, PATH, BAKTIME, SUBDIR) \
        sprintf(BAKPATH, "%s/backup/%s%s", PATH, bakup_folder(BAKTIME), SUBDIR + 1)
    //
    inline char *next_dirpath(char *path, char *subdir);

    char *utc_time_text(time_t utctime);
    // Wed, 15 Nov 1995 04:58:08 GMT
#define UTC_TIME_TEXT(TIMESTR, UTCTIME) { \
    if (!strftime(TIMESTR, TIME_LENGTH, "%a, %d %b %Y %H:%M:%S %Z", gmtime(&UTCTIME))) \
        { _LOG_WARN("strftime error:%d", UTCTIME); } \
}
    time_t utc_time_value(char *timestr);
    // Wed, 15 Nov 1995 04:58:08 GMT
#define UTC_TIME_VALUE(CALENDER, TIMESTR) { \
    struct tm utctm; \
    memset(&utctm, '\0', sizeof (struct tm)); \
    _strptime(&utctm, TIMESTR); \
    CALENDER = _mktime(&utctm); \
}

    //
    char *random_seion_id();
    char *random_valid();
    char *random_accesskey();

    typedef struct {
        char sin_addr[SERVN_LENGTH];
        int sin_port;
    } serv_addr;

    //
    void saddr_split(serv_addr *saddr, const char *addr_txt);
    char *strlchr(const char *str);
    char *strend(const char *str);
    char *strzcpy(char *dest, const char *source, size_t count);

    //
#define KILL_BLANK(TOKE, STRI) { \
    for (TOKE = STRI; '\0' != TOKE[0x00]; ++TOKE) { \
        if (' ' != TOKE[0x00]) break; \
    } \
}
    char *kill_blank(char *stri);
    char *blank_decode(char *stri);


#define KILL_INVAL(TOKE, STRI) { \
    for (TOKE = STRI; '\0' != TOKE[0x00]; ++TOKE) { \
        if (' ' != TOKE[0x00] && '\n' != TOKE[0x00]) break; \
    } \
}
    char *kill_inval(char *stri);

    //
    char *straln(char *str);
    char *stralp(char *str);
    char *strdig(char *str);
    char *strpar(char *str);

    //
    char *quote_decode(char *quostr);
#define kill_quote(paras) { \
    char **toke = paras; \
    for (; toke[0x00]; toke++) quote_decode(toke[0x00]); \
}

    //
#define PREDI_TYPE_EXCEP -1
#define PREDI_TYPE_OBJID 0x00
#define PREDI_TYPE_CONDI 0x01
#define PREDI_TYPE_TRAVE 0x02

    int check_predi_type(char *para_str);
    int query_source_numb(char *source);
    int query_source_coten(char quer_conta[SOUR_COTE][OBJE_LENGTH], char *source);

    //
    char *qstrch(const char *stri, int ch);
    char *qstrst(const char * str1, const char * str2);
    int ostcmp(const char *p1, const char *p2);

    /*Check path string contains invalid characters.*/
#define VALID_FILE_PATH(PATH) \
    ('\0' == *PATH || strlen(PATH) >= PATH_MAX || strpbrk(PATH, "\\:*?\"<>|"))

    //  
#define lmcpy_o(dest, src, len, last) { \
    dest = last; \
    memcpy(last, src, len); \
    last += len; \
}

#define lscpy_o(dest, src, last) { \
    dest = last; \
    last = lscpy(last, src); \
    last++; \
}

#define lszcpy_o(dest, src, coun, last) { \
    dest = last; \
    last = lszcpy(last, src, coun); \
    last++; \
}

    //
    void expand_tail(char **stri, char *posi);

    //

    char *strupr(char *str);
    char *strlow(char *str);

    //
    char *inser_head(char *data, int slen, int hlen);

#ifdef __cplusplus
}
#endif

#endif /* STRI_UTILI_H_ */
