
/* 
 * File:   clas_save.h
 * Author: James Xu
 *
 * Created on 2016.12.23, AM 9:35
 */

#ifndef CLAS_SAVE_H
#define CLAS_SAVE_H

#include "clas_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    int save_class_conte(char *clat_path, clas_attr *clasa, char *clas_path, clas_meta *clasm);
    int save_class_attri(char *clat_path, clas_attr *clasa);
    //
#define class_exist FILE_EXIST
    int creat_class_conte(char *clat_path, char *clas_path, char *clasn, char *clas_decl);
    int class_dele_conte(char *clat_path, char *clas_path);


#ifdef __cplusplus
}
#endif

#endif /* CLAS_SAVE_H */

