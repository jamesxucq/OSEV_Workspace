
/* 
 * File:   conve.h
 * Author: James Xu
 *
 * Created on 2016.12.21, PM 3:38
 */

#ifndef CONVE_H
#define CONVE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *conve_class_clang(char *clang_txt, char *clas_decl);
    //
    char *conve_advan_clang(char *clang_txt, char *advan_txt, char *clas_decl, int meth_type);
    char *conve_handle_name(char *handn, char *mepan, char *meth_txt);
//

#ifdef __cplusplus
}
#endif

#endif /* CONVE_H */

