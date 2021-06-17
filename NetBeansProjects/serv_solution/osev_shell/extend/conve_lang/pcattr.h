
/* 
 * File:   pcattr.h
 * Author: James Xu
 *
 * Created on 2017.6.23, AM 8:49
 */

#ifndef PCATTR_H
#define PCATTR_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *parse_attrib(osv_oid_t *obje_oid, char *clasn, unsigned long *version, int *integrity, char *clas_data);

    //
    char *split_class_attri(char *attr_data, char *clas_data);
    char *find_class_attri(char *clas_data);
    
    //


#ifdef __cplusplus
}
#endif

#endif /* PCATTR_H */

