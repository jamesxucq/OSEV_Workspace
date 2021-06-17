
/* 
 * File:   parse.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 3:20
 */

#ifndef PARSE_H
#define PARSE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    class_meta *parse_class_conte(class_meta *clasm, char *clas_data);

    //
#define CTYPE_CLAS_ATTRIB 0x0001
#define CTYPE_CLAS_CONTE 0x0002
#define CTYPE_METH_CONTE 0x0004
    int conv_conte_type(char *conv_data);

#ifdef __cplusplus
}
#endif

#endif /* PARSE_H */

