
/* 
 * File:   conver.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 3:22
 */

#ifndef CONVER_H
#define CONVER_H

#include "clas_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *conve_class_conte(char *clang_txt, class_meta *clasm);
    char *conve_metho_conte(char *clang_txt, class_meta *clasm, char *osdb);


#ifdef __cplusplus
}
#endif

#endif /* CONVER_H */

