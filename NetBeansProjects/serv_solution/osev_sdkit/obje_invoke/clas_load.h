/* 
 * File:   clas_load.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 4:21
 */

#ifndef CLAS_LOAD_H
#define CLAS_LOAD_H

#include "commo_header.h"
#include "clas_list.h"

#ifdef __cplusplus
extern "C" {
#endif
  
//
clas_attr *parse_class_attri(clas_attr *clasa, char *clat_path);
clas_meta *parse_class_conte(clas_meta *clasm, char *clas_path);
char *parse_class_decla(char *clas_decl, char *clas_path);
char *find_class_objid(char *clas_obid, char *clat_path);
char *find_class_attri(char *clas_attr, char *clat_path);
char *find_class_inheri(char *clas_inhe, char *clat_path);
char *find_class_defin(char *clas_decl, char *clas_path);
// int parse_class_method(struct ivk_list *ivklist, char *clas_path);



//


#ifdef __cplusplus
}
#endif

#endif /* CLAS_LOAD_H */

