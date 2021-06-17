
/* 
 * File:   xml_utili.h
 * Author: James Xu
 *
 * Created on 2017.5.25, PM2:11
 */

#ifndef XML_UTILI_H
#define XML_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define GET_ELEMENT_VALUE(ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.len; \
        if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
            strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
            PARSE_TOKEN = elem_end + LABEL_END.len; \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

    //
char *get_attval(char *value, char *attrib);
char *get_attval2(char *value1, char *value2, char *attrib1, char *attrib2);
    
//
#define GET_ATTRIB_ELEMENT_VALUE(ATTRIB_VALUE, ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, ATTRIB_LABEL, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.len; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            strzcpy(ATTRIB_VALUE, elem_start, elem_end - elem_start); \
            if(get_attval(ATTRIB_VALUE, ATTRIB_LABEL.data)) { \
                elem_start = elem_end + 0x01; \
                if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
                    strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
                    PARSE_TOKEN = elem_end + LABEL_END.len; \
                } else PARSE_TOKEN = NULL; \
            } else PARSE_TOKEN = NULL; \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

#define GET_ATTRIB2_ELEMENT_VALUE(ATTRIB_VALUE1, ATTRIB_VALUE2, ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, ATTRIB_LABEL1, ATTRIB_LABEL2, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.len; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            strzcpy(ATTRIB_VALUE1, elem_start, elem_end - elem_start); \
            if(get_attval2(ATTRIB_VALUE1, ATTRIB_VALUE2, ATTRIB_LABEL1.data, ATTRIB_LABEL2.data)) { \
                elem_start = elem_end + 0x01; \
                if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
                    strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
                    PARSE_TOKEN = elem_end + LABEL_END.len; \
                } else PARSE_TOKEN = NULL; \
            } else PARSE_TOKEN = NULL; \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

    //


#ifdef __cplusplus
}
#endif

#endif /* XML_UTILI_H */

